cmake_minimum_required(VERSION 3.28)
project(HelloWorldGRPC)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Protobuf
find_package(PkgConfig REQUIRED)
pkg_check_modules(PROTOBUF REQUIRED protobuf)
pkg_check_modules(GRPC REQUIRED grpc++)

# Get protoc and grpc_cpp_plugin
find_program(PROTOC protoc)
find_program(GRPC_CPP_PLUGIN grpc_cpp_plugin)

if(NOT PROTOC)
    message(FATAL_ERROR "protoc not found")
endif()

if(NOT GRPC_CPP_PLUGIN)
    message(FATAL_ERROR "grpc_cpp_plugin not found")
endif()

# Generate protobuf and gRPC code
set(PROTO_FILES ${CMAKE_CURRENT_SOURCE_DIR}/protos/helloworld.proto)
get_filename_component(PROTO_FILE_NAME ${PROTO_FILES} NAME_WE)

set(GENERATED_PROTO_DIR ${CMAKE_CURRENT_BINARY_DIR}/generated)
file(MAKE_DIRECTORY ${GENERATED_PROTO_DIR})

add_custom_command(
        OUTPUT
        "${GENERATED_PROTO_DIR}/${PROTO_FILE_NAME}.pb.cc"
        "${GENERATED_PROTO_DIR}/${PROTO_FILE_NAME}.pb.h"
        "${GENERATED_PROTO_DIR}/${PROTO_FILE_NAME}.grpc.pb.cc"
        "${GENERATED_PROTO_DIR}/${PROTO_FILE_NAME}.grpc.pb.h"
        COMMAND ${PROTOC}
        ARGS
        --grpc_out="${GENERATED_PROTO_DIR}"
        --cpp_out="${GENERATED_PROTO_DIR}"
        -I "${CMAKE_CURRENT_SOURCE_DIR}/protos"
        --plugin=protoc-gen-grpc=${GRPC_CPP_PLUGIN}
        "${PROTO_FILES}"
        DEPENDS ${PROTO_FILES}
)

# Create library from generated files
add_library(helloworld_grpc_proto
        ${GENERATED_PROTO_DIR}/${PROTO_FILE_NAME}.pb.cc
        ${GENERATED_PROTO_DIR}/${PROTO_FILE_NAME}.pb.h
        ${GENERATED_PROTO_DIR}/${PROTO_FILE_NAME}.grpc.pb.cc
        ${GENERATED_PROTO_DIR}/${PROTO_FILE_NAME}.grpc.pb.h
)

target_include_directories(helloworld_grpc_proto
        PUBLIC
        ${GENERATED_PROTO_DIR}
        ${PROTOBUF_INCLUDE_DIRS}
        ${GRPC_INCLUDE_DIRS}
)

target_link_libraries(helloworld_grpc_proto
        PUBLIC
        ${PROTOBUF_LIBRARIES}
        ${GRPC_LIBRARIES}
)

# Server executable
add_executable(greeter_server src/greeter_server.cpp)
target_link_libraries(greeter_server
        PRIVATE
        helloworld_grpc_proto
)

# Client executable
add_executable(greeter_client src/greeter_client.cpp)
target_link_libraries(greeter_client
        PRIVATE
        helloworld_grpc_proto
)