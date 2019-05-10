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
		// wsastartup��Ҫ���ǽ�����Ӧ��socket���
		// ʹ��2.2�汾��Socket
		WSAStartup(MAKEWORD(2, 2), &ws);
	}
#endif
}


int XTcp::CreateSocket()
{
	/*
	protofamily����Э�����ֳ�ΪЭ���壨family�������õ�Э�����У�AF_INET(IPV4)��AF_INET6(IPV6)��AF_LOCAL�����AF_UNIX��Unix��socket����AF_ROUTE�ȵȡ�Э���������socket�ĵ�ַ���ͣ���ͨ���б�����ö�Ӧ�ĵ�ַ����AF_INET������Ҫ��ipv4��ַ��32λ�ģ���˿ںţ�16λ�ģ�����ϡ�AF_UNIX������Ҫ��һ������·������Ϊ��ַ��
	type��ָ��socket���͡����õ�socket�����У�SOCK_STREAM��SOCK_DGRAM��SOCK_RAW��SOCK_PACKET��SOCK_SEQPACKET�ȵȣ�socket����������Щ������
	protocol������˼�⣬����ָ��Э�顣���õ�Э���У�IPPROTO_TCP��IPPTOTO_UDP��IPPROTO_SCTP��IPPROTO_TIPC�ȣ����Ƿֱ��ӦTCP����Э�顢UDP����Э�顢STCP����Э�顢TIPC����Э�飨���Э���ҽ��ᵥ����ƪ���ۣ�����
	*/
	// tcp����
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1) {
		printf("create socket failed!\n");
	}
	//printf("[%d]\n", sock);
	return sock;
}

bool XTcp::Bind(unsigned short port)
{
	// ���û�д���socket�ʹ���һ��
	if (sock <= 0)
		CreateSocket();
	//�˿ںš�ip��ַ
	sockaddr_in saddr;
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(port); //ת��Ĭ��x86С��
	saddr.sin_addr.s_addr = htonl(0); // �����ַ�����Է���

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
	// ����һ���µ�socket����������������ͻ��˵���ͨ�ŵ�
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
	int s = 0; // ���ݷ���ƫ����
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
		fd_set fdset; // �����
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
	unsigned long  mode = 0; // ����
	if (!isblock)
		mode = 1; // ������
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
