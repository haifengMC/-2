#pragma once
#include "ZinxTCP.h"
class GameCF :
	public IZinxTcpConnFact
{
public:
	GameCF();
	virtual ~GameCF();

	// ͨ�� IZinxTcpConnFact �̳�
	virtual ZinxTcpData * CreateTcpDataChannel(int _fd) override;
};

