#pragma once

#include <ZinxTCP.h>

class GameC :
	public ZinxTcpData
{
public:
	virtual ~GameC();

	

	// Í¨¹ý ZinxTcpData ¼Ì³Ð
	virtual AZinxHandler * GetInputNextStage(BytesMsg & _oInput) override;

};

