#pragma once
#include "zinx.h"
class CmdMsg :
	public UserData
{
public:
	CmdMsg();
	virtual ~CmdMsg();
	bool b_exit = false;
	bool b_open = true;
	std::string m_echo;
};

