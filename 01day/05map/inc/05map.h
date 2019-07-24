#pragma once
#include <iostream>
#include <zinx.h>
#include <map>

using namespace std;

//2.1.创建数据处理类Echo-->继承类AZinxHandler
class Echo : public AZinxHandler
{
	// 通过 AZinxHandler 继承
	virtual IZinxMsg * InternelHandle(IZinxMsg & _oInput) override;
	virtual AZinxHandler * GetNextHandler(IZinxMsg & _oNextMsg) override;
};
extern Echo g_echo;

//2.2.创建数据处理类ExitFrame-->继承类AZinxHandler
class ExitFrame : public AZinxHandler
{
	// 通过 AZinxHandler 继承
	virtual IZinxMsg * InternelHandle(IZinxMsg & _oInput) override;
	virtual AZinxHandler * GetNextHandler(IZinxMsg & _oNextMsg) override;
};
extern ExitFrame g_exit;

//2.3.创建数据处理类Cmd-->继承类AZinxHandler
class Cmd : public AZinxHandler
{
	map<string, AZinxHandler*> cmds;
	// 通过 AZinxHandler 继承
	virtual IZinxMsg * InternelHandle(IZinxMsg & _oInput) override;
	virtual AZinxHandler * GetNextHandler(IZinxMsg & _oNextMsg) override;
public:
	//Cmd();
	void add_handle(const string& s, AZinxHandler* h);
};
extern Cmd g_cmd;

//2.4.创建数据处理类OMng-->继承类AZinxHandler
class OMng : public AZinxHandler
{
	Ichannel* stdout_channel = nullptr;
	// 通过 AZinxHandler 继承
	virtual IZinxMsg * InternelHandle(IZinxMsg & _oInput) override;
	virtual AZinxHandler * GetNextHandler(IZinxMsg & _oNextMsg) override;
};
extern OMng g_omng;

//3.1.创建IO通道类stdin_channel-->继承Ichannel类
class stdin_channel : public Ichannel
{
	// 通过 Ichannel 继承
	virtual bool Init() override;
	//读文件，从标准输入读数据
	virtual bool ReadFd(std::string & _input) override;
	//写文件，不需要向标准输入写内容，可忽略
	virtual bool WriteFd(std::string & _output) override;
	//操作结束后调用，无操作
	virtual void Fini() override;
	virtual int GetFd() override;
	virtual std::string GetChannelInfo() override;
	//获取下一个处理环节,指定为g_echo
	virtual AZinxHandler * GetInputNextStage(BytesMsg & _oInput) override;
};

//3.2.创建IO通道类stdout_channel-->继承Ichannel
class stdout_channel : public Ichannel
{
	// 通过 Ichannel 继承
	virtual bool Init() override;
	virtual bool ReadFd(std::string & _input) override;
	virtual bool WriteFd(std::string & _output) override;
	virtual void Fini() override;
	virtual int GetFd() override;
	virtual std::string GetChannelInfo() override;
	virtual AZinxHandler * GetInputNextStage(BytesMsg & _oInput) override;
};
