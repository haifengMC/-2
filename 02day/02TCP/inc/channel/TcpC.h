#pragma once
#include <ZinxTCP.h>

class TcpC :
	public ZinxTcpData
{
public:
	TcpC(int _fd);
	virtual ~TcpC();

	// Í¨¹ý ZinxTcpData ¼Ì³Ð
	virtual AZinxHandler * GetInputNextStage(BytesMsg & _oInput) override;
};

