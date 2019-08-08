#include "../../inc/protocol/GameMsgF.h"
#include "../../inc/protocol/GameMsg.protoc.pb.h"

using namespace std;


GameMsgF::GameMsgF(const int& msgType, GameMsgF** const& pp_gameMsgF)
{
	if (msgFObj_map.end() == msgFObj_map.find(msgType))
	{
		msgFObj_map[msgType] = pp_gameMsgF;
	}
}


GameMsgF::~GameMsgF()
{
}

GameMsgF * GameMsgF::getGameMsgF(const int & msgType)
{
	if (msgFObj_map.end() == msgFObj_map.find(msgType)) return nullptr;
	return *msgFObj_map[msgType];
}

map<int, GameMsgF**> GameMsgF::msgFObj_map;


LoginMsgF::LoginMsgF() : GameMsgF(MSG_TYPE_LOGIN, (GameMsgF**)&p_LoginMsgF)
{
	p_msg = new GameMsg::SyncPlyrId;
}

LoginMsgF::~LoginMsgF()
{
	delete p_msg;
}

void LoginMsgF::getSerialization(GameMsgData * const & p_gameMsgData, string & serialization)
{
	SyncPlyrIdData* p_loginData = dynamic_cast<SyncPlyrIdData*>(p_gameMsgData);
	GameMsg::SyncPlyrId* p_loginMsg = dynamic_cast<GameMsg::SyncPlyrId*>(p_msg);
	
	p_loginMsg->set_plyrid(p_loginData->plyrId);
	p_loginMsg->set_usrname(p_loginData->usrName);
	
	p_loginMsg->SerializePartialToString(&serialization);
}

void LoginMsgF::getMsgData(const string & serialization, GameMsgData *& p_gameMsgData)
{
	delete p_gameMsgData;
	p_gameMsgData = new SyncPlyrIdData;
	SyncPlyrIdData* p_loginData = dynamic_cast<SyncPlyrIdData*>(p_gameMsgData);
	GameMsg::SyncPlyrId* p_loginMsg = dynamic_cast<GameMsg::SyncPlyrId*>(p_msg);

	p_loginMsg->ParseFromString(serialization);
	p_loginData->plyrId = p_loginMsg->plyrid();
	p_loginData->usrName = p_loginMsg->usrname();
}


LoginMsgF* LoginMsgF::p_LoginMsgF = new LoginMsgF;


ChatMsgF::ChatMsgF() : GameMsgF(MSG_TYPE_CHAT, (GameMsgF**)&p_charMsgF)
{
	p_msg = new GameMsg::Chat;
}

ChatMsgF::~ChatMsgF()
{
	delete p_msg;
}

void ChatMsgF::getSerialization(GameMsgData * const & p_gameMsgData, string & serialization)
{
	ChatData* p_chatData = dynamic_cast<ChatData*>(p_gameMsgData);
	GameMsg::Chat* p_chatMsg = dynamic_cast<GameMsg::Chat*>(p_msg);
	p_chatMsg->set_content(p_chatData->content);
	p_chatMsg->SerializePartialToString(&serialization);
}

void ChatMsgF::getMsgData(const string & serialization, GameMsgData *& p_gameMsgData)
{
	delete p_gameMsgData;
	p_gameMsgData = new ChatData;
	ChatData* p_chatData = dynamic_cast<ChatData*>(p_gameMsgData);
	GameMsg::Chat* p_chatMsg = dynamic_cast<GameMsg::Chat*>(p_msg);

	p_chatMsg->ParseFromString(serialization);
	p_chatData->content = p_chatMsg->content();
}

ChatMsgF* ChatMsgF::p_charMsgF = new ChatMsgF;

NewPosMsgF::NewPosMsgF() : GameMsgF(MSG_TYPE_NEW_POS, (GameMsgF**)&p_newPosMsgF)
{
	p_msg = new GameMsg::PlyrPos;
}

NewPosMsgF::~NewPosMsgF()
{
	delete p_msg;
}

void NewPosMsgF::getSerialization(GameMsgData * const & p_gameMsgData, string & serialization)
{
	PlyrPosData* p_newPosData = dynamic_cast<PlyrPosData*>(p_gameMsgData);
	GameMsg::PlyrPos* p_newPosMsg = dynamic_cast<GameMsg::PlyrPos*>(p_msg);
	p_newPosMsg->set_x(p_newPosData->X);
	p_newPosMsg->set_y(p_newPosData->Y);
	p_newPosMsg->set_z(p_newPosData->Z);
	p_newPosMsg->set_v(p_newPosData->V);
	p_newPosMsg->set_bloodvalue(p_newPosData->bloodValue);
	p_newPosMsg->SerializePartialToString(&serialization);
}

void NewPosMsgF::getMsgData(const string & serialization, GameMsgData *& p_gameMsgData)
{
	delete p_gameMsgData;
	p_gameMsgData = new PlyrPosData;
	PlyrPosData* p_plyrPosData = dynamic_cast<PlyrPosData*>(p_gameMsgData);
	GameMsg::PlyrPos* p_plyrPosMsg = dynamic_cast<GameMsg::PlyrPos*>(p_msg);

	p_plyrPosMsg->ParseFromString(serialization);
	p_plyrPosData->X = p_plyrPosMsg->x();
	p_plyrPosData->Y = p_plyrPosMsg->y();
	p_plyrPosData->Z = p_plyrPosMsg->z();
	p_plyrPosData->V = p_plyrPosMsg->v();
	p_plyrPosData->bloodValue = p_plyrPosMsg->bloodvalue();
}

NewPosMsgF* NewPosMsgF::p_newPosMsgF = new NewPosMsgF;

BroadcastMsgF::BroadcastMsgF() : GameMsgF(MSG_TYPE_BROADCAST, (GameMsgF**)&p_broadcastMsgF)
{
	p_msg = new GameMsg::BroadCast;
}

BroadcastMsgF::~BroadcastMsgF()
{
	delete p_msg;
}

void BroadcastMsgF::getSerialization(GameMsgData * const & p_gameMsgData, string & serialization)
{
	BroadCastData* p_broadcastData = dynamic_cast<BroadCastData*>(p_gameMsgData);
	GameMsg::BroadCast* p_broadcastMsg = dynamic_cast<GameMsg::BroadCast*>(p_msg);
	p_broadcastMsg->set_plyrid(p_broadcastData->plyrId);
	p_broadcastMsg->set_bctype(p_broadcastData->bcType);
	p_broadcastMsg->set_usrname(p_broadcastData->usrName);
	switch (p_broadcastMsg->bctype())
	{
		//广播类型，1、聊天内容；2、出生位置；3、移动后的位置;4、动作数据
	case 1:
		{
			GameMsg::Chat* p_chatMsg = p_broadcastMsg->mutable_plyrchat();
			p_chatMsg->set_content(p_broadcastData->data.plyrChat.content);
		}
		break;
	case 2:
		{
			GameMsg::PlyrPos* p_plyrPosMsg = p_broadcastMsg->mutable_plyrpos();
			p_plyrPosMsg->set_x(p_broadcastData->data.plyrPos.X);
			p_plyrPosMsg->set_y(p_broadcastData->data.plyrPos.Y);
			p_plyrPosMsg->set_z(p_broadcastData->data.plyrPos.Z);
			p_plyrPosMsg->set_v(p_broadcastData->data.plyrPos.V);
			p_plyrPosMsg->set_bloodvalue(p_broadcastData->data.plyrPos.bloodValue);
		}
		break;
	case 3:
		{
			GameMsg::PlyrPos* p_plyrPosMsg = p_broadcastMsg->mutable_plyrpos();
			p_plyrPosMsg->set_x(p_broadcastData->data.plyrPos.X);
			p_plyrPosMsg->set_y(p_broadcastData->data.plyrPos.Y);
			p_plyrPosMsg->set_z(p_broadcastData->data.plyrPos.Z);
			p_plyrPosMsg->set_v(p_broadcastData->data.plyrPos.V);
			p_plyrPosMsg->set_bloodvalue(p_broadcastData->data.plyrPos.bloodValue);
		}
		break;
	case 4:
		{
			p_broadcastMsg->set_actiondata(p_broadcastData->data.actionData);
		}
		break;
	default:
		break;
	}
	p_broadcastMsg->SerializePartialToString(&serialization);
}

void BroadcastMsgF::getMsgData(const string & serialization, GameMsgData *& p_gameMsgData)
{
	delete p_gameMsgData;
	p_gameMsgData = new BroadCastData;
	BroadCastData* p_broadcastData = dynamic_cast<BroadCastData*>(p_gameMsgData);
	GameMsg::BroadCast* p_broadcastMsg = dynamic_cast<GameMsg::BroadCast*>(p_msg);

	p_broadcastMsg->ParseFromString(serialization);
	p_broadcastData->plyrId = p_broadcastMsg->plyrid();
	p_broadcastData->bcType = p_broadcastMsg->bctype();
	p_broadcastData->usrName = p_broadcastMsg->usrname();
	switch (p_broadcastData->bcType)
	{
		//广播类型，1、聊天内容；2、出生位置；3、移动后的位置;4、动作数据
	case 1:
		{
			p_broadcastData->data.plyrChat.content = 
				p_broadcastMsg->plyrchat().content();
		}
		break;
	case 2:
		{
			p_broadcastData->data.plyrPos.X = p_broadcastMsg->plyrpos().x();
			p_broadcastData->data.plyrPos.Y = p_broadcastMsg->plyrpos().y();
			p_broadcastData->data.plyrPos.Z = p_broadcastMsg->plyrpos().z();
			p_broadcastData->data.plyrPos.V = p_broadcastMsg->plyrpos().v();
			p_broadcastData->data.plyrPos.bloodValue =
				p_broadcastMsg->plyrpos().bloodvalue();
		}
		break;
	case 3:
		{		
			p_broadcastData->data.plyrPos.X = p_broadcastMsg->plyrpos().x();
			p_broadcastData->data.plyrPos.Y = p_broadcastMsg->plyrpos().y();
			p_broadcastData->data.plyrPos.Z = p_broadcastMsg->plyrpos().z();
			p_broadcastData->data.plyrPos.V = p_broadcastMsg->plyrpos().v();
			p_broadcastData->data.plyrPos.bloodValue =
				p_broadcastMsg->plyrpos().bloodvalue();
		}
		break;
	case 4:
		{
			p_broadcastData->data.actionData = p_broadcastMsg->actiondata();
		}
		break;
	default:
		break;
	}
}

BroadcastMsgF* BroadcastMsgF::p_broadcastMsgF = new BroadcastMsgF;

LogoutMsgF::LogoutMsgF() : GameMsgF(MSG_TYPE_LOGOUT, (GameMsgF**)&p_logoutMsgF)
{
	p_msg = new GameMsg::SyncPlyrId;
}

LogoutMsgF::~LogoutMsgF()
{
	delete p_msg;
}

void LogoutMsgF::getSerialization(GameMsgData * const & p_gameMsgData, string & serialization)
{
	SyncPlyrIdData* p_logoutData = dynamic_cast<SyncPlyrIdData*>(p_gameMsgData);
	GameMsg::SyncPlyrId* p_logoutMsg = dynamic_cast<GameMsg::SyncPlyrId*>(p_msg);

	p_logoutMsg->set_plyrid(p_logoutData->plyrId);
	p_logoutMsg->set_usrname(p_logoutData->usrName);

	p_logoutMsg->SerializePartialToString(&serialization);
}

void LogoutMsgF::getMsgData(const string & serialization, GameMsgData *& p_gameMsgData)
{
	delete p_gameMsgData;
	p_gameMsgData = new SyncPlyrIdData;
	SyncPlyrIdData* p_logoutData = dynamic_cast<SyncPlyrIdData*>(p_gameMsgData);
	GameMsg::SyncPlyrId* p_logoutMsg = dynamic_cast<GameMsg::SyncPlyrId*>(p_msg);

	p_logoutMsg->ParseFromString(serialization);
	p_logoutData->plyrId = p_logoutMsg->plyrid();
	p_logoutData->usrName = p_logoutMsg->usrname();
}

LogoutMsgF* LogoutMsgF::p_logoutMsgF = new LogoutMsgF;

SrdPlyrsMsgF::SrdPlyrsMsgF() : GameMsgF(MSG_TYPE_SRDPLYRS_POS, (GameMsgF**)&p_srdPlyrsMsgF)
{
	p_msg = new GameMsg::SyncPlyrs;
}

SrdPlyrsMsgF::~SrdPlyrsMsgF()
{
	delete p_msg;
}

void SrdPlyrsMsgF::getSerialization(GameMsgData * const & p_gameMsgData, string & serialization)
{
	SyncPlyrsData* p_syncPlyrsData = dynamic_cast<SyncPlyrsData*>(p_gameMsgData);
	GameMsg::SyncPlyrs* p_syncPlyrsMsg = dynamic_cast<GameMsg::SyncPlyrs*>(p_msg);
	
	for (PlyrData& pd : p_syncPlyrsData->plyrs)
	{
		GameMsg::Plyr* p_plyr = p_syncPlyrsMsg->add_plyrs();
		p_plyr->set_plyrid(pd.plyrId);
		p_plyr->set_usrname(pd.usrName);
		GameMsg::PlyrPos* p_plyrPos = p_plyr->mutable_plyrpos();
		p_plyrPos->set_x(pd.plyrPos.X);
		p_plyrPos->set_y(pd.plyrPos.Y);
		p_plyrPos->set_z(pd.plyrPos.Z);
		p_plyrPos->set_v(pd.plyrPos.V);
		p_plyrPos->set_bloodvalue(pd.plyrPos.bloodValue);
	}
	p_syncPlyrsMsg->SerializePartialToString(&serialization);
}

void SrdPlyrsMsgF::getMsgData(const string & serialization, GameMsgData *& p_gameMsgData)
{
	delete p_gameMsgData;
	p_gameMsgData = new SyncPlyrsData;
	SyncPlyrsData* p_syncPlyrsData = dynamic_cast<SyncPlyrsData*>(p_gameMsgData);
	GameMsg::SyncPlyrs* p_syncPlyrsMsg = dynamic_cast<GameMsg::SyncPlyrs*>(p_msg);

	p_syncPlyrsMsg->ParseFromString(serialization);
	for (int i = 0; i < p_syncPlyrsMsg->plyrs_size(); i++)
	{
		const GameMsg::Plyr& p_plyr = p_syncPlyrsMsg->plyrs(i);
		PlyrData pd;
		pd.plyrId = p_plyr.plyrid();
		pd.usrName = p_plyr.usrname();

		pd.plyrPos.X = p_plyr.plyrpos().x();
		pd.plyrPos.Y = p_plyr.plyrpos().y();
		pd.plyrPos.Z = p_plyr.plyrpos().z();
		pd.plyrPos.V = p_plyr.plyrpos().v();
		pd.plyrPos.bloodValue = p_plyr.plyrpos().bloodvalue();

		p_syncPlyrsData->plyrs.push_back(pd);
	}
	//cout << "SrdPlyrsMsgF::getMsgData OK" << endl;
}

SrdPlyrsMsgF* SrdPlyrsMsgF::p_srdPlyrsMsgF = new SrdPlyrsMsgF;
