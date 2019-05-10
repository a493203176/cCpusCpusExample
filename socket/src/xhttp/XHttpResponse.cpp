#include "XHttpResponse.h"
#include <string>
#include <regex>

using namespace std;

bool XHttpResponse::SetRequest(std::string request)
{
	string src = request;
	smatch m;
	//  /   /index.html  /ff 
	//string pattern = "^([A-Z]+) /([a-zA-Z0-9]*([.][a-zA-Z]*)?)[?]?(.*) HTTP/1";
	string pattern = "^([A-Z]+) /([a-zA-Z0-9]*([.][a-zA-Z]*)?)[?]?(.*) HTTP/1";
	regex e (pattern);
	regex_search(src,m,e);
	
	if (m.size() == 0) {
		printf("%s failed!\n",pattern.c_str());
		//Close();
		return false;
	}
	string type = m[1]; // m[0] 是整段匹配的字符串
	string path = "/";
	path += m[2];
	string filetype = m[3];
	string query = m[4];


	if (filetype.size() > 0) {
		filetype = filetype.substr(1,filetype.size() -1);
	}
	
	printf("type:[%s]\npath=[%s]\nfiletype:[%s]\nquery:[%s]\n",
		type.c_str(),
		path.c_str(),
		filetype.c_str(),
		query.c_str()
		);
	
	
	if( type != "GET") {
		printf("No Get\n");
		//Close();
		return false;
	}
	string filename = path;
	
	if (filename == "/")
	{
		filename = "/index.html";
	}
	string filepath = "www";
	filepath += filename;
	
	// 对php文件做处理
	// 1. php-cgi www/index.php > www/index.php.html
	// 2. php-cgi www/index.php id=1 name=xcj > www/index.php.html
	if (filetype == "php") {
				
		string cmd = "php-cgi ";
		cmd += filepath;
		cmd += " ";
		// query id=1&name=xcj
		// id=1 name=xcj
		// 参数不正常,会产生bug
		//query = query.replace(query.find("&"), 1, "");
		for (int i = 0; i< query.size(); i++)
		{
			if (query[i] == '&') query[i] = ' ';
		}
		cmd += query;
	
		cmd += " > ";
		filepath += ".html";
		cmd += filepath;
	
		printf("%s\n", cmd.c_str());
		system(cmd.c_str());
	}
	
	fp = fopen(filepath.c_str(),"rb");
	if (fp == NULL) {
		printf("open file %s failed\n",filepath.c_str());
		//Close();
		return false;
	}
	// 获取文件大小
	fseek(fp,0,SEEK_END);
	filesize = ftell(fp);
	fseek(fp,0,SEEK_SET);
	printf("file size is %ld \n",filesize);
	
	if (filetype == "php")
	{
		char c = 0;
		//\r\n\r\n 表示php头部
		int headsize = 0;
		while (fread(&c, 1, 1, fp) > 0)
		{
			headsize++;
			if (c == '\r')
			{
				fseek(fp, 2, SEEK_CUR);
				fread(&c, 1, 1, fp);
				headsize += 3;
				// bug: 这里必须在读一次,不然会误认为\r\n,每段的结尾
				if (c == '\n') {
					//printf("匹配成功");
					break;
				}
					
			}
		}
		filesize = filesize - headsize;
	}	
	return true;
}

std::string XHttpResponse::GetHead()
{
	// 回应http GET请求
	// 消息头
	string rmsg = "";
	rmsg = "HTTP/1.1 200 OK\r\n";
	rmsg += "Server: XHttp\r\n";
	rmsg += "Content-Type: text/html\r\n";
	rmsg += "Content-Length: ";
	char bsize[128] = { 0 };
	sprintf(bsize, "%ld", filesize);
	rmsg += bsize;
	// rmsg += "10\r\n";
	rmsg += "\r\n\r\n";
	return rmsg;

}
int XHttpResponse::Read(char * buf, int bufsize)
{
	//// 发送正文
	return fread(buf,1, bufsize,fp);
}


XHttpResponse::XHttpResponse()
{
}


XHttpResponse::~XHttpResponse()
{
}
