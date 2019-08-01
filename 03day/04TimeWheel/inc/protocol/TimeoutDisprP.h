#pragma once
#include "zinx.h"
#include "../role/TimeoutTaskR.h"

class TimeoutDisprP :
	public Iprotocol
{
public:
	TimeoutDisprP();
	virtual ~TimeoutDisprP();

	static TimeoutDisprP& getInstance();

	// ͨ�� Iprotocol �̳�
	virtual UserData * raw2request(std::string _szInput) override;
	virtual std::string * response2raw(UserData & _oUserData) override;
	virtual Irole * GetMsgProcessor(UserDataMsg & _oUserDataMsg) override;
	virtual Ichannel * GetMsgSender(BytesMsg & _oBytes) override;
private:
	static TimeoutDisprP td;
	TimeoutTaskR* ptt = nullptr;
};

