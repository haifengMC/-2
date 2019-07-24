#pragma once
#include <iostream>
#include <zinx.h>

using namespace std;


//2.创建数据处理类echo-->继承类AZinxHandler
class echo : public AZinxHandler
{
	// 通过 AZinxHandler 继承
	virtual IZinxMsg * InternelHandle(IZinxMsg & _oInput) override
	{
		//将数据输出到标准输出
		GET_REF2DATA(BytesMsg, byte, _oInput);
		cout << byte.szData << endl;

		return nullptr;
	}

	virtual AZinxHandler * GetNextHandler(IZinxMsg & _oNextMsg) override
	{
		//没有下一个环节
		return nullptr;
	}

};
echo g_echo;

//3.创建IO通道类stdin_channel-->继承Ichannel类
class stdin_channel : public Ichannel
{
	// 通过 Ichannel 继承
	virtual bool Init() override
	{
		//无需初始化，直接返回true表示初始化成功
		return true;
	}
	//读文件，从标准输入读数据
	virtual bool ReadFd(std::string & _input) override
	{
		cin >> _input;
		return true;
	}
	//写文件，不需要向标准输入写内容，可忽略
	virtual bool WriteFd(std::string & _output) override
	{
		return false;
	}
	//操作结束后调用，无操作
	virtual void Fini() override
	{
	}
	virtual int GetFd() override
	{
		return STDIN_FILENO;
	}
	virtual std::string GetChannelInfo() override
	{
		return "stdin_channel";
	}
	//获取下一个处理环节,指定为g_echo
	virtual AZinxHandler * GetInputNextStage(BytesMsg & _oInput) override
	{
		//返回处理读取到数据的对象，返回g_echo对象
		return &g_echo;
	}
};
