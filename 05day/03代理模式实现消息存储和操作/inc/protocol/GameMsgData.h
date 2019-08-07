#pragma once
#include <iostream>

using namespace std;

struct GameMsgData
{
	virtual ~GameMsgData();
};

struct ChatData : GameMsgData
{
	virtual ~ChatData() override;
	string content;
};

