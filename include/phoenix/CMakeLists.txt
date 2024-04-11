cmake_minimum_required(VERSION 3.0)
project(phoenix-from-scratch)

include (cmake/utils.cmake)

set(CMAKE_VERBOSE_MAKEFILE ON)

# 指定编译选项
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -std=c++11 -O0 -ggdb -Wall -Werror")

# -rdynamic: 将所有符号都加入到符号表中，便于使用dlopen或者backtrace追踪到符号
# -fPIC: 生成位置无关的代码，便于动态链接
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -rdynamic -fPIC")

# -Wno-unused-function: 不要警告未使用函数
# -Wno-builtin-macro-redefined: 不要警告内置宏重定义，用于重定义内置的__FILE__宏
# -Wno-deprecated: 不要警告过时的特性
# -Wno-deprecated-declarations: 不要警告使用带deprecated属性的变量，类型，函数
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-function -Wno-builtin-macro-redefined -Wno-deprecated -Wno-deprecated-declarations")

include_directories(.)

option(BUILD_TEST "ON for complile test" ON)

find_package(Boost REQUIRED) 
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

set(LIB_SRC
    phoenix/log.cpp
    phoenix/util.cpp
    phoenix/mutex.cc
    phoenix/env.cc
    phoenix/config.cc
    phoenix/thread.cc
    phoenix/fiber.cc
    phoenix/scheduler.cc
    phoenix/iomanager.cc
    phoenix/timer.cc
    phoenix/fd_manager.cc
    phoenix/hook.cc
    phoenix/address.cc 
    phoenix/socket.cc 
    phoenix/bytearray.cc 
    phoenix/tcp_server.cc 
    phoenix/http/http-parser/http_parser.c 
    phoenix/http/http.cc
    phoenix/http/http_parser.cc 
    phoenix/stream.cc 
    phoenix/streams/socket_stream.cc
    phoenix/http/http_session.cc 
    phoenix/http/servlet.cc
    phoenix/http/http_server.cc 
    phoenix/uri.cc 
    phoenix/http/http_connection.cc 
    phoenix/daemon.cc 
    )

add_library(phoenix SHARED ${LIB_SRC})
force_redefine_file_macro_for_sources(phoenix)

set(LIBS
    phoenix
    pthread
    dl
    yaml-cpp
)

if(BUILD_TEST)
phoenix_add_executable(test_log "tests/test_log.cpp" phoenix "${LIBS}")
phoenix_add_executable(test_util "tests/test_util.cpp" phoenix "${LIBS}")
phoenix_add_executable(test_env "tests/test_env.cc" phoenix "${LIBS}")
phoenix_add_executable(test_config "tests/test_config.cc" phoenix "${LIBS}")
phoenix_add_executable(test_thread "tests/test_thread.cc" phoenix "${LIBS}")
phoenix_add_executable(test_fiber "tests/test_fiber.cc" phoenix "${LIBS}")
phoenix_add_executable(test_fiber2 "tests/test_fiber2.cc" phoenix "${LIBS}")
phoenix_add_executable(test_scheduler "tests/test_scheduler.cc" phoenix "${LIBS}")
phoenix_add_executable(test_iomanager "tests/test_iomanager.cc" phoenix "${LIBS}")
phoenix_add_executable(test_timer "tests/test_timer.cc" phoenix "${LIBS}")
phoenix_add_executable(test_hook "tests/test_hook.cc" phoenix "${LIBS}")
phoenix_add_executable(test_address "tests/test_address.cc" phoenix "${LIBS}")
phoenix_add_executable(test_socket_tcp_server "tests/test_socket_tcp_server.cc" phoenix "${LIBS}")
phoenix_add_executable(test_socket_tcp_client "tests/test_socket_tcp_client.cc" phoenix "${LIBS}")
phoenix_add_executable(test_bytearray "tests/test_bytearray.cc" phoenix "${LIBS}")
phoenix_add_executable(test_tcp_server "tests/test_tcp_server.cc" phoenix "${LIBS}")
phoenix_add_executable(test_http "tests/test_http.cc" phoenix "${LIBS}")
phoenix_add_executable(test_http_parser "tests/test_http_parser.cc" phoenix "${LIBS}")
phoenix_add_executable(test_http_server "tests/test_http_server.cc" phoenix "${LIBS}")
phoenix_add_executable(test_uri "tests/test_uri.cc" phoenix "${LIBS}")
phoenix_add_executable(test_http_connection "tests/test_http_connection.cc" phoenix "${LIBS}")
phoenix_add_executable(test_daemon "tests/test_daemon.cc" phoenix "${LIBS}")
endif()

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)