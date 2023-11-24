// LFInteractive LLC. (c) 2020-2024 All Rights Reserved
#include "NetworkClient.h"
#include <stdio.h>
using namespace canl;
int main()
{
	auto client = new NetworkClient();
	HttpResponseMessage response = client->get("https://www.google.com");

	if (response.isSuccessStatusCode)
	{
		printf("Content: %s", response.body);
	}

	return 0;
}