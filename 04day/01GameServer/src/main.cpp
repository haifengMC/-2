#include <iostream>
#include "../inc/channel/GameCF.h"

using namespace std;

int main()
{
	if (ZinxKernel::ZinxKernelInit())
	{
		Ichannel* p_gameC = new ZinxTCPListen(8080, new GameCF);
		ZinxKernel::Zinx_Add_Channel(*p_gameC);

		ZinxKernel::Zinx_Run();

		ZinxKernel::ZinxKernelFini();
	}

	return 0;
}