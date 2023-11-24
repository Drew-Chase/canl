// LFInteractive LLC. (c) 2020-2024 All Rights Reserved
#pragma once
#include "HttpResponseMessage.h"
#include "HttpRequestOptions.h"
#include "NetworkUpdateMessage.h"
#include "json.hpp"
#include "curl.h"
#include <string>
using std::string;
using json = nlohmann::json;
namespace canl
{
	class NetworkClient
	{
	private:
		CURL* curl;
	public:
		typedef void(*UpdateCallback)(NetworkUpdateMessage);
		NetworkClient();
		~NetworkClient();
		HttpResponseMessage send(HttpRequestOptions options, UpdateCallback updateCalback = nullptr);
		HttpResponseMessage get(string url, UpdateCallback updateCalback = nullptr);
		HttpResponseMessage post(string url, UpdateCallback updateCalback = nullptr);
		HttpResponseMessage download(HttpRequestOptions options, string path, UpdateCallback updateCalback = nullptr);
		HttpResponseMessage download(string url, string path, UpdateCallback updateCalback = nullptr);
		string getAsString(string url);
		string getAsString(HttpRequestOptions options);
		json getAsJson(string url);
		json getAsJson(HttpRequestOptions options);

		//HttpResponseMessage sendAsync(HttpRequestOptions options, UpdateCallback updateCalback = nullptr);
		//HttpResponseMessage getAsync(string url, UpdateCallback updateCalback = nullptr);
		//HttpResponseMessage postAsync(string url, UpdateCallback updateCalback = nullptr);
		//HttpResponseMessage downloadAsync(HttpRequestOptions options, string path, UpdateCallback updateCalback = nullptr);
		//HttpResponseMessage downloadAsync(string url, string path, UpdateCallback updateCalback = nullptr);
		//string getAsStringAsync(string url);
		//string getAsStringAsync(HttpRequestOptions options);
		//json getAsJsonAsync(string url);
		//json getAsJsonAsync(HttpRequestOptions options);

		void close();
	};
}
