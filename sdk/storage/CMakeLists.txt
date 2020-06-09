# Copyright (c) Microsoft Corporation. All rights reserved.
# SPDX-License-Identifier: MIT

cmake_minimum_required (VERSION 3.12)

project (azure-storage LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(BUILD_STORAGE_SAMPLES "Build sample codes" ON)

set (AZURE_STORAGE_BLOB_HEADER
    inc/common/storage_common.hpp
    inc/common/storage_credential.hpp
    inc/common/storage_url_builder.hpp
    inc/common/common_headers_request_policy.hpp
    inc/common/shared_key_policy.hpp
    inc/common/crypt.hpp
    inc/blobs/blob.hpp
    inc/blobs/blob_client.hpp
    inc/blobs/block_blob_client.hpp
    inc/blobs/blob_container_client.hpp
    inc/blobs/blob_client_options.hpp
    inc/blobs/blob_container_client_options.hpp
    inc/blobs/internal/protocol/blob_rest_client.hpp
)

set (AZURE_STORAGE_DATALAKE_HEADER
    external/json.hpp
    inc/datalake/protocol/datalake_rest_client.hpp
)

set (AZURE_STORAGE_BLOB_SOURCE
    src/blobs/blob_client.cpp
    src/blobs/block_blob_client.cpp
    src/blobs/blob_container_client.cpp
    src/common/storage_credential.cpp
    src/common/storage_url_builder.cpp
    src/common/common_headers_request_policy.cpp
    src/common/shared_key_policy.cpp
    src/common/crypt.cpp
)

set (AZURE_STORAGE_DATALAKE_SOURCE
)

set(AZURE_STORAGE_HEADER
    ${AZURE_STORAGE_BLOB_HEADER}
    ${AZURE_STORAGE_DATALAKE_HEADER}
)

set(AZURE_STORAGE_SOURCE
    ${AZURE_STORAGE_BLOB_SOURCE}
    ${AZURE_STORAGE_DATALAKE_SOURCE}
)

add_library(azure-storage ${AZURE_STORAGE_HEADER} ${AZURE_STORAGE_SOURCE})

find_package(LibXml2 REQUIRED)

target_include_directories(azure-storage PUBLIC ${LIBXML2_INCLUDE_DIR} $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc> $<INSTALL_INTERFACE:include/azure_storage>)

target_link_libraries(azure-storage azure-core ${LIBXML2_LIBRARIES})

if(MSVC)
    target_link_libraries(azure-storage bcrypt)
    target_compile_definitions(azure-storage PRIVATE NOMINMAX)
else()
    find_package(OpenSSL REQUIRED)
    target_link_libraries(azure-storage OpenSSL::SSL OpenSSL::Crypto)
endif()

# Set version numbers centralized
set(AZURE_STORAGE_VERSION_MAJOR 0)
set(AZURE_STORAGE_VERSION_MINOR 1)
set(AZURE_STORAGE_VERSION_REVISION 0)

#install(DIRECTORY include/ DESTINATION include)
#install(TARGETS azure-storage
#    ARCHIVE DESTINATION lib
#    LIBRARY DESTINATION lib
#    RUNTIME DESTINATION bin)

if(BUILD_STORAGE_SAMPLES)
  add_subdirectory(sample)
endif()

if(BUILD_TESTING)
  add_subdirectory(test)
endif()

# make sure that users can consume the project as a library.
add_library (azure::storage ALIAS azure-storage)