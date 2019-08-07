#pragma once
#include <iostream>
#include "zinx.h"
#include "GameMsgData.h"
#include "GameMsgF.h"
#include "google/protobuf/message.h"

using namespace std;

class GameMsg :
	public UserData
{
	//enum _MSG_TYPE
	//{
	//	MSG_TYPE_LOGIN = 1,
	//	MSG_TYPE_CHAT = 2,
	//	MSG_TYPE_NEW_POS = 3,
	//	MSG_TYPE_BROADCAST = 200,
	//	MSG_TYPE_LOGOUT = 201,
	//	MSG_TYPE_SRDPLYS_POS = 202
	//};
	mutable int e_msgType;
	mutable string value;
	mutable GameMsgData* p_gameMsgData = nullptr;
	//GameMsgF gameMsgF;
	//google::protobuf::Message* p_msgContent = NULL;
public:
	//typedef _MSG_TYPE MSG_TYPE;

	GameMsg(const size_t& msgType, const string &value);
	GameMsg(const size_t& msgType, GameMsgData* const &value);
	virtual ~GameMsg();

	int& getId() const;
	size_t getSize() const;
	string& getSerialization() const;
	GameMsgData*& getMsgData() const;

};

