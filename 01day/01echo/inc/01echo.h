#pragma once
#include <iostream>
#include <zinx.h>

using namespace std;


//2.�������ݴ�����echo-->�̳���AZinxHandler
class echo : public AZinxHandler
{
	// ͨ�� AZinxHandler �̳�
	virtual IZinxMsg * InternelHandle(IZinxMsg & _oInput) override
	{
		//�������������׼���
		GET_REF2DATA(BytesMsg, byte, _oInput);
		cout << byte.szData << endl;

		return nullptr;
	}

	virtual AZinxHandler * GetNextHandler(IZinxMsg & _oNextMsg) override
	{
		//û����һ������
		return nullptr;
	}

};
echo g_echo;

//3.����IOͨ����stdin_channel-->�̳�Ichannel��
class stdin_channel : public Ichannel
{
	// ͨ�� Ichannel �̳�
	virtual bool Init() override
	{
		//�����ʼ����ֱ�ӷ���true��ʾ��ʼ���ɹ�
		return true;
	}
	//���ļ����ӱ�׼���������
	virtual bool ReadFd(std::string & _input) override
	{
		cin >> _input;
		return true;
	}
	//д�ļ�������Ҫ���׼����д���ݣ��ɺ���
	virtual bool WriteFd(std::string & _output) override
	{
		return false;
	}
	//������������ã��޲���
	virtual void Fini() override
	{
	}
	virtual int GetFd() override
	{
		return STDIN_FILENO;
	}
	virtual std::string GetChannelInfo() override
	{
		return "stdin_channel";
	}
	//��ȡ��һ��������,ָ��Ϊg_echo
	virtual AZinxHandler * GetInputNextStage(BytesMsg & _oInput) override
	{
		//���ش����ȡ�����ݵĶ��󣬷���g_echo����
		return &g_echo;
	}
};
