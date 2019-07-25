#include "../../inc/channel/TcpF.h"
#include "../../inc/channel/TcpC.h"



TcpF::TcpF()
{
}


TcpF::~TcpF()
{
}

ZinxTcpData * TcpF::CreateTcpDataChannel(int _fd)
{
	return new TcpC(_fd);
}
