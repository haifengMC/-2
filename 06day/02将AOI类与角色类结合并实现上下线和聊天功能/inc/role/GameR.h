#pragma once

#include <zinx.h>

class GameR :
	public Irole
{
	Iprotocol* p_gameP = NULL;
public:
	GameR();
	virtual ~GameR();
	
	void bindProtocol(Iprotocol * &&p_gameP) { this->p_gameP = p_gameP; }

	// Í¨¹ý Irole ¼Ì³Ð
	virtual bool Init() override;
	virtual UserData * ProcMsg(UserData & _poUserData) override;
	virtual void Fini() override;
};

