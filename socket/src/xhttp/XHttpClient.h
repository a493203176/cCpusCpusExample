#pragma once

#include "XTcp.h"
#include "XHttpResponse.h"

class XHttpClient
{
public:
	XHttpClient();
	~XHttpClient();
	XTcp client;
	bool Start(XTcp client);
	void Main();
	void  Close();
	XHttpResponse res;
};

