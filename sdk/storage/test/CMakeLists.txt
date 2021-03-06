# Copyright (c) Microsoft Corporation. All rights reserved.
# SPDX-License-Identifier: MIT

cmake_minimum_required (VERSION 3.15)

add_executable (
     azure-storage-test
     test_base.hpp
     test_base.cpp
     blobs/blob_service_client_test.cpp
     blobs/blob_container_client_test.hpp
     blobs/blob_container_client_test.cpp
     blobs/block_blob_client_test.hpp
     blobs/block_blob_client_test.cpp
     blobs/append_blob_client_test.hpp
     blobs/append_blob_client_test.cpp
     blobs/page_blob_client_test.hpp
     blobs/page_blob_client_test.cpp
     datalake/service_client_test.hpp
     datalake/service_client_test.cpp
     datalake/file_system_client_test.hpp
     datalake/file_system_client_test.cpp
     datalake/path_client_test.hpp
     datalake/path_client_test.cpp
     main.cpp
    )

target_include_directories(azure-storage-test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(azure-storage-test PRIVATE azure-storage)

if (MSVC)
    target_compile_options(azure-storage-test PRIVATE /wd6326 /wd26495 /wd26812)
endif()

add_gtest(azure-storage-test)
