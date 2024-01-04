#include <string>
#include <map>

struct response {
  std::string text;
  unsigned int status_code;
};

struct options {
  std::multimap<std::string, std::string> headers;
};

response get(const std::string& url, const options& opts = {});
