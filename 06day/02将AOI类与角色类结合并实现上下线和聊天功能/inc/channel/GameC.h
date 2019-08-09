#pragma once

#include <ZinxTCP.h>

class GameC :
	public ZinxTcpData
{
	Iprotocol* p_gameP = NULL;
public:
	GameC(int _fd);
	virtual ~GameC();
	
	void bindProtocol(Iprotocol* &&p_gameP) { this->p_gameP = p_gameP; }
	
	// Í¨¹ý ZinxTcpData ¼Ì³Ð
	virtual AZinxHandler * GetInputNextStage(BytesMsg & _oInput) override;

};

