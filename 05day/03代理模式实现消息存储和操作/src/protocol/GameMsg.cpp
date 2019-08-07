#include "../../inc/protocol/GameMsg.h"





GameMsg::GameMsg(const size_t& msgType, const string &value) :
	e_msgType(msgType), value(value)
{
}

GameMsg::GameMsg(const size_t & msgType, GameMsgData * const & value) :
	e_msgType(msgType), p_gameMsgData(value)
{
	
}

GameMsg::~GameMsg()
{
	if (nullptr != p_gameMsgData)
		delete p_gameMsgData;
	p_gameMsgData = nullptr;
}

int & GameMsg::getId() const
{
	return e_msgType;
}

size_t GameMsg::getSize() const
{
	if ("" == value) value = getSerialization();
	return value.size();
}

string & GameMsg::getSerialization() const
{
	if ("" != value) return value;
	if (nullptr == p_gameMsgData) return value = "";
	GameMsgF::getGameMsgF(e_msgType)->
		getSerialization(p_gameMsgData, value);
	return value;
}

GameMsgData *& GameMsg::getMsgData() const
{
	if (nullptr != p_gameMsgData)
	{
		delete p_gameMsgData;
		p_gameMsgData = nullptr;
	}
	GameMsgF* p_gameMsgF = GameMsgF::getGameMsgF(e_msgType);
	if (nullptr == p_gameMsgF)
	{
		delete p_gameMsgData;
		p_gameMsgData = nullptr;

		return p_gameMsgData;
	}
	p_gameMsgF->getMsgData(value, p_gameMsgData);

	return p_gameMsgData;
}
