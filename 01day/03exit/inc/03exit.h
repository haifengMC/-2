#pragma once
#include <iostream>
#include <zinx.h>

using namespace std;

//2.1.�������ݴ�����Echo-->�̳���AZinxHandler
class Echo : public AZinxHandler
{
	// ͨ�� AZinxHandler �̳�
	virtual IZinxMsg * InternelHandle(IZinxMsg & _oInput) override;
	virtual AZinxHandler * GetNextHandler(IZinxMsg & _oNextMsg) override;
};
extern Echo g_echo;

//2.2.�������ݴ�����ExitFrame-->�̳���AZinxHandler
class ExitFrame : public AZinxHandler
{
	// ͨ�� AZinxHandler �̳�
	virtual IZinxMsg * InternelHandle(IZinxMsg & _oInput) override;
	virtual AZinxHandler * GetNextHandler(IZinxMsg & _oNextMsg) override;
};
extern ExitFrame g_exit;

//2.3.�������ݴ�����Cmd-->�̳���AZinxHandler
class Cmd : public AZinxHandler
{
	// ͨ�� AZinxHandler �̳�
	virtual IZinxMsg * InternelHandle(IZinxMsg & _oInput) override;
	virtual AZinxHandler * GetNextHandler(IZinxMsg & _oNextMsg) override;
};
extern Cmd g_cmd;

//3.1.����IOͨ����stdin_channel-->�̳�Ichannel��
class stdin_channel : public Ichannel
{
	// ͨ�� Ichannel �̳�
	virtual bool Init() override;
	//���ļ����ӱ�׼���������
	virtual bool ReadFd(std::string & _input) override;
	//д�ļ�������Ҫ���׼����д���ݣ��ɺ���
	virtual bool WriteFd(std::string & _output) override;
	//������������ã��޲���
	virtual void Fini() override;
	virtual int GetFd() override;
	virtual std::string GetChannelInfo() override;
	//��ȡ��һ��������,ָ��Ϊg_echo
	virtual AZinxHandler * GetInputNextStage(BytesMsg & _oInput) override;
};

//3.2.����IOͨ����stdout_channel-->�̳�Ichannel
class stdout_channel : public Ichannel
{
	// ͨ�� Ichannel �̳�
	virtual bool Init() override;
	virtual bool ReadFd(std::string & _input) override;
	virtual bool WriteFd(std::string & _output) override;
	virtual void Fini() override;
	virtual int GetFd() override;
	virtual std::string GetChannelInfo() override;
	virtual AZinxHandler * GetInputNextStage(BytesMsg & _oInput) override;
};
