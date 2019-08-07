#pragma once
#include <iostream>
#include <list>

using namespace std;


struct GameMsgData
{
	virtual ~GameMsgData() = 0;
};

//1号消息或201号消息，客户端记录自己ID和姓名，或将该ID从画面中拿掉
struct SyncPlyrIdData : GameMsgData
{
	virtual ~SyncPlyrIdData() override;
	int plyrId;
	string usrName;
};

//2号消息，聊天内容
struct ChatData : GameMsgData
{
	virtual ~ChatData() override;
	string content;
};
//3号消息，服务器处理玩家位置更新后的信息同步
struct PlyrPosData : GameMsgData
{
	virtual ~PlyrPosData() override;
	float X;//横坐标
	float Y;//高
	float Z;//纵坐标
	float V;//视角（单位：度）
	int bloodValue;//血量（保留）
};

//200号消息
struct BroadCastData : GameMsgData
{
	~BroadCastData() override;
	int plyrId;
	//广播类型，1、聊天内容；2、出生位置；3、移动后的位置
	int bcType;

	//一个共用体数据
	union Data
	{
		Data() {}
		~Data() {}
		ChatData plyrChat;
		PlyrPosData plyrPos;
		//actionData暂时预留动作数据
		int actionData;
	} data;

	string usrName;
};

//玩家信息：id，姓名，坐标
struct PlyrData : GameMsgData
{
	virtual ~PlyrData() override;
	int plyrId;
	PlyrPosData plyrPos;
	string usrName;
};

//202号消息，同步周围玩家信息 
struct SyncPlyrsData : GameMsgData
{
	virtual ~SyncPlyrsData() override;
	list<PlyrData> plyrs;
};
