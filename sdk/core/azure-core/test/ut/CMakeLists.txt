# Copyright (c) Microsoft Corporation. All rights reserved.
# SPDX-License-Identifier: MIT

cmake_minimum_required (VERSION 3.12)

set(TARGET_NAME "azure-core-test")

project (${TARGET_NAME} LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable (
     ${TARGET_NAME}
     main.cpp
     nullable.cpp
     http.cpp
     string.cpp)

target_link_libraries(${TARGET_NAME} PRIVATE azure-core)
add_gtest(${TARGET_NAME})

