#pragma once
#include "zinx.h"
#include <list>
#include <map>

#include "../../inc/role/TimeoutTaskR.h"

class TimeoutP :
	public Iprotocol
{
	struct _TaskData
	{
		int* pcount;
		std::list<TimeoutTaskR*> ptt_list;
	};
public:
	TimeoutP();
	virtual ~TimeoutP();


	static TimeoutP& getInstance();
	static void registerTask(TimeoutTaskR & tt);
	static void unregisterTask(const TimeoutTaskR & tt);
	// Í¨¹ý Iprotocol ¼Ì³Ð
	virtual UserData * raw2request(std::string _szInput) override;
	virtual std::string * response2raw(UserData & _oUserData) override;
	virtual Irole * GetMsgProcessor(UserDataMsg & _oUserDataMsg) override;
	virtual Ichannel * GetMsgSender(BytesMsg & _oBytes) override;

private:
	static TimeoutP s_timeout;
	static std::map<int, _TaskData*> timeout_map;

	bool findInList(const TimeoutTaskR* const & ptt,
		const std::list<TimeoutTaskR*>& ptt_list);
};

