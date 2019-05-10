#include "XUdp.h"
#include <iostream>
#ifdef WIN32
#include <Windows.h>
#define socklen_t int
#else
#include <sys/types.h>         
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#endif
using namespace std;

int XUdp::CreateSocket()
{
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock <= 0) {
		cout << "socket create failed!" << endl;
		return -1;
	}
	return sock;
}

bool XUdp::Bind(unsigned short port)
{
	if (sock <= 0)
		CreateSocket();
	sockaddr_in  saddr;
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(port);
	saddr.sin_addr.s_addr = htonl(0);
	if (::bind(sock, (sockaddr*)&saddr, sizeof(saddr)) != 0)
	{
		printf("bind port %d failed!\n", port);
		return false;
	}
	printf("bind port %d success!\n", port);
	listen(sock, 10);
	return true;
}
void XUdp::Close()
{
	if (sock <= 0) return;
	closesocket(sock);
	if (addr)
	{
		delete addr;
	}
	addr = 0;
	sock = 0;
}
int XUdp::Recv(char * buf, int bufsize)
{
	if (sock <= 0)return 0;
	if (addr == 0)
	{
		addr = new sockaddr_in();
	}
	socklen_t len = sizeof(sockaddr_in);
	int re = recvfrom(sock, buf, bufsize, 0, (sockaddr*)addr, &len);
	return re;
}
int XUdp::Send(const char *buf, int sendsize)
{
	socklen_t len = sizeof(sockaddr_in);
	return sendto(sock, buf, sendsize, 0, (sockaddr *)addr, len);
}


XUdp::XUdp()
{
#ifdef WIN32
	static bool first = true;
	if (first)
	{
		first = false;
		WSADATA ws;
		WSAStartup(MAKEWORD(2, 2), &ws);
	}
#endif

	memset(ip, 0, sizeof(ip));
}


XUdp::~XUdp()
{
}
