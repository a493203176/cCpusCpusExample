#include "XUdp.h"
#include <iostream>
#include <regex>
#include <string>
using namespace std;
int main(int argc,char *argv[])
{
	unsigned short port = 514;
	XUdp syslog;
	if (!syslog.Bind(port))
	{
		return -1;
	}
	char buf[2000] = { 0 };
	for (;;)
	{
		//接收linux发送的日志
		int len = syslog.Recv(buf, sizeof(buf));
		if (len <= 0)
		{
			continue;
		}
		buf[len] = '\0';
		//Failed password for xcj from 192.168.3.76 port 16939 ssh2
		string src = buf;
		string p = "Failed password for ([a-zA-Z0-9]+) from ([0-9.]+)";
		regex r(p);
		smatch mas;
		//分析日志内容
		regex_search(src, mas, r);
		if (mas.size() > 0)
		{
			cout << "Warning: User " << mas[1] << "@" << mas[2] << "login failed!" << endl;
		}
	}
	return 0;
}