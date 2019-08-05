#include "GameMsg.protoc.pb.h"

using namespace std;

#define p(X)\
	for (unsigned char c : X)\
	{\
		printf("%02X ", c);\
	}\
	cout << endl


int main()
{
	//1号消息或201号消息，客户端记录自己ID和姓名，或将该ID从画面中拿掉
	{
		GameMsg::SyncPlyrId syncPlyrId;
		syncPlyrId.set_plyrid(100);
		syncPlyrId.set_usrname("syw");
		string plyrIdMsg;
		syncPlyrId.AppendToString(&plyrIdMsg);
		p(plyrIdMsg);
		GameMsg::SyncPlyrId syncPlyrId_;
		syncPlyrId_.ParseFromString(plyrIdMsg);
		cout << "plyrId : " << syncPlyrId_.plyrid() << endl;
		cout << "usrName : " << syncPlyrId_.usrname() << endl; 
	}


	//2号消息，聊天内容
	{
		GameMsg::Chat chat;
		chat.set_content("hello!");
		string chatMsg;
		chat.AppendToString(&chatMsg);
		p(chatMsg);
		GameMsg::Chat chat_;
		chat_.ParseFromString(chatMsg);
		cout << "content : " << chat_.content() << endl;
	}


	//3号消息，服务器处理玩家位置更新后的信息同步
	{
		GameMsg::PlyrPos plyrPos;
		plyrPos.set_x(1.0);
		plyrPos.set_y(1.0);
		plyrPos.set_z(1.0);
		plyrPos.set_v(1.0);
		plyrPos.set_bloodvalue(5);
		string plyrPosMsg;
		plyrPos.AppendToString(&plyrPosMsg);
		p(plyrPosMsg);
		GameMsg::PlyrPos plyrPos_;
		plyrPos_.ParseFromString(plyrPosMsg);
		cout << "X : " << plyrPos_.x() << endl;
		cout << "Y : " << plyrPos_.y() << endl;
		cout << "Z : " << plyrPos_.z() << endl;
		cout << "V : " << plyrPos_.v() << endl;
		cout << "bloodValue : " << plyrPos_.bloodvalue() << endl;
	}



	//玩家信息：id，姓名，坐标
	{
		GameMsg::Plyr plyr;
		plyr.set_plyrid(100);
		plyr.set_usrname("syw");
		GameMsg::PlyrPos* p_plyrPos = plyr.mutable_plyrpos();
		p_plyrPos->set_x(1.0);
		p_plyrPos->set_y(1.0);
		p_plyrPos->set_z(1.0);
		p_plyrPos->set_v(1.0);
		p_plyrPos->set_bloodvalue(5);
		string plyrMsg;
		plyr.AppendToString(&plyrMsg);
		p(plyrMsg);
		GameMsg::Plyr plyr_;
		plyr_.ParseFromString(plyrMsg);
		cout << "plyrId : " << plyr_.plyrid() << endl;
		cout << "usrName : " << plyr_.usrname() << endl;
		cout << "X : " << plyr_.plyrpos().x() << endl;
		cout << "Y : " << plyr_.plyrpos().y() << endl;
		cout << "Z : " << plyr_.plyrpos().z() << endl;
		cout << "V : " << plyr_.plyrpos().v() << endl;
		cout << "bloodValue : " << plyr_.plyrpos().bloodvalue() << endl;
	}



	//202号消息，同步周围玩家信息 
	{
		GameMsg::SyncPlyrs syncPlyrs;
		GameMsg::Plyr* p_plyr1 = syncPlyrs.add_plyrs();
		p_plyr1->set_plyrid(100);
		p_plyr1->set_usrname("syw");
		GameMsg::PlyrPos* p_plyrPos1 = p_plyr1->mutable_plyrpos();
		p_plyrPos1->set_x(1.0);
		p_plyrPos1->set_y(1.0);
		p_plyrPos1->set_z(1.0);
		p_plyrPos1->set_v(1.0);
		p_plyrPos1->set_bloodvalue(5);

		GameMsg::Plyr* p_plyr2 = syncPlyrs.add_plyrs();
		p_plyr2->set_plyrid(200);
		p_plyr2->set_usrname("lulu");
		GameMsg::PlyrPos* p_plyrPos2 = p_plyr2->mutable_plyrpos();
		p_plyrPos2->set_x(1.0);
		p_plyrPos2->set_y(1.0);
		p_plyrPos2->set_z(1.0);
		p_plyrPos2->set_v(1.0);
		p_plyrPos2->set_bloodvalue(5);

		string syncPlyrsMsg;
		syncPlyrs.AppendToString(&syncPlyrsMsg);
		p(syncPlyrsMsg);
		
		GameMsg::SyncPlyrs syncPlyrs_;
		syncPlyrs_.ParseFromString(syncPlyrsMsg);
		for (int i = 0; i < syncPlyrs_.plyrs_size(); i++)
		{
			const GameMsg::Plyr& plyr_ = syncPlyrs_.plyrs(i);
			cout << "i : " << i << endl;
			cout << "plyrId : " << plyr_.plyrid() << endl;
			cout << "usrName : " << plyr_.usrname() << endl;
			cout << "X : " << plyr_.plyrpos().x() << endl;
			cout << "Y : " << plyr_.plyrpos().y() << endl;
			cout << "Z : " << plyr_.plyrpos().z() << endl;
			cout << "V : " << plyr_.plyrpos().v() << endl;
			cout << "bloodValue : " << plyr_.plyrpos().bloodvalue() << endl;
		}


		//200号消息
		enum { CHAT, POS, MOVE };
		{
			GameMsg::BroadCast broadcastChat;
			broadcastChat.set_plyrid(100);
			broadcastChat.set_bctype(CHAT);
			GameMsg::Chat* p_chat = broadcastChat.mutable_plyrchat();
			p_chat->set_content("hello");
			broadcastChat.set_usrname("syw");

			string chatMsg;
			broadcastChat.AppendToString(&chatMsg);
			p(chatMsg);

			GameMsg::BroadCast broadcastChat_;
			broadcastChat_.ParseFromString(chatMsg);

			cout << "plyrId : " << broadcastChat_.plyrid() << endl;
			cout << "bcType : " << broadcastChat_.bctype() << endl;
			cout << "usrName : " << broadcastChat_.usrname() << endl;
			cout << "Data : " << broadcastChat_.plyrchat().content() << endl;
		}
		{
			GameMsg::BroadCast broadcastPos;
			broadcastPos.set_plyrid(200);
			broadcastPos.set_bctype(POS);
			broadcastPos.set_usrname("lulu");
			GameMsg::PlyrPos* p_plyrPos = broadcastPos.mutable_plyrpos();
			p_plyrPos->set_x(1.0);
			p_plyrPos->set_y(1.0);
			p_plyrPos->set_z(1.0);
			p_plyrPos->set_v(1.0);
			p_plyrPos->set_bloodvalue(5);

			string posMsg;
			broadcastPos.AppendToString(&posMsg);
			p(posMsg);

			GameMsg::BroadCast broadcastPos_;
			broadcastPos_.ParseFromString(posMsg);

			cout << "plyrId : " << broadcastPos_.plyrid() << endl;
			cout << "bcType : " << broadcastPos_.bctype() << endl;
			cout << "usrName : " << broadcastPos_.usrname() << endl;
			cout << "Data : " << endl;
			cout << "X : " << broadcastPos_.plyrpos().x() << endl;
			cout << "Y : " << broadcastPos_.plyrpos().y() << endl;
			cout << "Z : " << broadcastPos_.plyrpos().z() << endl;
			cout << "V : " << broadcastPos_.plyrpos().v() << endl;
			cout << "bloodValue : " << broadcastPos_.plyrpos().bloodvalue() << endl;
		}
		{
			GameMsg::BroadCast broadcastMove;
			broadcastMove.set_plyrid(300);
			broadcastMove.set_bctype(MOVE);
			broadcastMove.set_usrname("mjs");
			GameMsg::PlyrPos* p_plyrMove = broadcastMove.mutable_plyrpos();
			p_plyrMove->set_x(1.0);
			p_plyrMove->set_y(1.0);
			p_plyrMove->set_z(1.0);
			p_plyrMove->set_v(1.0);
			p_plyrMove->set_bloodvalue(5);

			string moveMsg;
			broadcastMove.AppendToString(&moveMsg);
			p(moveMsg);

			GameMsg::BroadCast broadcastMove_;
			broadcastMove_.ParseFromString(moveMsg);

			cout << "plyrId : " <<broadcastMove_.plyrid() << endl;
			cout << "bcType : " <<broadcastMove_.bctype() << endl;
			cout << "usrName : " << broadcastMove_.usrname() << endl;
			cout << "Data : " << endl;
			cout << "X : " << broadcastMove_.plyrpos().x() << endl;
			cout << "Y : " << broadcastMove_.plyrpos().y() << endl;
			cout << "Z : " << broadcastMove_.plyrpos().z() << endl;
			cout << "V : " << broadcastMove_.plyrpos().v() << endl;
			cout << "bloodValue : " << broadcastMove_.plyrpos().bloodvalue() << endl;
		}
	}


}