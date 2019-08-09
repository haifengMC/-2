#include "../../inc/channel/GameC.h"


GameC::GameC(int _fd) : ZinxTcpData(_fd)
{
}

GameC::~GameC()
{
}

AZinxHandler * GameC::GetInputNextStage(BytesMsg & _oInput)
{
	return p_gameP;
}

