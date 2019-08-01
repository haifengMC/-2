#include "../../inc/protocol/TimeoutDisprP.h"
#include "../../inc/protocol/TimeoutMsg.h"

#include <iostream>

using namespace std;


TimeoutDisprP::TimeoutDisprP()
{
}


TimeoutDisprP::~TimeoutDisprP()
{
}

TimeoutDisprP TimeoutDisprP::td;
TimeoutDisprP & TimeoutDisprP::getInstance()
{
	return td;
}


UserData * TimeoutDisprP::raw2request(std::string _szInput)
{
	TimeoutMsg* tm = new TimeoutMsg;
	this->ptt = *(TimeoutTaskR**)_szInput.data();
	tm->ptt = ptt;

	return tm;
}

std::string * TimeoutDisprP::response2raw(UserData & _oUserData)
{
	return nullptr;
}

Irole * TimeoutDisprP::GetMsgProcessor(UserDataMsg & _oUserDataMsg)
{
	return ptt;
}

Ichannel * TimeoutDisprP::GetMsgSender(BytesMsg & _oBytes)
{
	return nullptr;
}
