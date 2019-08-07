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
	virtual void getSerialization(GameMsgData * const & p_gameMsgData, string& serialization) = 0;
	virtual void getMsgData(const string& serialization, GameMsgData *& gameMsgData) = 0;
protected:
	google::protobuf::Message* p_msg = nullptr;
private:
	static map<int, GameMsgF**> msgFObj_map;
};
#define MSG_TYPE_LOGIN 1
class LoginMsgF : public GameMsgF
{
private:
	LoginMsgF();
	virtual ~LoginMsgF();

	static LoginMsgF* p_LoginMsgF;

	// 通过 GameMsgF 继承
	virtual void getSerialization(GameMsgData * const & p_gameMsgData, string & serialization) override;
	virtual void getMsgData(const string & serialization, GameMsgData *& p_gameMsgData) override;
};

#define MSG_TYPE_CHAT 2
class ChatMsgF : public GameMsgF
{
private:
	ChatMsgF();
	virtual ~ChatMsgF();
	
	static ChatMsgF* p_charMsgF;


	// 通过 GameMsgF 继承
	virtual void getSerialization(GameMsgData * const & p_gameMsgData, string & serialization) override;
	virtual void getMsgData(const string & serialization, GameMsgData *& p_gameMsgData) override;
};

#define MSG_TYPE_NEW_POS 3
class NewPosMsgF : public GameMsgF
{
private:
	NewPosMsgF();
	virtual ~NewPosMsgF();

	static NewPosMsgF* p_newPosMsgF;


	// 通过 GameMsgF 继承
	virtual void getSerialization(GameMsgData * const & p_gameMsgData, string & serialization) override;
	virtual void getMsgData(const string & serialization, GameMsgData *& p_gameMsgData) override;
};

#define MSG_TYPE_BROADCAST 200
class BroadcastMsgF : public GameMsgF
{
private:
	BroadcastMsgF();
	virtual ~BroadcastMsgF();

	static BroadcastMsgF* p_broadcastMsgF;


	// 通过 GameMsgF 继承
	virtual void getSerialization(GameMsgData * const & p_gameMsgData, string & serialization) override;
	virtual void getMsgData(const string & serialization, GameMsgData *& p_gameMsgData) override;
};

#define MSG_TYPE_LOGOUT 201
class LogoutMsgF : public GameMsgF
{
private:
	LogoutMsgF();
	virtual ~LogoutMsgF();

	static LogoutMsgF* p_logoutMsgF;


	// 通过 GameMsgF 继承
	virtual void getSerialization(GameMsgData * const & p_gameMsgData, string & serialization) override;
	virtual void getMsgData(const string & serialization, GameMsgData *& p_gameMsgData) override;
};

#define MSG_TYPE_SRDPLYRS_POS 202
class SrdPlyrsMsgF : public GameMsgF
{
private:
	SrdPlyrsMsgF();
	virtual ~SrdPlyrsMsgF();

	static SrdPlyrsMsgF* p_srdPlyrsMsgF;


	// 通过 GameMsgF 继承
	virtual void getSerialization(GameMsgData * const & p_gameMsgData, string & serialization) override;
	virtual void getMsgData(const string & serialization, GameMsgData *& p_gameMsgData) override;
};


