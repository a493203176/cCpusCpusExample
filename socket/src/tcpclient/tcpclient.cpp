#include <XTcp.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char * argv[])
{
	XTcp client;
	client.CreateSocket();
	client.SetBlock(false);
	client.Connect("192.168.0.1", 8081,3000);
	client.Send("client", strlen("client") + 1);
	char buf[1024] = { 0 };
	client.Recv(buf, sizeof(buf));
	printf("%s \n", buf);
	getchar();
	return 0;
}