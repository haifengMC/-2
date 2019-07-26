#pragma once
#include "zinx.h"

class TimeoutP :
	public Iprotocol
{
public:
	TimeoutP();
	virtual ~TimeoutP();

	static TimeoutP& getInstance();
	// Í¨¹ý Iprotocol ¼Ì³Ð
	virtual UserData * raw2request(std::string _szInput) override;
	virtual std::string * response2raw(UserData & _oUserData) override;
	virtual Irole * GetMsgProcessor(UserDataMsg & _oUserDataMsg) override;
	virtual Ichannel * GetMsgSender(BytesMsg & _oBytes) override;

private:
	static TimeoutP s_timeout;
};

