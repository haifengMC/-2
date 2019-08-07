#pragma once
#include <map>
#include <functional>

#include "GameMsgData.h"
#include "google/protobuf/message.h"


using namespace std;

class GameMsgF
{
public:
	GameMsgF(const int& msgType, GameMsgF** const& pp_gameMsgF);
	virtual ~GameMsgF();
	
	static GameMsgF* getGameMsgF(const int& msgType);
	virtual void getSerialization(GameMsgData * const & gameMsgData, string& serialization) = 0;
	virtual void getMsgData(const string& serialization, GameMsgData *& gameMsgData) = 0;
protected:
	google::protobuf::Message* p_msg = nullptr;
private:
	static map<int, GameMsgF**> msgFObj_map;
};


#define MSG_TYPE_CHAT 2
class ChatMsgF : public GameMsgF
{
private:
	ChatMsgF();
	virtual ~ChatMsgF();
	
	static ChatMsgF* p_charMsgF;


	// Í¨¹ý GameMsgF ¼Ì³Ð
	virtual void getSerialization(GameMsgData * const & p_gameMsgData, string & serialization) override;
	virtual void getMsgData(const string & serialization, GameMsgData *& p_gameMsgData) override;
};

