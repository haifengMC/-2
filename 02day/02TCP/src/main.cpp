/*
--------------------------------
	用三层模型重构回显例程
--------------------------------
*/
#include "../inc/channel/StdinC.h"
#include "../inc/channel/StdoutC.h"
#include "../inc/channel/TcpF.h"
#include "../inc/protocol/CmdPrsP.h"
#include "../inc/role/EchoR.h"
#include "../inc/role/ExitR.h"
#include "../inc/role/OMngR.h"


int main()
{
	//1.初始化核心
	if (ZinxKernel::ZinxKernelInit())
	{
		//2.1.添加通道
		Ichannel* p_stdinC = new StdinC;
		Ichannel* p_stdoutC = new StdoutC;
		ZinxKernel::Zinx_Add_Channel(*p_stdinC);
		ZinxKernel::Zinx_Add_Channel(*p_stdoutC);
		//2.2.添加TCP通道
		Ichannel* p_tcpC = new ZinxTCPListen(8080, new TcpF);
		ZinxKernel::Zinx_Add_Channel(*p_tcpC);
		//2.3.添加协议
		ZinxKernel::Zinx_Add_Proto(CmdPrsP::getInstance());
		//2.4.添加角色
		Irole* p_echoR = new EchoR;
		Irole* p_exitR = new ExitR;
		Irole* p_oMngR = new OMngR;
		ZinxKernel::Zinx_Add_Role(*p_echoR); 
		ZinxKernel::Zinx_Add_Role(*p_exitR);
		ZinxKernel::Zinx_Add_Role(*p_oMngR);
		//2.5.添加命令到协议
		CmdPrsP::addRole("echo", p_echoR);
		CmdPrsP::addRole("exit", p_exitR);
		CmdPrsP::addRole("open", p_oMngR);
		CmdPrsP::addRole("close", p_oMngR);
		//3.运行
		ZinxKernel::Zinx_Run();
		//4.1.摘除通道
		ZinxKernel::Zinx_Del_Channel(*p_stdinC);
		ZinxKernel::Zinx_Del_Channel(*p_stdoutC);
		delete(p_stdinC);
		delete(p_stdoutC);
		//4.2.摘除TCP通道
		ZinxKernel::Zinx_Del_Channel(*p_tcpC);
		delete(p_tcpC);
		//4.3.摘除协议
		ZinxKernel::Zinx_Del_Proto(CmdPrsP::getInstance());
		//4.4.摘除角色
		ZinxKernel::Zinx_Del_Role(*p_echoR);
		ZinxKernel::Zinx_Del_Role(*p_exitR);
		ZinxKernel::Zinx_Del_Role(*p_oMngR);
		delete(p_echoR);
		delete(p_exitR);
		delete(p_oMngR);
		//5.释放核心
		ZinxKernel::ZinxKernelFini();
	}

	return 0;
}