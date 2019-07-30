#pragma once
#include "zinx.h"
#include <array>
#include <list>
#include <map>

#include "../../inc/role/TimeoutTaskR.h"

#define TIME_WHEEL_LEN 16

using namespace std;

class TimeoutP :
	public Iprotocol
{
	struct _TaskKey
	{
		const int sec;
		int const* pcount;

		~_TaskKey()
		{
			if (NULL != pcount)
				delete pcount;
		}
		bool operator==(const _TaskKey& tk)
		{
			if (sec == tk.sec && *pcount == *tk.pcount)
			{
				return true;
			}
		}
		bool operator<(const _TaskKey& tk) const
		{
			if (sec < tk.sec) return true;
			else if (sec == tk.sec && *pcount < *tk.pcount)return true;
			else return false;
		}
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
	static uint64_t s_oldScale;
	static uint64_t s_timeWheelScale;
	static array<list<multimap<_TaskKey, TimeoutTaskR*>*>, TIME_WHEEL_LEN> s_timeWheel;
	//static std::map<int, _TaskData*> timeout_map;

	static bool findInMap(
		const TimeoutTaskR * const & ptt,
		multimap<const _TaskKey, TimeoutTaskR*>::iterator& ptt_it,
		multimap<_TaskKey, TimeoutTaskR*>& ptt_list);
	static void insertNewMap(
		TimeoutTaskR & tt, 
		list<multimap<_TaskKey, TimeoutTaskR*>*>& s_wheelList);
};

