#include "XHttpServer.h"
#include <signal.h>

int main(int argc, char *argv[])
{
#ifdef WIN32
#else
	// 忽略这个信号
	signal(SIGPIPE, SIG_IGN);
#endif
	unsigned short port = 8080;
	if (argc > 1)
	{
		port = atoi(argv[1]);
	}
	XHttpServer server;
	server.Start(port);

	getchar();
	return 0;
}