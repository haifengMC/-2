#pragma once
#include "zinx.h"
class OMngR :
	public Irole
{
	Ichannel* stdoutC = NULL;
public:
	OMngR();
	virtual ~OMngR();

	// ͨ�� Irole �̳�
	virtual bool Init() override;
	virtual UserData * ProcMsg(UserData & _poUserData) override;
	virtual void Fini() override;
};

