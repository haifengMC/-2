#include "../../inc/channel/TcpC.h"
#include "../../inc/protocol/CmdPrsP.h"


TcpC::TcpC(int _fd) : ZinxTcpData(_fd)
{
}


TcpC::~TcpC()
{
}

AZinxHandler * TcpC::GetInputNextStage(BytesMsg & _oInput)
{
	return &CmdPrsP::getInstance();
}
