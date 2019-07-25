#include <list>

#include "../../inc/protocol/CmdPrsP.h"
#include "../../inc/role/EchoR.h"
#include "../../inc/role/ExitR.h"
#include "../../inc/role/OMngR.h"
#include "../../inc/CmdMsg.h"

CmdPrsP::CmdPrsP()
{
}

UserData * CmdPrsP::raw2request(std::string _szInput)
{
	CmdMsg* temp_msg = new CmdMsg;
	if ("exit" == _szInput) temp_msg->b_exit = true;
	else if ("open" == _szInput) temp_msg->b_open = true;
	else if ("close" == _szInput) temp_msg->b_open = false;
	else temp_msg->m_echo = _szInput;

	return temp_msg;
}

std::string * CmdPrsP::response2raw(UserData & _oUserData)
{
	GET_REF2DATA(CmdMsg, msg, _oUserData);
	return new std::string(msg.m_echo);
}

Irole * CmdPrsP::GetMsgProcessor(UserDataMsg & _oUserDataMsg)
{
	GET_REF2DATA(BytesMsg, byte, _oUserDataMsg);
	//std::list<Irole*> list_role = ZinxKernel::Zinx_GetAllRole();
	//for (Irole* role : list_role)
	//{
	//	if (nullptr != dynamic_cast<ExitR*>(role) &&
	//		"exit" == byte.szData)
	//		return dynamic_cast<ExitR*>(role);
	//	else if (nullptr != dynamic_cast<OMngR*>(role) &&
	//		("open" == byte.szData || "close" == byte.szData))
	//		return  dynamic_cast<OMngR*>(role);
	//	else if (nullptr != dynamic_cast<EchoR*>(role))
	//	{
	//		return  dynamic_cast<EchoR*>(role);
	//	}
	//}
	if (roleMap.end() != roleMap.find(byte.szData))
		return roleMap[byte.szData];
	else
		return roleMap["echo"];
}

Ichannel * CmdPrsP::GetMsgSender(BytesMsg & _oBytes)
{
	return ZinxKernel::Zinx_GetChannel_ByInfo("stdout_channel");
}


CmdPrsP::~CmdPrsP()
{
}


CmdPrsP CmdPrsP::s_cmdPrs;
CmdPrsP& CmdPrsP::getInstance()
{
	return s_cmdPrs;
}

void CmdPrsP::addRole(const std::string name, Irole* r)
{
	s_cmdPrs.roleMap[name] = r;
}
