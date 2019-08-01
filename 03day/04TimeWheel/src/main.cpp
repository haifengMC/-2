/*
--------------------------------
	������ģ���ع���������
--------------------------------
*/
#include <string>

#include "../inc/channel/StdinC.h"
#include "../inc/channel/StdoutC.h"
#include "../inc/channel/TimeoutC.h"
#include "../inc/channel/TimeoutDispIC.h"
#include "../inc/channel/TimeoutDispOC.h"

#include "../inc/protocol/CmdPrsP.h"
#include "../inc/protocol/TimeoutP.h"
#include "../inc/protocol/TimeoutDisprP.h"

#include "../inc/role/EchoR.h"
#include "../inc/role/ExitR.h"
#include "../inc/role/OMngR.h"
#include "../inc/role/TimeoutTaskR.h"

using namespace std;

int main()
{
	//1.��ʼ������
	if (ZinxKernel::ZinxKernelInit())
	{
		//2.1.���ͨ��
		Ichannel* p_stdinC = new StdinC;
		Ichannel* p_stdoutC = new StdoutC;
		Ichannel* p_timeoutC = new TimeoutC;
		Ichannel* p_timeoutDispIC = new TimeoutDispIC;
		Ichannel* p_timeoutDispOC = new TimeoutDispOC;
		ZinxKernel::Zinx_Add_Channel(*p_stdinC);
		ZinxKernel::Zinx_Add_Channel(*p_stdoutC);
		ZinxKernel::Zinx_Add_Channel(*p_timeoutC);
		ZinxKernel::Zinx_Add_Channel(*p_timeoutDispOC);
		ZinxKernel::Zinx_Add_Channel(*p_timeoutDispIC);
		//2.2.���Э��
		ZinxKernel::Zinx_Add_Proto(CmdPrsP::getInstance());
		ZinxKernel::Zinx_Add_Proto(TimeoutP::getInstance());
		ZinxKernel::Zinx_Add_Proto(TimeoutDisprP::getInstance());
		//2.3.��ӽ�ɫ
		Irole* p_echoR = new EchoR;
		Irole* p_exitR = new ExitR;
		Irole* p_oMngR = new OMngR;
		Irole* p_task1 = new TimeoutTaskR("task1", 3);
		Irole* p_task2 = new TimeoutTaskR("task2", 1);
		Irole* p_task3 = new TimeoutTaskR("task3", 3);
		Irole* p_task4 = new TimeoutTaskR("task4", 17);
		ZinxKernel::Zinx_Add_Role(*p_echoR); 
		ZinxKernel::Zinx_Add_Role(*p_exitR);
		ZinxKernel::Zinx_Add_Role(*p_oMngR);
		ZinxKernel::Zinx_Add_Role(*p_task1);
		ZinxKernel::Zinx_Add_Role(*p_task2);
		ZinxKernel::Zinx_Add_Role(*p_task3);
		ZinxKernel::Zinx_Add_Role(*p_task4);
		//2.4.������Э��
		CmdPrsP::addRole("echo", p_echoR);
		CmdPrsP::addRole("exit", p_exitR);
		CmdPrsP::addRole("open", p_oMngR);
		CmdPrsP::addRole("close", p_oMngR);
		//3.����
		ZinxKernel::Zinx_Run();
		//4.1.ժ��ͨ��
		ZinxKernel::Zinx_Del_Channel(*p_stdinC);
		ZinxKernel::Zinx_Del_Channel(*p_stdoutC);
		ZinxKernel::Zinx_Del_Channel(*p_timeoutC);
		ZinxKernel::Zinx_Del_Channel(*p_timeoutDispIC);
		ZinxKernel::Zinx_Del_Channel(*p_timeoutDispOC);
		delete(p_stdinC);
		delete(p_stdoutC);
		delete(p_timeoutC);
		delete(p_timeoutDispIC);
		delete(p_timeoutDispOC);
		//4.2.ժ��Э��
		ZinxKernel::Zinx_Del_Proto(CmdPrsP::getInstance());
		ZinxKernel::Zinx_Del_Proto(TimeoutP::getInstance());
		ZinxKernel::Zinx_Del_Proto(TimeoutDisprP::getInstance());
		//4.3.ժ����ɫ
		ZinxKernel::Zinx_Del_Role(*p_echoR);
		ZinxKernel::Zinx_Del_Role(*p_exitR);
		ZinxKernel::Zinx_Del_Role(*p_oMngR);
		ZinxKernel::Zinx_Del_Role(*p_task1);
		ZinxKernel::Zinx_Del_Role(*p_task2);
		ZinxKernel::Zinx_Del_Role(*p_task3);
		ZinxKernel::Zinx_Del_Role(*p_task4);
		delete(p_echoR);
		delete(p_exitR);
		delete(p_oMngR);
		delete(p_task1);
		delete(p_task2);
		delete(p_task3);
		delete(p_task4);
		//5.�ͷź���
		ZinxKernel::ZinxKernelFini();
	}

	return 0;
}