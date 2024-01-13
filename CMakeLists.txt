cmake_minimum_required(VERSION 3.22)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/cmake/toolchain.cmake)

include("cmake/HunterGate.cmake")

HunterGate(
    URL "https://api.github.com/repos/hades/hunter-cpp-pm/tarball/2daf2323d0dbc40ab2e36ba1e09ce5e3e7c764c1"
    SHA1 "d1c51689c7c2cb8075cff475ac15979798f44c78"
)

project(aoc15)

hunter_add_package(Boost COMPONENTS url)
find_package(Boost CONFIG REQUIRED url)
hunter_add_package(cpptrace)
find_package(cpptrace CONFIG REQUIRED)
hunter_add_package(cxxopts)
find_package(cxxopts CONFIG REQUIRED)
hunter_add_package(OpenSSL)
find_package(OpenSSL REQUIRED)
hunter_add_package(rang)
find_package(rang CONFIG REQUIRED)
hunter_add_package(spdlog)
find_package(spdlog CONFIG REQUIRED)
hunter_add_package(yaml-cpp)
find_package(yaml-cpp CONFIG REQUIRED)
hunter_add_package(Zug)
find_package(Zug CONFIG REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -std=c++23 -Wall -Wextra -Werror")

add_library(crash STATIC crash.cc crash.h)
target_link_libraries(crash
                      cpptrace::cpptrace
)

add_library(requests STATIC requests.cc requests.h)
target_link_libraries(requests
                      Boost::boost
                      Boost::url
                      OpenSSL::SSL
                      spdlog::spdlog
                      zug
)

add_library(dec01 OBJECT dec01.cc)
target_link_libraries(dec01
                      Boost::boost
                      cpptrace::cpptrace
                      spdlog::spdlog
)

add_executable(aoc15 main.cc)
target_link_libraries(aoc15 PUBLIC
                      crash
                      requests
                      $<TARGET_OBJECTS:dec01>
                      cpptrace::cpptrace
                      cxxopts::cxxopts
                      spdlog::spdlog
)
