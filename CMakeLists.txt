cmake_minimum_required(VERSION 3.22)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/cmake/toolchain.cmake)

include("cmake/HunterGate.cmake")

HunterGate(
    URL "https://api.github.com/repos/hades/hunter-cpp-pm/tarball/4ecf814eaec65d4bfecf9b1903c4a65e433aa91d"
    SHA1 "f09d3e1392cec9c378a7336404b99b49c26e606f"
)

project(aoc15)

include(CTest)

hunter_add_package(Boost COMPONENTS json test url)
find_package(Boost CONFIG REQUIRED json unit_test_framework url)
hunter_add_package(cpptrace)
find_package(cpptrace CONFIG REQUIRED)
hunter_add_package(cryptopp)
find_package(cryptopp CONFIG REQUIRED)
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
hunter_add_package(z3)
find_package(Z3 CONFIG REQUIRED)

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

add_library(solvers STATIC solvers.h)
target_link_libraries(solvers
                      cpptrace::cpptrace
)

add_executable(aoc15 main.cc)
target_link_libraries(aoc15 PUBLIC
                      Boost::json
                      crash
                      requests
                      cpptrace::cpptrace
                      cryptopp-static
                      cxxopts::cxxopts
                      spdlog::spdlog
                      yaml-cpp
                      z3::libz3
)

set(extra_link_libraries_4 cryptopp-static)
set(extra_link_libraries_12 Boost::json)
set(extra_link_libraries_13 z3::libz3)

foreach(day RANGE 1 13)
  if(day LESS 10)
    set(_day_formatted "dec0${day}")
  else()
    set(_day_formatted "dec${day}")
  endif()
  add_library(${_day_formatted} ${_day_formatted}.cc)
  target_link_libraries(${_day_formatted} PUBLIC
                        Boost::boost
                        cpptrace::cpptrace
                        spdlog::spdlog
  )
  add_executable(${_day_formatted}_test ${_day_formatted}_test.cc)
  target_link_libraries(${_day_formatted}_test PUBLIC
                        Boost::boost
                        Boost::unit_test_framework
                        solvers
                        $<TARGET_OBJECTS:${_day_formatted}>
                        ${extra_link_libraries_${day}}
  )
  add_test(NAME ${_day_formatted}_test COMMAND ${_day_formatted}_test)
  target_link_libraries(aoc15 PUBLIC $<TARGET_OBJECTS:${_day_formatted}>)
endforeach()
