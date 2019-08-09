#pragma once
#include "ZinxTCP.h"
class GameCF :
	public IZinxTcpConnFact
{
public:
	GameCF();
	virtual ~GameCF();

	// Í¨¹ý IZinxTcpConnFact ¼Ì³Ð
	virtual ZinxTcpData * CreateTcpDataChannel(int _fd) override;
};

