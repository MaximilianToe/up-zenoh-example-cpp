//  SPDX-FileCopyrightText: 2025 Contributors to the Eclipse Foundation
//
//  See the NOTICE file(s) distributed with this work for additional
//  information regarding copyright ownership.
//
//  This program and the accompanying materials are made available under the
//  terms of the Apache License Version 2.0 which is available at
//  https://www.apache.org/licenses/LICENSE-2.0
//
//  SPDX-License-Identifier: Apache-2.0
//

#include <spdlog/spdlog.h>
#include <unistd.h>
#include <up-cpp/communication/RpcClient.h>
#include <up-cpp/client/usubscription/v3/RpcClientUSubscription.h>
#include <up-cpp/client/usubscription/v3/RequestBuilder.h>
#include <up-transport-zenoh-cpp/ZenohUTransport.h>

#include <chrono>
#include <csignal>
#include <iostream>

#include "common.h"

using namespace uprotocol::v1;
using namespace uprotocol::communication;
using namespace uprotocol::datamodel::builder;
using ZenohUTransport = uprotocol::transport::ZenohUTransport;
using RpcClientUSubscription = uprotocol::core::usubscription::v3::RpcClientUSubscription;
using RequestBuilder  = uprotocol::core::usubscription::v3::RequestBuilder;

bool gTerminate = false;

void signalHandler(int signal) {
	if (signal == SIGINT) {
		std::cout << "Ctrl+C received. Exiting..." << std::endl;
		gTerminate = true;
	}
}

/* The sample RPC client applications demonstrates how to send RPC requests and
 * wait for the response
 */
int main(int argc, char** argv) {

	if (argc < 2) {
		std::cout << "No Zenoh config has been provided" << std::endl;
		std::cout << "Usage: usubscription_client <config_file>" << std::endl;
		return 1;
	}

	signal(SIGINT, signalHandler);

	UUri source = getUUri(0);

	auto transport = std::make_shared<ZenohUTransport>(source, argv[1]);
	RpcClientUSubscription usubscription_client(transport);
	RequestBuilder request_builder;

	UUri test_topic = getUUri(12);
	auto subscription_request = request_builder.buildSubscriptionRequest(test_topic);

	spdlog::info("Sending subscription request: {}", subscription_request.DebugString());

	auto response_or_status = usubscription_client.subscribe(subscription_request);

	if (!response_or_status.has_value()) {
		spdlog::error("Failed to subscribe to topic: {}", response_or_status.error().DebugString());
		return 1;
	}
	spdlog::info("Subscription response: {}", response_or_status.value().DebugString());
	// while (!response_or_status.has_value() && !gTerminate) {
	// 	spdlog::error("Failed to subscribe to topic: {}", response_or_status.error().DebugString());
	// 	sleep(1);
	// 	usubscription_client.subscribe(subscription_request);
	// }

	return 0;
}
