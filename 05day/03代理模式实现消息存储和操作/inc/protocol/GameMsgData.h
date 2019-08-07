#pragma once
#include <iostream>
#include <list>

using namespace std;


struct GameMsgData
{
	virtual ~GameMsgData() = 0;
};

//1����Ϣ��201����Ϣ���ͻ��˼�¼�Լ�ID���������򽫸�ID�ӻ������õ�
struct SyncPlyrIdData : GameMsgData
{
	virtual ~SyncPlyrIdData() override;
	int plyrId;
	string usrName;
};

//2����Ϣ����������
struct ChatData : GameMsgData
{
	virtual ~ChatData() override;
	string content;
};
//3����Ϣ���������������λ�ø��º����Ϣͬ��
struct PlyrPosData : GameMsgData
{
	virtual ~PlyrPosData() override;
	float X;//������
	float Y;//��
	float Z;//������
	float V;//�ӽǣ���λ���ȣ�
	int bloodValue;//Ѫ����������
};

//200����Ϣ
struct BroadCastData : GameMsgData
{
	~BroadCastData() override;
	int plyrId;
	//�㲥���ͣ�1���������ݣ�2������λ�ã�3���ƶ����λ��
	int bcType;

	//һ������������
	union Data
	{
		Data() {}
		~Data() {}
		ChatData plyrChat;
		PlyrPosData plyrPos;
		//actionData��ʱԤ����������
		int actionData;
	} data;

	string usrName;
};

//�����Ϣ��id������������
struct PlyrData : GameMsgData
{
	virtual ~PlyrData() override;
	int plyrId;
	PlyrPosData plyrPos;
	string usrName;
};

//202����Ϣ��ͬ����Χ�����Ϣ 
struct SyncPlyrsData : GameMsgData
{
	virtual ~SyncPlyrsData() override;
	list<PlyrData> plyrs;
};
