#pragma once

#include <ZinxTCP.h>

class GameC :
	public ZinxTcpData
{
public:
	virtual ~GameC();

	

	// ͨ�� ZinxTcpData �̳�
	virtual AZinxHandler * GetInputNextStage(BytesMsg & _oInput) override;

};

