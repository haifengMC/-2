#include "../../inc/role/GameR.h"
#include "../../inc/protocol/GameMsgList.h"
#include <iostream>

using namespace std;

GameR::GameR()
{
}


GameR::~GameR()
{
}

bool GameR::Init()
{
	return false;
}

UserData * GameR::ProcMsg(UserData & _poUserData)
{
	GET_REF2DATA(GameMsgList, gameMsgList, _poUserData);
	for (GameMsg* p_gm : gameMsgList)
	{
		cout <<
			"lenth: " << p_gm->getSize() << " " <<
			"ID: " << p_gm->getId() << " " <<
			"value :" << ((ChatData*)p_gm->getMsgData())->content << endl;
		
		ChatData* p_cd = new ChatData;
		p_cd->content = "hello";
		GameMsg* p_sendGm = new GameMsg(MSG_TYPE_CHAT, p_cd);
		ZinxKernel::Zinx_SendOut(*p_sendGm, *p_gameP);
	}

	return nullptr;
}

void GameR::Fini()
{
}
