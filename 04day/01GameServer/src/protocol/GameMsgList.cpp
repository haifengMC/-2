#include "../../inc/protocol/GameMsgList.h"



GameMsgList::GameMsgList()
{
}


GameMsgList::~GameMsgList()
{
	for (UserData* ud : gameMsgList)
	{
		delete ud;
	}
}

list<GameMsg*>::iterator GameMsgList::begin()
{
	return gameMsgList.begin();
}

list<GameMsg*>::iterator GameMsgList::end()
{
	return gameMsgList.end();
}

void GameMsgList::addMsg(GameMsg * const & p_msg)
{
	gameMsgList.push_back(p_msg);
}