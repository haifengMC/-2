#include "../../inc/channel/GameC.h"


GameC::GameC(int _fd) : ZinxTcpData(_fd)
{
}

GameC::~GameC()
{
	ZinxKernel::Zinx_Del_Proto(*p_gameP);
	delete(p_gameP);
}

AZinxHandler * GameC::GetInputNextStage(BytesMsg & _oInput)
{
	return p_gameP;
}

