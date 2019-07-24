/*
---------------------------------------------------------
	添加标准输出通道stdout_channel，来实现简单的回显
	补充完整框架的步骤
---------------------------------------------------------
*/

#include "../inc/02sendout.h"

int main()
{
	//1.初始化框架核心
	ZinxKernel::ZinxKernelInit();
	//2.创建数据处理类echo-->继承类AZinxHandler
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

