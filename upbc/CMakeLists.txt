#
# Copyright 2024 The titan-search Authors.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#    https://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
set(UPBC_COMMON_SRC
        common.cc
        names.cc
        file_layout.cc
)
add_library(upbc_common STATIC ${UPBC_COMMON_SRC})
target_link_libraries(upbc_common upb protobuf::libprotobuf)
target_include_directories(upbc_common PRIVATE ${upb_SOURCE_DIR})

add_executable(protoc-gen-upb protoc-gen-upb.cc)
target_link_libraries(protoc-gen-upb upb_base upbc_common ${DEPS_LIB})
target_include_directories(protoc-gen-upb PRIVATE ${upb_SOURCE_DIR})

file(MAKE_DIRECTORY ${upb_SOURCE_DIR}/upbc)
file(COPY ${PROTOBUF_INCLUDE_DIR}/google/protobuf/compiler/plugin.proto DESTINATION ${upb_SOURCE_DIR}/google/protobuf/compiler)
add_custom_command(
        OUTPUT code_generator_request_upb_h code_generator_request_upb_c
        COMMAND ${PROTOBUF_PROTOC_EXECUTABLE} ${PROTOC_FLAGS} -I${upb_SOURCE_DIR} --plugin=${upb_BINARY_DIR}/upbc/protoc-gen-upb --upb_out=bootstrap_upb:${upb_BINARY_DIR} ${upb_SOURCE_DIR}/upbc/code_generator_request.proto
        DEPENDS protoc-gen-upb
)
add_executable(protoc-gen-upbdefs protoc-gen-upbdefs.cc)
target_link_libraries(protoc-gen-upbdefs upb_base upbc_common ${DEPS_LIB})
target_include_directories(protoc-gen-upbdefs PRIVATE ${upb_SOURCE_DIR})

add_custom_command(
        OUTPUT plugin_upbdefs_h plugin_upbdefs_c
        COMMAND ${PROTOBUF_PROTOC_EXECUTABLE} ${PROTOC_FLAGS} -I${upb_SOURCE_DIR} --plugin=${upb_BINARY_DIR}/upbc/protoc-gen-upbdefs --upbdefs_out=${upb_BINARY_DIR} ${upb_SOURCE_DIR}/google/protobuf/compiler/plugin.proto
        DEPENDS protoc-gen-upbdefs
)

add_custom_command(
        OUTPUT code_generator_request_upbdefs_h code_generator_request_upbdefs_c
        COMMAND ${PROTOBUF_PROTOC_EXECUTABLE} ${PROTOC_FLAGS} -I${upb_SOURCE_DIR} --plugin=${upb_BINARY_DIR}/upbc/protoc-gen-upbdefs --upbdefs_out=${upb_BINARY_DIR} ${upb_SOURCE_DIR}/upbc/code_generator_request.proto
        DEPENDS protoc-gen-upbdefs
)

set(UPBC_LIB_SRC
        code_generator_request_upb_c
        code_generator_request.c
        plugin_upbdefs_c
        code_generator_request_upbdefs_c
        file_layout.cc
        keywords.cc
        names.cc
        get_used_fields.c
        subprocess.cc
        upbdev.c
        upbc_so.c
)
add_library(upbc SHARED ${UPBC_LIB_SRC})
target_include_directories(upbc PRIVATE ${upb_SOURCE_DIR})
target_include_directories(upbc PRIVATE ${upb_BINARY_DIR})