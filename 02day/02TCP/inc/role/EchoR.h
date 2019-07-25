#pragma once
#include "zinx.h"
class EchoR :
	public Irole
{
public:
	EchoR();
	virtual ~EchoR();

	// Í¨¹ý Irole ¼Ì³Ð
	virtual bool Init() override;
	virtual UserData * ProcMsg(UserData & _poUserData) override;
	virtual void Fini() override;
};

