#pragma once
#include "zinx.h"
class ExitR :
	public Irole
{
public:
	ExitR();
	virtual ~ExitR();

	// ͨ�� Irole �̳�
	virtual bool Init() override;
	virtual UserData * ProcMsg(UserData & _poUserData) override;
	virtual void Fini() override;
};

