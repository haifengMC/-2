/*
---------------------------------------------------------
	简单的回显
---------------------------------------------------------
*/

#include "01echo.h"

int main()
{
	//1.初始化框架核心
	ZinxKernel::ZinxKernelInit();
	//2.创建数据处理类echo-->继承类AZinxHandler
	//3.创建IO通道类stdin_channel-->继承Ichannel
	//定义一个stdin_channel对象
	stdin_channel *pstdin = new stdin_channel();
	//4.添加通道类对象到核心中
	ZinxKernel::Zinx_Add_Channel(*pstdin);
	//5.调用Zinx_Run运行
	ZinxKernel::Zinx_Run();

	return 0;
}


