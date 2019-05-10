#include "XTcp.h"
#ifdef _WIN64
#define WIN32
#endif
#ifdef WIN32
#include <Windows.h>
#define socklen_t int
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>

#define  closesocket close
#endif
#include <stdio.h>
#include<string.h>
#include<stdlib.h>

using namespace std;

XTcp::XTcp():port(0),sock(0)
{
#ifdef WIN32
	static bool first = true;
	if (true)
	{
		first = false;
		WSADATA ws;
		// wsastartup主要就是进行相应的socket库绑定
		// 使用2.2版本的Socket
		WSAStartup(MAKEWORD(2, 2), &ws);
	}
#endif
}


int XTcp::CreateSocket()
{
	/*
	protofamily：即协议域，又称为协议族（family）。常用的协议族有，AF_INET(IPV4)、AF_INET6(IPV6)、AF_LOCAL（或称AF_UNIX，Unix域socket）、AF_ROUTE等等。协议族决定了socket的地址类型，在通信中必须采用对应的地址，如AF_INET决定了要用ipv4地址（32位的）与端口号（16位的）的组合、AF_UNIX决定了要用一个绝对路径名作为地址。
	type：指定socket类型。常用的socket类型有，SOCK_STREAM、SOCK_DGRAM、SOCK_RAW、SOCK_PACKET、SOCK_SEQPACKET等等（socket的类型有哪些？）。
	protocol：故名思意，就是指定协议。常用的协议有，IPPROTO_TCP、IPPTOTO_UDP、IPPROTO_SCTP、IPPROTO_TIPC等，它们分别对应TCP传输协议、UDP传输协议、STCP传输协议、TIPC传输协议（这个协议我将会单独开篇讨论！）。
	*/
	// tcp连接
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1) {
		printf("create socket failed!\n");
	}
	//printf("[%d]\n", sock);
	return sock;
}

bool XTcp::Bind(unsigned short port)
{
	// 如果没有创建socket就创建一下
	if (sock <= 0)
		CreateSocket();
	//端口号、ip地址
	sockaddr_in saddr;
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(port); //转换默认x86小端
	saddr.sin_addr.s_addr = htonl(0); // 任意地址都可以访问

	if (::bind(sock, (sockaddr *)&saddr, sizeof(sockaddr)) != 0)
	{
		printf("bind port %d failed \n", port);
		return false;
	}
	printf("bind port %d succeed \n", port);

	listen(sock, 10);
	return true;
}

XTcp XTcp::Accept()
{
	XTcp tcp;
	sockaddr_in caddr;
	socklen_t len = sizeof(caddr);
	// 返回一个新的socket，用来单独给这个客户端单独通信的
	tcp.sock = accept(sock, (sockaddr *)&caddr, &len);
	if (tcp.sock <= 0) return tcp;
	char * ip = inet_ntoa(caddr.sin_addr);
	strcpy(tcp.ip, ip);
	tcp.port = ntohs(caddr.sin_port);

	printf("client ip: %s port:%d \n", tcp.ip, tcp.port);

	return tcp;
}

void XTcp::Close()
{
	if (sock <= 0) return;
	closesocket(sock);
}

int XTcp::Recv(char * buf, int bufsize)
{
	return recv(sock, buf, bufsize,0);
}
int XTcp::Send(const char *buf, int size)
{
	int s = 0; // 数据发送偏移量
	while (s != size)
	{
		int len = send(sock, buf + s, size - s, 0);
		if (len <= 0) break;
		s += len;
	}
	return s;
}


bool XTcp::Connect(const char * ip, unsigned short port, int timeoutms)
{
	if (sock <= 0)
		CreateSocket();

	sockaddr_in saddr;
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(port);
	saddr.sin_addr.s_addr = inet_addr(ip);
	SetBlock(false);
	if (connect(sock, (sockaddr *)&saddr, sizeof(saddr)) != 0) {
		fd_set fdset; // 句柄集
		timeval ts;
		ts.tv_sec = 0;
		ts.tv_usec = timeoutms * 1000;

		FD_ZERO(&fdset);
		FD_SET(sock, &fdset);

		if (select(sock + 1, 0, &fdset, 0, &ts) <= 0) {
			printf("connect timeout or error! \n");
			printf("connect %s:%d fauled error:%s \n", ip, port, strerror(errno));
			return false;
		}
	}
	printf("connect %s:%d succede \n", ip, port);
	SetBlock(true);
	return true;

}


bool XTcp::SetBlock(bool isblock)
{
	if (sock <= 0) return false;
#ifdef WIN32
	unsigned long  mode = 0; // 阻塞
	if (!isblock)
		mode = 1; // 非阻塞
	ioctlsocket(sock, FIONBIO, &mode);
#else
	int mode = fcntl(sock, F_GETFL, 0);
	if (mode < 0)
		return false;

	if (isblock) {
		mode &= ~(O_NONBLOCK);
	}
	else
	{
		mode |= O_NONBLOCK;
	}
	fcntl(sock, F_SETFL, mode);
#endif

	return true;
}

XTcp::~XTcp()
{
}
