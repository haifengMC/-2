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
	struct _TaskData
	{
		int const* pcount;
		list<const TimeoutTaskR*> task_list;

		_TaskData(int const* pcount) : pcount(pcount)
		{

		}
		~_TaskData()
		{
			delete pcount;
		}
	};
	typedef list<_TaskData*> TaskData_List;
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

	static list<map<int,TaskData_List>*> s_timeWheel[TIME_WHEEL_LEN];
	//static list<multimap<_TaskKey, TimeoutTaskR*>*> s_timeWheel[TIME_WHEEL_LEN];
	////static std::map<int, _TaskData*> timeout_map;

	//static bool findInMap(
	//	const TimeoutTaskR * const & ptt,
	//	multimap<const _TaskKey, TimeoutTaskR*>::iterator& ptt_it,
	//	multimap<_TaskKey, TimeoutTaskR*>& ptt_list);
	static void insertNewMap(
		TimeoutTaskR & tt, 
		list<map<int, TaskData_List>*>& scale_list);
	static void updataTaskMap(
		map<int, TaskData_List>*& tdl_map,
		list<map<int, TaskData_List>*>&  scale_list);
};

