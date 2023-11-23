// LFInteractive LLC. (c) 2020-2024 All Rights Reserved
#pragma once
#include "HttpRequestOptions.h"
#include <string>
#include <map>
using std::string;
using std::map;

namespace canl
{
	struct HttpResponseMessage
	{
		int statusCode;
		string body;
		map<string, string> headers;
		bool isSuccessStatusCode = statusCode >= 200 && statusCode < 300;
		string reasonPhrase;
		HttpRequestOptions requestOptions;
	};
}