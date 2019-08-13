#include <iostream>
#include "../inc/channel/GameCF.h"
#include "../inc/channel/TimeoutC.h"
#include "../inc/channel/TimeoutDispIC.h"
#include "../inc/channel/TimeoutDispOC.h"
#include "../inc/protocol/TimeoutP.h"
#include "../inc/protocol/TimeoutDisprP.h"

using namespace std;

void daemon()
{
	int pid = fork();
	switch(pid)
	{
	case -1:
		exit(-1);
	case 0:
		{
		restart:
			int pid = fork();
			int status;
			switch (pid)
			{
			case -1:
				exit(-2);
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
				wait(&status);
				if (0 != status)goto restart;
				exit(0);
			}

			
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
		Ichannel* p_timeoutC = new TimeoutC;
		Ichannel* p_timeoutDispIC = new TimeoutDispIC;
		Ichannel* p_timeoutDispOC = new TimeoutDispOC;
		
		ZinxKernel::Zinx_Add_Channel(*p_gameC);
		ZinxKernel::Zinx_Add_Channel(*p_timeoutC);
		ZinxKernel::Zinx_Add_Channel(*p_timeoutDispOC);
		ZinxKernel::Zinx_Add_Channel(*p_timeoutDispIC);


		ZinxKernel::Zinx_Add_Proto(TimeoutP::getInstance());
		ZinxKernel::Zinx_Add_Proto(TimeoutDisprP::getInstance());


		ZinxKernel::Zinx_Run();

		ZinxKernel::Zinx_Del_Channel(*p_gameC);
		ZinxKernel::Zinx_Del_Channel(*p_timeoutC);
		ZinxKernel::Zinx_Del_Channel(*p_timeoutDispIC);
		ZinxKernel::Zinx_Del_Channel(*p_timeoutDispOC);
		delete(p_gameC);
		delete(p_timeoutC);
		delete(p_timeoutDispIC);
		delete(p_timeoutDispOC);

		ZinxKernel::Zinx_Del_Proto(TimeoutP::getInstance());
		ZinxKernel::Zinx_Del_Proto(TimeoutDisprP::getInstance());

		ZinxKernel::ZinxKernelFini();
	}

	return 0;
}