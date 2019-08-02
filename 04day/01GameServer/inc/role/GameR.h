#pragma once

#include <zinx.h>

class GameR :
	public Irole
{
public:
	GameR();
	virtual ~GameR();

	// Í¨¹ý Irole ¼Ì³Ð
	virtual bool Init() override;
	virtual UserData * ProcMsg(UserData & _poUserData) override;
	virtual void Fini() override;
};

