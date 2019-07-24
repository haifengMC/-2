/*
---------------------------------------------------------
	��ӱ�׼���ͨ��stdout_channel����ʵ�ּ򵥵Ļ���
	����������ܵĲ���
---------------------------------------------------------
*/

#include "../inc/02sendout.h"

int main()
{
	//1.��ʼ����ܺ���
	ZinxKernel::ZinxKernelInit();
	//2.�������ݴ�����echo-->�̳���AZinxHandler
	//3.1.����IOͨ����stdin_channel-->�̳�Ichannel
	//3.2.����IOͨ����stdout_channel-->�̳�Ichannel
	//����һ��stdin_channel����
	stdin_channel *pstdin = new stdin_channel();
	stdout_channel *pstdout = new stdout_channel();
	//4.���ͨ������󵽺�����
	ZinxKernel::Zinx_Add_Channel(*pstdin);
	ZinxKernel::Zinx_Add_Channel(*pstdout);
	//5.����Zinx_Run����
	ZinxKernel::Zinx_Run();
	//6.���к�Ӻ�����ժ��ͨ��
	ZinxKernel::Zinx_Del_Channel(*pstdin);
	ZinxKernel::Zinx_Del_Channel(*pstdout);
	//7.�ͷ��ڴ�
	delete pstdin;
	delete pstdout;
	//8.��������
	ZinxKernel::ZinxKernelFini();

	return 0;
}

