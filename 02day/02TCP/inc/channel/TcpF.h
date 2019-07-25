#pragma once
#include <ZinxTCP.h>

class TcpF : public IZinxTcpConnFact
{
public:
	TcpF();
	~TcpF();

	// Í¨¹ý IZinxTcpConnFact ¼Ì³Ð
	virtual ZinxTcpData * CreateTcpDataChannel(int _fd) override;
};

