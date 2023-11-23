// LFInteractive LLC. (c) 2020-2024 All Rights Reserved
#include "NetworkClient.h"
#include <chrono>
#include <cmath>
#include <tuple>
#include <filesystem>

struct UpdateData
{
	canl::NetworkUpdateMessage& message;
	canl::NetworkClient::UpdateCallback& callback;
	canl::HttpResponseMessage& response;
};

canl::NetworkClient::NetworkClient()
{
	this->curl = curl_easy_init();
}

canl::NetworkClient::~NetworkClient()
{
	this->close();
}

canl::HttpResponseMessage canl::NetworkClient::send(HttpRequestOptions options, UpdateCallback updateCallback /*= nullptr*/)
{
	curl_easy_setopt(this->curl, CURLOPT_URL, options.url.c_str());
	switch (options.method)
	{
		case GET:
			curl_easy_setopt(this->curl, CURLOPT_HTTPGET, 1L);
			break;
		case POST:
			curl_easy_setopt(this->curl, CURLOPT_POST, 1L);
			break;
		case PUT:
			curl_easy_setopt(this->curl, CURLOPT_PUT, 1L);
			break;
		case DELETE:
			curl_easy_setopt(this->curl, CURLOPT_CUSTOMREQUEST, "DELETE");
			break;
		case HEAD:
			curl_easy_setopt(this->curl, CURLOPT_CUSTOMREQUEST, "HEAD");
			break;
		case PATCH:
			curl_easy_setopt(this->curl, CURLOPT_CUSTOMREQUEST, "PATCH");
			break;
		default:
			break;
	}
	if (options.followRedirects)
	{
		curl_easy_setopt(this->curl, CURLOPT_FOLLOWLOCATION, 1L);
	}
	if (options.method != GET && !options.body.empty())
	{
		curl_easy_setopt(this->curl, CURLOPT_POSTFIELDS, options.body.c_str());
	}
	if (!options.headers.empty())
	{
		struct curl_slist* headers = NULL;
		for (auto& header : options.headers)
		{
			string headerString = header.first + ": " + header.second;
			headers = curl_slist_append(headers, headerString.c_str());
		}
		curl_easy_setopt(this->curl, CURLOPT_HTTPHEADER, headers);
	}
	HttpResponseMessage response;
	if (updateCallback != nullptr)
	{
		NetworkUpdateMessage message;
		if (!options.path.empty())
		{
			message.path = options.path;
			message.fileName = std::filesystem::path(message.path).filename().string();
		}
		message.bytesTotal = 0;
		message.bytesPerSecond = 0;
		UpdateData data = { message, updateCallback, response };
		curl_easy_setopt(this->curl, CURLOPT_WRITEDATA, &data);
		curl_easy_setopt(this->curl, CURLOPT_WRITEFUNCTION, [](void* contents, size_t size, size_t nmemb, void* userp)
		{
			if (userp)
			{
				// Cast the user pointer to the callback function
				auto data = (UpdateData*)userp;

				NetworkClient::UpdateCallback callback = data->callback;
				NetworkUpdateMessage message = data->message;
				HttpResponseMessage response = data->response;

				// Get the current time and calculate the elapsed time since the last callback
				auto currentTime = std::chrono::high_resolution_clock::now();
				auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - message.lastCallbackTime).count() / 1000.0;

				// Calculate the data size and update the message
				message.bytesReceived += size * nmemb;

				message.bytesPerSecond = static_cast<size_t>(std::ceil(static_cast<double>(message.bytesReceived) / elapsedTime));
				message.lastCallbackTime = currentTime;

				response.body += (char*)contents;

				(*callback)(message);
			}
			return size * nmemb;
		});
	}

	CURLcode code = curl_easy_perform(this->curl);
}

void canl::NetworkClient::close()
{
	curl_easy_cleanup(this->curl);
}