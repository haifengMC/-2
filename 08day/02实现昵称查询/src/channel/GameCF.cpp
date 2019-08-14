#include "../../inc/channel/GameCF.h"
#include "../../inc/channel/GameC.h"
#include "../../inc/protocol/GameP.h"
#include "../../inc/role/GameR.h"



GameCF::GameCF()
{
}


GameCF::~GameCF()
{
}

ZinxTcpData * GameCF::CreateTcpDataChannel(int _fd)
{
	GameC* p_gameC = new GameC(_fd);
	GameP* p_gameP = new GameP();
	GameR* p_gameR = new GameR();

	p_gameC->bindProtocol(p_gameP);
	p_gameP->bindChannel(p_gameC);
	p_gameP->bindRole(p_gameR);
	p_gameR->bindProtocol(p_gameP);
	
	ZinxKernel::Zinx_Add_Proto(*p_gameP);
	ZinxKernel::Zinx_Add_Role(*p_gameR);


	return p_gameC;
}
