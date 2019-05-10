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

int main(int argc, char * argv[]) 
{
	unsigned short port = 8080;
	if (argc > 1) {
		port = atoi(argv[1]);
	}
#ifdef WIN32
	WSADATA ws;
	WSAStartup(MAKEWORD(2, 2),&ws);
#endif
	int sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock <= 0) {
		cout << "create socket failed !" << endl;
		return -1;
	}

	sockaddr_in saddr;
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(port);
	saddr.sin_addr.s_addr = inet_addr("127.0.0.1");


	int len = sendto(sock, "12345", strlen("12345") + 1, 0, (sockaddr *)&saddr, sizeof(saddr));
	cout << "send to is " << len << endl;
	char buf[10240] = { 0 };
	// 客户端知道服务器的地址,就不用传递地址了
	recvfrom(sock, buf, sizeof(buf)-1,0, 0, 0);
	cout << buf << endl;
	getchar();
	return 0;
}