#include "../inc/05map.h"

Echo g_echo;
ExitFrame g_exit;
Cmd g_cmd;
OMng g_omng;

// 通过 AZinxHandler 继承
IZinxMsg * Echo::InternelHandle(IZinxMsg & _oInput)
{
	//将数据输出到标准输出
	GET_REF2DATA(BytesMsg, byte, _oInput);
	//cout << byte.szData << endl;
	//if ("exit" == byte.szData)
	//	ZinxKernel::Zinx_Exit();
	Ichannel* poutstd =
		ZinxKernel::Zinx_GetChannel_ByInfo("stdout_channel");
	//cout << poutstd << endl;
	if (nullptr != poutstd)
		ZinxKernel::Zinx_SendOut(byte.szData, *poutstd);

	return nullptr;
}

AZinxHandler * Echo::GetNextHandler(IZinxMsg & _oNextMsg)
{
	//没有下一个环节
	return nullptr;
}

IZinxMsg * ExitFrame::InternelHandle(IZinxMsg & _oInput)
{
	ZinxKernel::Zinx_Exit();
	return nullptr;
}

AZinxHandler * ExitFrame::GetNextHandler(IZinxMsg & _oNextMsg)
{
	return nullptr;
}

IZinxMsg * Cmd::InternelHandle(IZinxMsg & _oInput)
{
	GET_REF2DATA(BytesMsg, byte, _oInput);
	return new BytesMsg(byte);
}

AZinxHandler * Cmd::GetNextHandler(IZinxMsg & _oNextMsg)
{
	GET_REF2DATA(BytesMsg, byte, _oNextMsg);
	if ("exit" == byte.szData)return &g_exit;
	else if ("open" == byte.szData ||
		"close" == byte.szData)return &g_omng;
	else return &g_echo;
}

IZinxMsg * OMng::InternelHandle(IZinxMsg & _oInput)
{
	GET_REF2DATA(BytesMsg, byte, _oInput);
	if (nullptr == stdout_channel)
		stdout_channel = 
			ZinxKernel::Zinx_GetChannel_ByInfo("stdout_channel");
	if ("open" == byte.szData)
		ZinxKernel::Zinx_Add_Channel(*stdout_channel);
	else ZinxKernel::Zinx_Del_Channel(*stdout_channel);

	return nullptr;
}

AZinxHandler * OMng::GetNextHandler(IZinxMsg & _oNextMsg)
{
	return nullptr;
}

// 通过 Ichannel 继承
bool stdin_channel::Init()
{
	//无需初始化，直接返回true表示初始化成功
	return true;
}
//读文件，从标准输入读数据
 bool stdin_channel::ReadFd(std::string & _input)
{
	cin >> _input;
	return true;
}
//写文件，不需要向标准输入写内容，可忽略
 bool stdin_channel::WriteFd(std::string & _output)
{
	return false;
}
//操作结束后调用，无操作
 void stdin_channel::Fini()
{
}
 int stdin_channel::GetFd()
{
	return STDIN_FILENO;
}
 std::string stdin_channel::GetChannelInfo()
{
	return "stdin_channel";
}
//获取下一个处理环节,指定为g_echo
 AZinxHandler * stdin_channel::GetInputNextStage(BytesMsg & _oInput)
{
	//返回处理读取到数据的对象，返回g_echo对象
	return &g_cmd;
}
 // 通过 Ichannel 继承
 bool stdout_channel::Init()
 {

	 return true;
 }

 bool stdout_channel::ReadFd(std::string & _input)
 {

	 return false;
 }

 bool stdout_channel::WriteFd(std::string & _output)
 {
	 cout << _output << endl;

	 return true;
 }

 void stdout_channel::Fini()
 {
 }

 int stdout_channel::GetFd()
 {

	 return STDOUT_FILENO;
 }

 std::string stdout_channel::GetChannelInfo()
 {

	 return "stdout_channel";
 }

 AZinxHandler * stdout_channel::GetInputNextStage(BytesMsg & _oInput)
 {

	 return nullptr;
 }


