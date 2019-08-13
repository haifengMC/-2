#pragma once
#include "zinx.h"
#include "../role/TimeoutTaskR.h"
class TimeoutMsg :
	public UserData
{
public:
	TimeoutMsg();
	virtual ~TimeoutMsg();

	TimeoutTaskR* ptt = nullptr;
};

