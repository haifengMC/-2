#pragma once
#include <ZinxTCP.h>

class TcpC :
	public ZinxTcpData
{
public:
	TcpC(int _fd);
	virtual ~TcpC();

	// ͨ�� ZinxTcpData �̳�
	virtual AZinxHandler * GetInputNextStage(BytesMsg & _oInput) override;
};

