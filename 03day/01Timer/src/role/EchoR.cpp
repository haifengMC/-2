#include "../../inc/role/EchoR.h"
#include "../../inc/protocol/CmdPrsP.h"
#include "../../inc/CmdMsg.h"


EchoR::EchoR()
{
}


EchoR::~EchoR()
{
}

bool EchoR::Init()
{
	return true;
}

UserData * EchoR::ProcMsg(UserData & _poUserData)
{
	GET_REF2DATA(CmdMsg, output, _poUserData);
	//Ichannel* stdout_c = 
	//	ZinxKernel::Zinx_GetChannel_ByInfo("stdout_channel");
	//if (nullptr == stdout_c)
	//ZinxKernel::Zinx_SendOut(msg.m_echo, *stdout_c);
	CmdMsg* msg = new CmdMsg;
	msg->m_echo = output.m_echo;
	ZinxKernel::Zinx_SendOut(*msg, CmdPrsP::getInstance());

	return nullptr;
}

void EchoR::Fini()
{
}
