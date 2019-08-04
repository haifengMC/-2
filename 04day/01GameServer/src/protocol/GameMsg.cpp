#include "../../inc/protocol/GameMsg.h"





GameMsg::GameMsg(MSG_TYPE msgType, string value) :
	e_msgType(msgType), value(value)
{
	cout << value << endl;
}

GameMsg::~GameMsg()
{
}

string GameMsg::serialize()
{
	return "hello";
}
