#include "requests.h"

#include <string_view>

#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/context.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/url/parse.hpp>
#include <spdlog/spdlog.h>
#include <zug/transducer/map.hpp>
#include <zug/transducer/range.hpp>

using boost::urls::parse_absolute_uri;
namespace http = boost::beast::http;

std::string debug_string(const boost::asio::ip::basic_resolver_results<boost::asio::ip::tcp>& res) {
  std::ostringstream str;
  for (const auto& ep: res) {
    str << ep.endpoint() << " ";
  }
  return str.str();
}

http::response<http::string_body> execute_over_tcp(
    boost::asio::io_context& io_context,
    boost::beast::flat_buffer& buf,
    const http::request<http::string_body>& req,
    const boost::asio::ip::tcp::resolver::results_type& lookup_results) {
  boost::beast::tcp_stream stream(io_context);
  spdlog::debug("connecting to {}", debug_string(lookup_results));
  stream.connect(lookup_results);
  http::write(stream, req);
  http::response<http::string_body> resp;
  http::read(stream, buf, resp);
  return resp;
}

http::response<http::string_body> execute_over_ssl(
    boost::asio::io_context& io_context,
    boost::beast::flat_buffer& buf,
    const http::request<http::string_body>& req,
    const boost::asio::ip::tcp::resolver::results_type& lookup_results) {
  boost::asio::ssl::context ssl_context(boost::asio::ssl::context::tlsv12_client);
  boost::beast::ssl_stream<boost::beast::tcp_stream> stream(io_context, ssl_context);
  spdlog::debug("connecting to {} (ssl)", debug_string(lookup_results));
  boost::beast::get_lowest_layer(stream).connect(lookup_results);
  stream.handshake(boost::asio::ssl::stream_base::client);
  http::write(stream, req);
  http::response<http::string_body> resp;
  http::read(stream, buf, resp);
  return resp;
}

response get(const std::string& url, const options& opts) {
  auto url_parse = parse_absolute_uri(url).value();
  std::string_view port = "443";
  bool https = true;
  if (url_parse.has_scheme() && url_parse.scheme_id() == boost::urls::scheme::http) {
    port = "80";
    https = false;
  }
  if (url_parse.has_port()) {
    port = url_parse.port();
  }
  boost::asio::io_context io_context;
  boost::asio::ip::tcp::resolver resolver(io_context);
  const std::string host = url_parse.host();
  spdlog::debug("resolving {}", host);
  const auto lookup_results = resolver.resolve(host, port);
  http::request<http::string_body> req{
    http::verb::get, url_parse.path(), 11};
  req.set(http::field::host, host);
  req.set(http::field::user_agent, "hades/aoc15 (https://github.com/hades/aoc15)");
  for (const auto& header: opts.headers) {
    req.set(header.first, header.second);
  }
  boost::beast::flat_buffer buf;
  auto resp = https?   execute_over_ssl(io_context, buf, req, lookup_results): execute_over_tcp(io_context, buf, req, lookup_results);
  return response{
    .text = resp.body(),
    .status_code = resp.result_int(),
  };
}