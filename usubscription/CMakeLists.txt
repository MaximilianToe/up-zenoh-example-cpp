#  SPDX-FileCopyrightText: 2025 Contributors to the Eclipse Foundation
#
#  See the NOTICE file(s) distributed with this work for additional
#  information regarding copyright ownership.
#
#  This program and the accompanying materials are made available under the
#  terms of the Apache License Version 2.0 which is available at
#  https://www.apache.org/licenses/LICENSE-2.0
#
#  SPDX-License-Identifier: Apache-2.0
#
cmake_minimum_required(VERSION 3.20)
project(usubscription VERSION 0.1.0 LANGUAGES CXX)

find_package(spdlog REQUIRED)
find_package(up-cpp REQUIRED)
find_package(up-transport-zenoh-cpp REQUIRED)

add_definitions(-DSPDLOG_FMT_EXTERNAL)

# rpc client
add_executable(usubscription src/main_usubscription_client.cpp)
target_link_libraries(usubscription
  PUBLIC
    spdlog::spdlog
    up-cpp::up-cpp
    up-core-api::up-core-api
    up-transport-zenoh-cpp::up-transport-zenoh-cpp)
target_include_directories(usubscription
  PRIVATE
    include)

