#include <stdlib.h>
#include "XTcp.h"
#include <thread>
#include <string.h>
 #include <sys/epoll.h>

//Ïß³ÌÈë¿ÚÀà
class TcpThread
{
public:
	void Main()
	{
		char buf[1024] = { 0 };
		for (;;)
		{
			int recvlen = client.Recv(buf, sizeof(buf) - 1);
			if (recvlen <= 0) break;
			buf[recvlen] = '\0';

			if (strstr(buf, "quit") != NULL)
			{
				char re[] = "quit success!\n";
				client.Send(re, strlen(re) + 1);
				break;
			}
			int sendlen = client.Send("ok\n", 4);
			printf("recv %s\n", buf);
		}
		client.Close();
		delete this;
	}
	XTcp client;
};

int main(int argc, char *argv[])
{
	unsigned short port = 8080;
	if (argc > 1)
	{
		port = atoi(argv[1]);
	}
	XTcp server;
	server.CreateSocket();
	server.Bind(port);

	int epollfd,nfds;
	epoll_event events[20],ev;

	epollfd = epoll_create(10);
	if (epollfd < 0) {
		printf("epoll_create error");
		return epollfd;
	}
	ev.events = EPOLLIN | EPOLLET;
	ev.data.fd = server.sock;

	epoll_ctl(epollfd,EPOLL_CTL_ADD,server.sock,&ev);

	char buf[1024] = {0};
	const char * msg = "HTTP/1.1 200 OK\r\nContent-Length: 1\r\n\r\nX";
	int size = strlen(msg)+1;
	server.SetBlock(false);
	for (;;)
	{
		nfds = epoll_wait(epollfd,events,20,500);

		for(int i = 0 ; i < nfds; i++) {
			if (events[i].data.fd == server.sock) {
				for(;;) 
				{
					XTcp client = server.Accept();
					if (client.sock <=0 ) break;
					ev.events = EPOLLIN | EPOLLET;
					ev.data.fd = client.sock;
					client.SetBlock(false);
					epoll_ctl(epollfd,EPOLL_CTL_ADD,client.sock,&ev);
				}
			}
			else 
			{
				XTcp client;
				client.sock = events[i].data.fd;
				client.Recv(buf,sizeof(buf));
				client.Send(msg,size);
				epoll_ctl(epollfd,EPOLL_CTL_DEL,client.sock,&ev);// 这个不要传0进去,有的内核版本会出错
				client.Close();
			}
		}

		// XTcp client = server.Accept();
		// TcpThread *th = new TcpThread();
		// th->client = client;
		// //´´½¨Ïß³Ì
		// std::thread sth(&TcpThread::Main, th);

		//ÊÍ·Å¸¸Ïß³ÌÓµÓÐµÄ×ÓÏß³Ì×ÊÔ´
		// sth.detach();
	}
	server.Close();
	getchar();
	return 0;
}