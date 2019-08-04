#include "../../inc/protocol/GameMsg.h"





GameMsg::GameMsg(MSG_TYPE msgType, const string &value) :
	e_msgType(msgType), value(value)
{
}

GameMsg::~GameMsg()
{
}

GameMsg::MSG_TYPE & GameMsg::getId() const
{
	return e_msgType;
}

size_t GameMsg::getSize() const
{
	return value.size();
}

string& GameMsg::serialize() const
{
	return value;
}
