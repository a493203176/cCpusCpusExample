#pragma once

#include <string>

class XHttpResponse
{
public:
	bool SetRequest(std::string request);
	std::string GetHead();
	int Read(char * buf, int bufsize);
	XHttpResponse();
	~XHttpResponse();
private:
	unsigned  long  filesize = 0;
	FILE * fp = nullptr;
};

