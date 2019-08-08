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
		case MSG_TYPE_LOGIN:
			{
				if (nullptr == (p_gmd = p_gm->getMsgData()))
				{
					cout << "nullptr == p_gm->getMsgData()" << endl;
					continue;
				}
				cout <<
					"login message :\n\t"
					"lenth: " << p_gm->getSize() << "\n\t" <<
					"ID: " << p_gm->getId() << "\n\t" <<
					"plyrId: " << ((SyncPlyrIdData*)p_gmd)->plyrId << "\n\t" <<
					"usrName: " << ((SyncPlyrIdData*)p_gmd)->usrName << endl;
				SyncPlyrIdData* p_spid = new SyncPlyrIdData;
				p_spid->plyrId = 30;
				p_spid->usrName = "lulu";
				p_sendGm = new GameMsg(MSG_TYPE_LOGIN, p_spid);
			}
			break;
		case MSG_TYPE_CHAT:
			{
				if (nullptr == (p_gmd = p_gm->getMsgData()))
				{
					cout << "nullptr == p_gm->getMsgData()" << endl;
					continue;
				}
				cout <<
					"chat message :\n\t"
					"lenth: " << p_gm->getSize() << "\n\t" <<
					"ID: " << p_gm->getId() << "\n\t" <<
					"content: " << ((ChatData*)p_gmd)->content << endl;

				ChatData* p_cd = new ChatData;
				p_cd->content = "hello";
				p_sendGm = new GameMsg(MSG_TYPE_CHAT, p_cd);
			}
			break;
		case MSG_TYPE_NEW_POS:
			{
				if (nullptr == (p_gmd = p_gm->getMsgData()))
				{
					cout << "nullptr == p_gm->getMsgData()" << endl;
					continue;
				}
				cout <<
					"new position message :\n\t"
					"lenth: " << p_gm->getSize() << "\n\t" <<
					"ID: " << p_gm->getId() << "\n\t" <<
					"Pos: (" << 
						((PlyrPosData*)p_gmd)->X << ", " <<
						((PlyrPosData*)p_gmd)->Y << ", " <<
						((PlyrPosData*)p_gmd)->Z << ", " <<
						((PlyrPosData*)p_gmd)->V << ")\n\t" <<
					"bloodValue: " << ((PlyrPosData*)p_gmd)->bloodValue << endl;
				PlyrPosData* p_ppd = new PlyrPosData;
				p_ppd->X = 1.0;
				p_ppd->Y = 1.0;
				p_ppd->Z = 1.0;
				p_ppd->V = 1.0;
				p_ppd->bloodValue = 5;

				p_sendGm = new GameMsg(MSG_TYPE_NEW_POS, p_ppd);
			}
			break;
		case MSG_TYPE_BROADCAST:
			{
				if (nullptr == (p_gmd = p_gm->getMsgData()))
				{
					cout << "nullptr == p_gm->getMsgData()" << endl;
					continue;
				}
				cout <<
					"broadcast message :\n\t"
					"lenth: " << p_gm->getSize() << "\n\t" <<
					"ID: " << p_gm->getId() << "\n\t" <<
					"plyrId: " << ((BroadCastData*)p_gmd)->plyrId << "\n\t" <<
					"bcType: " << ((BroadCastData*)p_gmd)->bcType << "\n\t" <<
					"usrName: " << ((BroadCastData*)p_gmd)->usrName << endl;
				BroadCastData* p_bcd = new BroadCastData;
				switch (((BroadCastData*)p_gmd)->bcType)
				{
				case 1:
					{
						cout << "\tchat content: \n\t\t" <<
							"content: " << ((BroadCastData*)p_gmd)->data.plyrChat.content << endl;
						p_bcd->plyrId = 300;
						p_bcd->usrName = "lulu";
						p_bcd->bcType = 1;
						p_bcd->data.plyrChat.content = "hello";
					}
	
					break;
				case 2:
					cout << "\tbirth position: \n\t\t" <<
						"Pos: (" <<
						((BroadCastData*)p_gmd)->data.plyrPos.X << ", " <<
						((BroadCastData*)p_gmd)->data.plyrPos.Y << ", " <<
						((BroadCastData*)p_gmd)->data.plyrPos.Z << ", " <<
						((BroadCastData*)p_gmd)->data.plyrPos.V << ")\n\t\t" <<
						"bloodValue: " << ((BroadCastData*)p_gmd)->data.plyrPos.bloodValue << endl;
					p_bcd->plyrId = 300;
					p_bcd->usrName = "lulu";
					p_bcd->bcType = 2;
					p_bcd->data.plyrPos.X = 1.0;
					p_bcd->data.plyrPos.Y = 1.0;
					p_bcd->data.plyrPos.Z = 1.0;
					p_bcd->data.plyrPos.V = 1.0;
					p_bcd->data.plyrPos.bloodValue = 5;
					break;
				case 3:	   
					cout << "\tmove position\n\t\t" <<
						"Pos: (" <<
						((BroadCastData*)p_gmd)->data.plyrPos.X << ", " <<
						((BroadCastData*)p_gmd)->data.plyrPos.Y << ", " <<
						((BroadCastData*)p_gmd)->data.plyrPos.Z << ", " <<
						((BroadCastData*)p_gmd)->data.plyrPos.V << ")\n\t\t" <<
						"bloodValue: " << 
						((BroadCastData*)p_gmd)->data.plyrPos.bloodValue << endl;
					p_bcd->plyrId = 300;
					p_bcd->usrName = "lulu";
					p_bcd->bcType = 3;
					p_bcd->data.plyrPos.X = 2.0;
					p_bcd->data.plyrPos.Y = 2.0;
					p_bcd->data.plyrPos.Z = 2.0;
					p_bcd->data.plyrPos.V = 2.0;
					p_bcd->data.plyrPos.bloodValue = 5;
					break;
				case 4:
					cout << "\taction data\n\t\t" <<
						"actionData: " << ((BroadCastData*)p_gmd)->data.actionData << endl;
					p_bcd->plyrId = 300;
					p_bcd->usrName = "lulu";
					p_bcd->bcType = 4;
					p_bcd->data.actionData = 20;
					break;
				default:
					break;
				}
				p_sendGm = new GameMsg(MSG_TYPE_BROADCAST, p_bcd);
			}
			break;
		case MSG_TYPE_LOGOUT:
			{
				if (nullptr == (p_gmd = p_gm->getMsgData()))
				{
					cout << "nullptr == p_gm->getMsgData()" << endl;
					continue;
				}
				cout <<
					"loginout message :\n\t"
					"lenth: " << p_gm->getSize() << "\n\t" <<
					"ID: " << p_gm->getId() << "\n\t" <<
					"plyrId: " << ((SyncPlyrIdData*)p_gmd)->plyrId << "\n\t" <<
					"usrName: " << ((SyncPlyrIdData*)p_gmd)->usrName << endl;
				SyncPlyrIdData* p_spid = new SyncPlyrIdData;
				p_spid->plyrId = 30;
				p_spid->usrName = "lulu";
				p_sendGm = new GameMsg(MSG_TYPE_LOGOUT, p_spid);
			}
			break;
		case MSG_TYPE_SRDPLYRS_POS:
			{
				if (nullptr == (p_gmd = p_gm->getMsgData()))
				{
					cout << "nullptr == p_gm->getMsgData()" << endl;
					continue;
				}
				cout <<
					"suround plays message :\n\t"
					"lenth: " << p_gm->getSize() << "\n\t" <<
					"ID: " << p_gm->getId() << endl;
				for (PlyrData& pd : ((SyncPlyrsData*)p_gmd)->plyrs)
				{
					cout << "\tplyrId: " << pd.plyrId << ";  " <<
						"usrName: " << pd.usrName << "\n\t\t" <<
						"Pos: (" <<
						pd.plyrPos.X << ", " <<
						pd.plyrPos.Y << ", " <<
						pd.plyrPos.Z << ", " <<
						pd.plyrPos.V << ")\n\t\t" <<
						"bloodValue: " << pd.plyrPos.bloodValue << endl;
				}
				SyncPlyrsData* p_spd = new SyncPlyrsData;

				for (int i = 0; i < 2; i++)
				{
					PlyrData pd;
					pd.plyrId = 300;
					pd.plyrPos.X = 1.0;
					pd.plyrPos.Y = 1.0;
					pd.plyrPos.Z = 1.0;
					pd.plyrPos.V = 1.0;
					pd.plyrPos.bloodValue = 5;
					p_spd->plyrs.push_back(pd);
				}

				p_sendGm = new GameMsg(MSG_TYPE_SRDPLYRS_POS, p_spd);
			}
			break;
		default:
			break;
		}

		ZinxKernel::Zinx_SendOut(*p_sendGm, *p_gameP);
		//cout << "Zinx_SendOut OK" << endl;
	}

	return nullptr;
}

void GameR::Fini()
{
}
