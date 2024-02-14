cmake_minimum_required(VERSION 3.0.2)

project(curl-ssl-sandbox)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenSSL REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(libcurl REQUIRED IMPORTED_TARGET libcurl)

add_executable(curl-ssl-example curl-ssl-example.cpp)
target_link_libraries(curl-ssl-example PRIVATE OpenSSL::SSL PkgConfig::libcurl)
