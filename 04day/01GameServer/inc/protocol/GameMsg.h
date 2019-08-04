#pragma once
#include <iostream>
#include "zinx.h"

using namespace std;

class GameMsg :
	public UserData
{
	mutable enum _MSG_TYPE
	{
		MSG_TYPE_LOGIN = 1,
		MSG_TYPE_CHAT = 2,
		MSG_TYPE_NEW_POS = 3,
		MSG_TYPE_BROADCAST = 200,
		MSG_TYPE_LOGOUT = 201,
		MSG_TYPE_SRDPLYS_POS = 202
	} e_msgType;
	mutable string value;
public:
	typedef _MSG_TYPE MSG_TYPE;

	GameMsg(MSG_TYPE msgType, const string &value);
	virtual ~GameMsg();

	MSG_TYPE& getId() const;
	size_t getSize() const;
	string& serialize() const;

};

