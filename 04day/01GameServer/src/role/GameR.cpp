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
			"value :" << p_gm->serialize() << endl;
		ZinxKernel::Zinx_SendOut(*p_gm, *p_gameP);
	}

	return nullptr;
}

void GameR::Fini()
{
}
