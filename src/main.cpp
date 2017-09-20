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
#include <signal.h>

#include "HttpClient.h"
#include "HttpRequest.h"
#include "HttpResponse.h"

#include "log4z.h"
using namespace zsummer::log4z;

#include <atomic>

//static bool exit_loop = false;
//
//void sighandler(int) {
//	exit_loop = true;
//}

int main(int argc, char ** argv) {
	if (argc < 3)
		return -1;

//	::signal(SIGINT, sighandler);

	ILog4zManager::getInstance()->start();

	std::string s1(argv[1]);
	std::string c1(argv[2]);
	int c = atoi(c1.c_str());
	int i = 1;
	do {
		HttpRequest *request = new HttpRequest();
		request->setUrl(s1.c_str());
		request->setRequestType(HttpRequest::Type::emGET);

		clock_t t = clock();
		request->setResponseCallback(
				[i, t](HttpResponse* response) {
					clock_t t1 = clock();

					double t2 = ((double)(t1)-t)/CLOCKS_PER_SEC;

					long code = response->getResponseCode();
					if (code == 200) {
						std::string data = response->getResponseDataString();
						LOGFMTD("[%d] [t: %f] [code: %ld] [data: %s]", i, t2, code, data.c_str());
					} else {
						const char* err = response->getErrorBuffer();
						LOGFMTD("[%d] [t: %f] [code: %ld] [data: %s]", i,  t2, code, err);
					}
				});

		HttpClient::getInstance()->send(request);
//		HttpClient::getInstance()->sendImmediate(request);

//		usleep(100);
		i++;

	} while (i <= c);

	getchar();
	return 0;
}
