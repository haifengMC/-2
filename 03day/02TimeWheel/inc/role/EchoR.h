#pragma once
#include "zinx.h"
class EchoR :
	public Irole
{
public:
	EchoR();
	virtual ~EchoR();

	// ͨ�� Irole �̳�
	virtual bool Init() override;
	virtual UserData * ProcMsg(UserData & _poUserData) override;
	virtual void Fini() override;
};

