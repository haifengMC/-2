#pragma once

#include <zinx.h>

class GameR :
	public Irole
{
public:
	GameR();
	virtual ~GameR();

	// ͨ�� Irole �̳�
	virtual bool Init() override;
	virtual UserData * ProcMsg(UserData & _poUserData) override;
	virtual void Fini() override;
};

