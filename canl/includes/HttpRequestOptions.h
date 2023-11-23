// LFInteractive LLC. (c) 2020-2024 All Rights Reserved
#pragma once
#include "HttpMethod.h"
#include <map>
#include <string>
using std::string;
using std::map;

namespace canl
{
	struct HttpRequestOptions
	{
		string url;
		HttpMethod method = GET;
		string body;
		map<string, string> headers;
		bool followRedirects = true;
		string path;
	};
}