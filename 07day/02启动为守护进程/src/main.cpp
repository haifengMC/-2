#include <iostream>
#include "../inc/channel/GameCF.h"

using namespace std;

void daemon()
{
	int pid = fork();
	switch(pid)
	{
	case 1:
		exit(-1);
	case 0:
		{
			int fd = open("/dev/null", O_RDWR);

			if (fd > 0)
			{
				setsid();
				
				dup2(fd, STDIN_FILENO);
				dup2(fd, STDOUT_FILENO);
				dup2(fd, STDERR_FILENO);
			}

			close(fd);
		}
		break;
	default:
		exit(0);
	}
}


int main()
{
	daemon();

	if (ZinxKernel::ZinxKernelInit())
	{
		Ichannel* p_gameC = new ZinxTCPListen(8080, new GameCF);
		ZinxKernel::Zinx_Add_Channel(*p_gameC);

		ZinxKernel::Zinx_Run();

		ZinxKernel::Zinx_Del_Channel(*p_gameC);
		delete(p_gameC);
		ZinxKernel::ZinxKernelFini();
	}

	return 0;
}