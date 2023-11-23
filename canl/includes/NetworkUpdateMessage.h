// LFInteractive LLC. (c) 2020-2024 All Rights Reserved
#pragma once
#include <string>
#include <chrono>
#include <NetworkClient.h>
using std::string;
namespace canl
{
	struct NetworkUpdateMessage
	{
		size_t bytesReceived;
		size_t bytesTotal;
		size_t bytesRemaining = bytesTotal - bytesReceived;
		size_t bytesPerSecond;
		std::chrono::high_resolution_clock::time_point lastCallbackTime;
		string path;
		string fileName;
		float percentage = (float)bytesReceived / (float)bytesTotal;
	};
}