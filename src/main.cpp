/*
 * main.cpp
 *
 *  Created on: Dec 22, 2016
 *      Author: root
 */

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <unistd.h>

#include "HttpClient.h"
#include "HttpRequest.h"
#include "HttpResponse.h"

#include <log4z/log4z.h>
using namespace zsummer::log4z;

int main(int argc, char ** argv) {
	ILog4zManager::getInstance()->start();

	do {
		HttpRequest *request = new HttpRequest();
		request->setUrl("www.baidu.com");
		request->setRequestType(HttpRequest::Type::emGET);

		request->setResponseCallback([](HttpResponse* response) {
			long code = response->getResponseCode();
			if (code == 200) {
				std::string data = response->getResponseDataString();
				LOGD(data);
			} else {
				const char* err = response->getErrorBuffer();
				LOGD(err);
			}
		});

		HttpClient::getInstance()->send(request);
//		HttpClient::getInstance()->sendImmediate(request);

		sleep(1);

	} while (1);

	getchar();

	return 0;
}
