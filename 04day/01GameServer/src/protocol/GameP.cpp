#include "../../inc/protocol/GameP.h"
#include "../../inc/protocol/GameMsgList.h"



GameP::GameP()
{
}


GameP::~GameP()
{
}

UserData * GameP::raw2request(std::string _szInput)
{
	rawSerialization.append(_szInput);
	GameMsgList* p_gameMsgList = new GameMsgList;

	while (true)
	{
		if (8 > rawSerialization.size())
		{
			break;
		}

		size_t msgLen = (unsigned char)rawSerialization[0];
		msgLen |= (unsigned char)rawSerialization[1] << 8;
		msgLen |= (unsigned char)rawSerialization[2] << 16;
		msgLen |= (unsigned char)rawSerialization[3] << 24;
		size_t msgId = (unsigned char)rawSerialization[4];
		msgId |= (unsigned char)rawSerialization[5] << 8;
		msgId |= (unsigned char)rawSerialization[6] << 16;
		msgId |= (unsigned char)rawSerialization[7] << 24;

		if (msgLen + 8 > rawSerialization.size())
		{
			break;
		}

		GameMsg* p_userData =
			new GameMsg((GameMsg::MSG_TYPE)msgId, rawSerialization.substr(8, msgLen));
		p_gameMsgList->addMsg(p_userData);
		
		rawSerialization.erase(0, 8 + msgLen);
	}
	

	return p_gameMsgList;
}

std::string * GameP::response2raw(UserData & _oUserData)
{
	string* rawSerialization = new string;

	GET_REF2DATA(GameMsg, gameMsg, _oUserData);
	
	rawSerialization->append(
		{
			(char)(gameMsg.getSize() & 0xff),
			(char)(gameMsg.getSize() >> 8 & 0xff),
			(char)(gameMsg.getSize() >> 16 & 0xff),
			(char)(gameMsg.getSize() >> 24 & 0xff)
		});
	rawSerialization->append(
		{
			(char)(gameMsg.getId() & 0xff),
			(char)(gameMsg.getId() >> 8 & 0xff),
			(char)(gameMsg.getId() >> 16 & 0xff),
			(char)(gameMsg.getId() >> 24 & 0xff)
		});

	rawSerialization->append(gameMsg.serialize());

	return rawSerialization;
}

Irole * GameP::GetMsgProcessor(UserDataMsg & _oUserDataMsg)
{
	return p_gameR;
}

Ichannel * GameP::GetMsgSender(BytesMsg & _oBytes)
{
	return p_gameC;
}
