#pragma once
#include "zinx.h"
class OMngR :
	public Irole
{
	Ichannel* stdoutC = NULL;
public:
	OMngR();
	virtual ~OMngR();

	// Í¨¹ý Irole ¼Ì³Ð
	virtual bool Init() override;
	virtual UserData * ProcMsg(UserData & _poUserData) override;
	virtual void Fini() override;
};

