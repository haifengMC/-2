#pragma once
#include "zinx.h"
class ExitR :
	public Irole
{
public:
	ExitR();
	virtual ~ExitR();

	// Í¨¹ý Irole ¼Ì³Ð
	virtual bool Init() override;
	virtual UserData * ProcMsg(UserData & _poUserData) override;
	virtual void Fini() override;
};

