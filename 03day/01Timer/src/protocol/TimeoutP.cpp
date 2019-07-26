#include "../../inc/protocol/TimeoutP.h"

using namespace std;

TimeoutP::TimeoutP()
{
}

TimeoutP::~TimeoutP()
{
}

TimeoutP TimeoutP::s_timeout;

TimeoutP & TimeoutP::getInstance()
{
	return s_timeout;
}

UserData * TimeoutP::raw2request(std::string _szInput)
{
	cout << *(uint64_t*)_szInput.data() << endl;

	return (UserData *)new uint64_t(*(uint64_t*)_szInput.data());
}

std::string * TimeoutP::response2raw(UserData & _oUserData)
{
	return nullptr;
}

Irole * TimeoutP::GetMsgProcessor(UserDataMsg & _oUserDataMsg)
{
	cout << "[" << *(uint64_t*)_oUserDataMsg.szData.data() << "]" << endl;
	return nullptr;
}

Ichannel * TimeoutP::GetMsgSender(BytesMsg & _oBytes)
{
	return nullptr;
}
