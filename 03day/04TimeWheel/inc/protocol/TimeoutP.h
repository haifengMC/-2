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
	struct _TaskCountGrp
	{
		typedef list<TimeoutTaskR*>::iterator PTTit;
		int* pcount;
		list<TimeoutTaskR*> timeTask;

		_TaskCountGrp(int *const &pcount);

		bool empty();
		void clear();
		void pushback(TimeoutTaskR * const & ttask);
		PTTit insert(const PTTit& pos, const PTTit& beg, const PTTit& end);
		void remove(TimeoutTaskR * const & ttask);
		PTTit erase(const PTTit& beg, const PTTit& end);
		list<TimeoutTaskR*>::iterator begin();
		list<TimeoutTaskR*>::iterator end();
	};
	struct _TaskGrp
	{
		typedef list<_TaskCountGrp>::iterator TCGit;
		int sec_key;
		list<_TaskCountGrp> taskCountGrp;

		_TaskGrp(const int& sec_key);

		bool empty();
		void clear();
		void pushback(const _TaskCountGrp & tcg);
		TCGit insert(const TCGit& pos, const TCGit& beg, const TCGit& end);
		void remove(const _TaskCountGrp & tcg);
		TCGit erase(const TCGit& beg, const TCGit& end);
		list<_TaskCountGrp>::iterator begin();
		list<_TaskCountGrp>::iterator end();
	};
	struct _Scale
	{
		typedef list<_TaskGrp>::iterator TGit;
		list<_TaskGrp> taskGrp;

		bool empty();
		void clear();
		void pushback(const _TaskGrp & tg);
		TGit insert(const TGit& pos, const TGit& beg, const TGit& end);
		void remove(const _TaskGrp & tg);
		TGit erase(const TGit& beg, const TGit& end);
		TGit begin();
		TGit end();

	};
public:
	TimeoutP();
	virtual ~TimeoutP();


	static TimeoutP& getInstance();
	static void registerTask(TimeoutTaskR & tt);
	static void unregisterTask(TimeoutTaskR & tt);
	// Í¨¹ý Iprotocol ¼Ì³Ð
	virtual UserData * raw2request(std::string _szInput) override;
	virtual std::string * response2raw(UserData & _oUserData) override;
	virtual Irole * GetMsgProcessor(UserDataMsg & _oUserDataMsg) override;
	virtual Ichannel * GetMsgSender(BytesMsg & _oBytes) override;

private:
	static TimeoutP s_timeout;
	static uint64_t s_oldScale;
	static uint64_t s_timeWheelScale;

	static _Scale* s_timewheel;
	//static list<multimap<_TaskKey, TimeoutTaskR*>*> s_timeWheel[TIME_WHEEL_LEN];
	////static std::map<int, _TaskData*> timeout_map;

	//static bool findInMap(
	//	const TimeoutTaskR * const & ptt,
	//	multimap<const _TaskKey, TimeoutTaskR*>::iterator& ptt_it,
	//	multimap<_TaskKey, TimeoutTaskR*>& ptt_list);
	//static void insertNewMap(
	//	TimeoutTaskR & tt, 
	//	list<map<int, TaskData_List>*>& scale_list);
	static void updataScale(_Scale& scale);
};

