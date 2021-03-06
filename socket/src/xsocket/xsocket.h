// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 XSOCKET_EXPORT
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// XSOCKET_API 函数视为自 DLL 导入，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifdef XSOCKET_EXPORTS
#define XSOCKET_API __declspec(dllexport)
#else
#define XSOCKET_API __declspec(dllimport)
#endif

// 此类导出自 xsocket.dll
class XSOCKET_API Cxsocket {
public:
	Cxsocket(void);
	// TODO:  在此添加您的方法。
};

extern XSOCKET_API int nxsocket;

XSOCKET_API int fnxsocket(void);
