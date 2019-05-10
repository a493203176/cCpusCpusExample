#ifndef __XTCP_H__
#define __XTCP_H__


#ifdef WIN32
#ifdef XSOCKET_EXPORTS
#define XSOCKET_API __declspec(dllexport)
#else
#define XSOCKET_API __declspec(dllimport)
#endif
#else
#define XSOCKET_API
#endif

#include <string>


class XSOCKET_API XTcp
{
public:
	int CreateSocket();
	bool Bind(unsigned short port);
	XTcp Accept();
	void Close();
	int Recv(char * buf,int bufsize);
	int Send(const char *buf,int sendsize);
	bool Connect(const char * ip, unsigned short port, int timeoutms=1000);
	bool SetBlock(bool isblock);
	XTcp();
	virtual ~XTcp();

public:
	int sock;
	unsigned short port;
	char ip[16];
};

#endif