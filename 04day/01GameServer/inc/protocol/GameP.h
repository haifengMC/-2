#pragma once

#include <zinx.h>

class GameP :
	public Iprotocol
{
	Ichannel* p_gameC = NULL;
	Irole* p_gameR = NULL;
public:
	GameP();
	virtual ~GameP();

	void bindChannel(Ichannel * &&p_gameC) { this->p_gameC = p_gameC; }
	void bindRole(Irole* &&p_gameR) { this->p_gameR = p_gameR; }

	// ͨ�� Iprotocol �̳�
	virtual UserData * raw2request(std::string _szInput) override;
	virtual std::string * response2raw(UserData & _oUserData) override;
	virtual Irole * GetMsgProcessor(UserDataMsg & _oUserDataMsg) override;
	virtual Ichannel * GetMsgSender(BytesMsg & _oBytes) override;
};

