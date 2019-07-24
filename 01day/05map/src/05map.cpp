#include "../inc/05map.h"

Echo g_echo;
ExitFrame g_exit;
Cmd g_cmd;
OMng g_omng;

// ͨ�� AZinxHandler �̳�
IZinxMsg * Echo::InternelHandle(IZinxMsg & _oInput)
{
	//�������������׼���
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
	//û����һ������
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

// ͨ�� Ichannel �̳�
bool stdin_channel::Init()
{
	//�����ʼ����ֱ�ӷ���true��ʾ��ʼ���ɹ�
	return true;
}
//���ļ����ӱ�׼���������
 bool stdin_channel::ReadFd(std::string & _input)
{
	cin >> _input;
	return true;
}
//д�ļ�������Ҫ���׼����д���ݣ��ɺ���
 bool stdin_channel::WriteFd(std::string & _output)
{
	return false;
}
//������������ã��޲���
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
//��ȡ��һ��������,ָ��Ϊg_echo
 AZinxHandler * stdin_channel::GetInputNextStage(BytesMsg & _oInput)
{
	//���ش����ȡ�����ݵĶ��󣬷���g_echo����
	return &g_cmd;
}
 // ͨ�� Ichannel �̳�
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


