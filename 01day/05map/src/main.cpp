/*
---------------------------------------------------------
	在命令管理类Cmd里添加一个map，将命令放进去
---------------------------------------------------------
*/

#include "../inc/05map.h"


int main()
{
	//1.初始化框架核心
	ZinxKernel::ZinxKernelInit();
	//2.1.创建数据处理类Echo-->继承类AZinxHandler
	//2.2.创建数据处理类ExitFrame-->继承类AZinxHandler
	//2.3.创建数据处理类Cmd-->继承类AZinxHandler
	//	2.3.1.在命令管理类Cmd里添加一个map，将命令放进去
	g_cmd.add_handle("exit", &g_exit);
	g_cmd.add_handle("open", &g_omng);
	g_cmd.add_handle("close", &g_omng);
	//2.4.创建数据处理类OMng-->继承类AZinxHandler

	//3.1.创建IO通道类stdin_channel-->继承Ichannel
	//3.2.创建IO通道类stdout_channel-->继承Ichannel
	//定义一个stdin_channel对象
	stdin_channel *pstdin = new stdin_channel();
	stdout_channel *pstdout = new stdout_channel();
	//4.添加通道类对象到核心中
	ZinxKernel::Zinx_Add_Channel(*pstdin);
	ZinxKernel::Zinx_Add_Channel(*pstdout);
	//5.调用Zinx_Run运行
	ZinxKernel::Zinx_Run();
	//6.运行后从核心中摘除通道
	ZinxKernel::Zinx_Del_Channel(*pstdin);
	ZinxKernel::Zinx_Del_Channel(*pstdout);
	//7.释放内存
	delete pstdin;
	delete pstdout;
	//8.结束核心
	ZinxKernel::ZinxKernelFini();

	return 0;
}
