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
