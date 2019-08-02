#include "../../inc/protocol/GameP.h"



GameP::GameP()
{
}


GameP::~GameP()
{
}

UserData * GameP::raw2request(std::string _szInput)
{
	return nullptr;
}

std::string * GameP::response2raw(UserData & _oUserData)
{
	return nullptr;
}

Irole * GameP::GetMsgProcessor(UserDataMsg & _oUserDataMsg)
{
	return nullptr;
}

Ichannel * GameP::GetMsgSender(BytesMsg & _oBytes)
{
	return nullptr;
}
