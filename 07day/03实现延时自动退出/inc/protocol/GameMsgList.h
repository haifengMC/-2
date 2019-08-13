#pragma once
#include "zinx.h"
#include "GameMsg.h"
#include <list>

class GameMsgList :
	public UserData
{
	list<GameMsg*> gameMsgList;
public:
	GameMsgList();
	virtual ~GameMsgList();

	list<GameMsg*>::iterator begin();
	list<GameMsg*>::iterator end();
	void addMsg(GameMsg* const& p_msg);
};

