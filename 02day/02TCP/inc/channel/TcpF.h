#pragma once
#include <ZinxTCP.h>

class TcpF : public IZinxTcpConnFact
{
public:
	TcpF();
	~TcpF();

	// ͨ�� IZinxTcpConnFact �̳�
	virtual ZinxTcpData * CreateTcpDataChannel(int _fd) override;
};

