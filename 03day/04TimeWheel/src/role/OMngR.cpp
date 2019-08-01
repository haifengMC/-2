#include "../../inc/role/OMngR.h"
#include "../../inc/protocol/CmdMsg.h"


OMngR::OMngR()
{
}


OMngR::~OMngR()
{
}

bool OMngR::Init()
{
	return true;
}

UserData * OMngR::ProcMsg(UserData & _poUserData)
{
	GET_REF2DATA(CmdMsg, msg, _poUserData);

	if (NULL == stdoutC)
		stdoutC = ZinxKernel::Zinx_GetChannel_ByInfo("stdout_channel");
	if (msg.b_open)
	{
		ZinxKernel::Zinx_Add_Channel(*stdoutC);
	}
	else
	{
		ZinxKernel::Zinx_Del_Channel(*stdoutC);
	}
	return nullptr;
}

void OMngR::Fini()
{
}
