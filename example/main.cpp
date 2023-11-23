// LFInteractive LLC. (c) 2020-2024 All Rights Reserved
#include "NetworkClient.h"
#include <stdio.h>
using namespace canl;
int main()
{
	auto client = new NetworkClient();
	HttpResponseMessage response = client->get("https://www.google.com", [](NetworkUpdateMessage message)
	{
		printf("Bytes received: %d\n", message.bytesReceived);
		printf("Bytes total: %d\n", message.bytesTotal);
		printf("Bytes remaining: %d\n", message.bytesRemaining);
		printf("Bytes per second: %d\n", message.bytesPerSecond);
		printf("Last callback time: %d\n", message.lastCallbackTime);
		printf("Path: %s\n", message.path.c_str());
		printf("File name: %s\n", message.fileName.c_str());
		printf("Percentage: %d\n", message.percentage);
	});

	if (response.isSuccessStatusCode)
	{
		printf("Content: %s", response.body);
	}

	return 0;
}