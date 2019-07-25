/*
--------------------------------
	������ģ���ع���������
--------------------------------
*/


#include "../inc/channel/StdinC.h"
#include "../inc/channel/StdoutC.h"
#include "../inc/protocol/CmdPrsP.h"
#include "../inc/role/EchoR.h"
#include "../inc/role/ExitR.h"
#include "../inc/role/OMngR.h"

int main()
{
	//1.��ʼ������
	if (ZinxKernel::ZinxKernelInit())
	{
		//2.1.���ͨ��
		Ichannel* p_stdinC = new StdinC;
		Ichannel* p_stdoutC = new StdoutC;
		ZinxKernel::Zinx_Add_Channel(*p_stdinC);
		ZinxKernel::Zinx_Add_Channel(*p_stdoutC);
		//2.2.���Э��
		ZinxKernel::Zinx_Add_Proto(CmdPrsP::getInstance());
		//2.3.��ӽ�ɫ
		Irole* p_echoR = new EchoR;
		Irole* p_exitR = new ExitR;
		Irole* p_oMngR = new OMngR;
		ZinxKernel::Zinx_Add_Role(*p_echoR); 
		ZinxKernel::Zinx_Add_Role(*p_exitR);
		ZinxKernel::Zinx_Add_Role(*p_oMngR);
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
		delete(p_stdinC);
		delete(p_stdoutC);
		//4.2.ժ��Э��
		ZinxKernel::Zinx_Del_Proto(CmdPrsP::getInstance());
		//4.3.ժ����ɫ
		ZinxKernel::Zinx_Del_Role(*p_echoR);
		ZinxKernel::Zinx_Del_Role(*p_exitR);
		ZinxKernel::Zinx_Del_Role(*p_oMngR);
		delete(p_echoR);
		delete(p_exitR);
		delete(p_oMngR);
		//5.�ͷź���
		ZinxKernel::Zinx_Exit();
	}

	return 0;
}