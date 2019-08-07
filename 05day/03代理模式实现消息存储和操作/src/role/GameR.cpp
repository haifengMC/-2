#include "../../inc/role/GameR.h"
#include "../../inc/protocol/GameMsgList.h"
#include "../../inc/protocol/GameMsgF.h"

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
		GameMsgData* p_gmd = nullptr;
		GameMsg* p_sendGm = nullptr;
		switch (p_gm->getId())
		{
		case MSG_TYPE_CHAT:
		{
			if (nullptr == (p_gmd = p_gm->getMsgData()))
			{
				cout << "nullptr == p_gm->getMsgData()" << endl;
				continue;
			}
			cout <<
				"lenth: " << p_gm->getSize() << " " <<
				"ID: " << p_gm->getId() << " " <<
				"value :" << ((ChatData*)p_gmd)->content << endl;

			ChatData* p_cd = new ChatData;
			p_cd->content = "hello";
			p_sendGm = new GameMsg(MSG_TYPE_CHAT, p_cd);
		}
			break;

		default:
			break;
		}

		ZinxKernel::Zinx_SendOut(*p_sendGm, *p_gameP);
	}

	return nullptr;
}

void GameR::Fini()
{
}
