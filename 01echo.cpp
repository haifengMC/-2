/*
---------------------------------------------------------
	�򵥵Ļ���
---------------------------------------------------------
*/

#include "01echo.h"

int main()
{
	//1.��ʼ����ܺ���
	ZinxKernel::ZinxKernelInit();
	//2.�������ݴ�����echo-->�̳���AZinxHandler
	//3.����IOͨ����stdin_channel-->�̳�Ichannel
	//����һ��stdin_channel����
	stdin_channel *pstdin = new stdin_channel();
	//4.���ͨ������󵽺�����
	ZinxKernel::Zinx_Add_Channel(*pstdin);
	//5.����Zinx_Run����
	ZinxKernel::Zinx_Run();

	return 0;
}


