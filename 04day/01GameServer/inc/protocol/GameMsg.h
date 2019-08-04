#pragma once
#include <iostream>
#include "zinx.h"

using namespace std;

class GameMsg :
	public UserData
{
	enum MSG_TYPE
	{
		MSG_TYPE_LOGIN = 1,
		MSG_TYPE_CHAT = 2,
		MSG_TYPE_NEW_POS = 3,
		MSG_TYPE_BROADCAST = 200,
		MSG_TYPE_LOGOUT = 201,
		MSG_TYPE_SRDPLYS_POS = 202
	} e_msgType;
	string value;
public:
	GameMsg(MSG_TYPE msgType, string value);
	virtual ~GameMsg();

	string serialize();
};

