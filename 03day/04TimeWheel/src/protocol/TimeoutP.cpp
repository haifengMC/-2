#include "../../inc/protocol/TimeoutMsg.h"
#include "../../inc/protocol/TimeoutP.h"
#include "../../inc/protocol/TimeoutDisprP.h"

#define D(X) std::cout << #X", " << X << ", " << __LINE__ << endl;

TimeoutP::TimeoutP()
{
	s_timewheel = new _Scale[TIME_WHEEL_LEN];
}

TimeoutP::~TimeoutP()
{
	for (int i = 0; i < TIME_WHEEL_LEN; i++)
	{
		_Scale& s = s_timewheel[i];
		for (_TaskGrp& tg : s)
		{
			for (_TaskCountGrp& tcg : tg)
			{
				delete tcg.pcount;
			}
		}

	}

	delete[] s_timewheel;

}

TimeoutP TimeoutP::s_timeout;
uint64_t TimeoutP::s_oldScale;
uint64_t TimeoutP::s_timeWheelScale = 0;
TimeoutP::_Scale* TimeoutP::s_timewheel = NULL;
//std::map<int, TimeoutP::_TaskData*> TimeoutP::timeout_map;

TimeoutP & TimeoutP::getInstance()
{
	return s_timeout;
}

void TimeoutP::registerTask(TimeoutTaskR & tt)
{
	int scale = (s_timeWheelScale + tt.getTimeoutSec()) % TIME_WHEEL_LEN;
	int count = (s_timeWheelScale + tt.getTimeoutSec()) / TIME_WHEEL_LEN;
	
	_Scale& s = s_timewheel[scale];

	if (s.empty())
	{
		_TaskCountGrp tcg(new int(count));
		tt.setPCount(tcg.pcount);
		tcg.pushback(&tt);
		_TaskGrp tg(tt.getTimeoutSec());
		tg.pushback(tcg);
		s.pushback(tg);

		return;
	}

	for (_TaskGrp& tg : s)
	{
		if (tg.sec_key == tt.getTimeoutSec())
		{
			for (_TaskCountGrp& tcg : tg)
			{
				if (count == *tcg.pcount)
				{
					for (TimeoutTaskR*& pttask : tcg)
					{
						if (pttask == &tt)return;
					}
					tt.setPCount(tcg.pcount);
					tcg.pushback(&tt);

					return;
				}
			}
			_TaskCountGrp tcg(new int(count));
			tt.setPCount(tcg.pcount);
			tcg.pushback(&tt);
			tg.pushback(tcg);

			return;
		}
	}
	_TaskCountGrp tcg(new int(count));
	tt.setPCount(tcg.pcount);
	tcg.pushback(&tt);
	_TaskGrp tg(tt.getTimeoutSec());
	tg.pushback(tcg);
	s.pushback(tg);

	return;
}

void TimeoutP::unregisterTask(TimeoutTaskR & tt)
{
	for (int i = 0; i < TIME_WHEEL_LEN; i++)
	{
		_Scale& s = s_timewheel[i];
		for (_TaskGrp& tg : s)
		{
			if (tg.sec_key != tt.getTimeoutSec()) continue;
			for (_TaskCountGrp& tcg : tg)
			{
				if (tcg.pcount != tt.getPCount()) continue;

				tt.setPCount(NULL);
				tcg.remove(&tt);

				if (tcg.empty()) tg.remove(tcg);
			}
			if (tg.empty()) s.remove(tg);
		}
	}
}

UserData * TimeoutP::raw2request(std::string _szInput)
{
	s_oldScale = s_timeWheelScale;
	s_timeWheelScale += *(uint64_t*)_szInput.data();

	int scale = s_timeWheelScale % TIME_WHEEL_LEN;


	for (int i = s_timeWheelScale - s_oldScale - 1; i >= 0; i--)
	{

		_Scale& s = s_timewheel[i]; 

		for (_TaskGrp& tg : s)
		{
			if (tg.empty())continue;
			for (_TaskCountGrp& tcg : tg)
			{
				if (tcg.empty())continue;
				for (TimeoutTaskR*& pttask : tcg)
				{
					char buf[sizeof(TimeoutTaskR*)];
					memcpy(buf, &pttask, sizeof(TimeoutTaskR*));
					std::string str(buf, sizeof(buf));

					Ichannel* ch = ZinxKernel::
						Zinx_GetChannel_ByInfo("timeout_dispO_channel");

					ZinxKernel::Zinx_SendOut(str, *ch);
				}
			}
		}
	}
	return nullptr;
}

std::string * TimeoutP::response2raw(UserData & _oUserData)
{
	return nullptr;
}

Irole * TimeoutP::GetMsgProcessor(UserDataMsg & _oUserDataMsg)
{


	return nullptr;
}

Ichannel * TimeoutP::GetMsgSender(BytesMsg & _oBytes)
{
	return nullptr;
}

void TimeoutP::updataScale(_Scale & scale)
{
	//int scale = (s_timeWheelScale + tt.getTimeoutSec()) % TIME_WHEEL_LEN;
	//int count = (s_timeWheelScale + tt.getTimeoutSec()) / TIME_WHEEL_LEN;
	list<_TaskGrp*> del_tg;

	if (scale.empty()) return;
	for (_TaskGrp& tg : scale)
	{
		if (tg.empty()) continue;

		int m_scale = (s_timeWheelScale + tg.sec_key) % TIME_WHEEL_LEN;
		int m_count = (s_timeWheelScale + tg.sec_key) / TIME_WHEEL_LEN;


		for (_TaskGrp& tgDest : s_timewheel[m_scale])
		{
			if (tgDest.empty()) break;

			if (tg.sec_key == tgDest.sec_key)
			{
				for (_TaskCountGrp& tcg : tg)
				{
					if (tcg.empty()) continue;

					for (_TaskCountGrp& tcgDest : tgDest)
					{
						if (tcgDest.empty()) break;
						if (*tcgDest.pcount == *tcg.pcount)
						{
							tcgDest.insert(tcgDest.end(), tcg.begin(), tcg.end());
							tcg.clear();
						}
					}
				}
				tgDest.insert(tgDest.end(), tg.begin(), tg.end());
				tg.clear();
			}
		}
		s_timewheel[m_scale].pushback(tg);
		del_tg.push_back(&tg);
	}

	for (_TaskGrp* &ptg : del_tg)
	{
		scale.remove(*ptg);
	}
}

//bool TimeoutP::findInMap(
//	const TimeoutTaskR * const & ptt,
//	multimap<const _TaskKey, TimeoutTaskR*>::iterator& ptt_it,
//	multimap<_TaskKey, TimeoutTaskR*>& ptt_list)
//{
//	ptt_it = ptt_list.begin();
//	multimap<const _TaskKey, TimeoutTaskR*>::iterator ptt_it2 =
//		ptt_list.begin();
//	do 
//	{
//		if (ptt->getTimeoutSec() == ptt_it->second->getTimeoutSec())
//		{
//			if (NULL == ptt->getPCount())
//			{
//				
//				return true;
//			}
//			else if (*ptt->getPCount() == *ptt_it->second->getPCount())
//			{
//				return true;
//			}
//		}
//	}
//	while (ptt_list.end() != ++ptt_it);
//
//	ptt_it = ptt_list.end();
//
//	return false;
//}
//
//void TimeoutP::insertNewMap(
//	TimeoutTaskR & tt,
//	list<map<int, TaskData_List>*>& scale_list)
//{
//	int count = 
//		(s_timeWheelScale + tt.getTimeoutSec()) / 
//		TIME_WHEEL_LEN;
//
//	map<int, TaskData_List>* ptask_map =
//		new map<int, TaskData_List>;
//
//	TaskData_List& tdl = (*ptask_map)[tt.getTimeoutSec()];
//	_TaskData* td = new _TaskData(new int(count));
//	td->task_list.push_back(&tt);
//	tdl.push_back(td);
//
//
//	scale_list.push_back(ptask_map);
//}

bool TimeoutP::_Scale::empty()
{
	return taskGrp.empty();
}

void TimeoutP::_Scale::clear()
{
	return taskGrp.clear();
}

void TimeoutP::_Scale::pushback(const _TaskGrp & tg)
{
	taskGrp.push_back(tg);
}

TimeoutP::_Scale::TGit TimeoutP::_Scale::insert(const TGit & pos, const TGit & beg, const TGit & end)
{
	return taskGrp.insert(pos, beg, end);
}

void TimeoutP::_Scale::remove(const _TaskGrp & tg)
{
	taskGrp.remove(tg);
}

TimeoutP::_Scale::TGit TimeoutP::_Scale::erase(const TGit & beg, const TGit & end)
{
	return taskGrp.erase(beg, end);
}

list<TimeoutP::_TaskGrp>::iterator TimeoutP::_Scale::begin()
{
	return taskGrp.begin();
}

list<TimeoutP::_TaskGrp>::iterator TimeoutP::_Scale::end()
{
	return taskGrp.end();
}

TimeoutP::_TaskGrp::_TaskGrp(const int & sec_key) :
	sec_key(sec_key)
{
}

bool TimeoutP::_TaskGrp::empty()
{
	return taskCountGrp.empty();
}

void TimeoutP::_TaskGrp::clear()
{
	return taskCountGrp.clear();
}

void TimeoutP::_TaskGrp::pushback(const _TaskCountGrp & tcg)
{
	taskCountGrp.push_back(tcg);
}

TimeoutP::_TaskGrp::TCGit TimeoutP::_TaskGrp::insert(const TCGit & pos, const TCGit & beg, const TCGit & end)
{
	return taskCountGrp.insert(pos, beg, end);
}

void TimeoutP::_TaskGrp::remove(const _TaskCountGrp & tcg)
{
	taskCountGrp.remove(tcg);
}

TimeoutP::_TaskGrp::TCGit TimeoutP::_TaskGrp::erase(const TCGit & beg, const TCGit & end)
{
	return taskCountGrp.erase(beg, end);
}

list<TimeoutP::_TaskCountGrp>::iterator TimeoutP::_TaskGrp::begin()
{
	return taskCountGrp.begin();
}

list<TimeoutP::_TaskCountGrp>::iterator TimeoutP::_TaskGrp::end()
{
	return taskCountGrp.end();
}

TimeoutP::_TaskCountGrp::_TaskCountGrp(int * const & pcount) :
	pcount(pcount)
{

}

bool TimeoutP::_TaskCountGrp::empty()
{
	return timeTask.empty();
}

void TimeoutP::_TaskCountGrp::clear()
{
	return timeTask.clear();
}

void TimeoutP::_TaskCountGrp::pushback(TimeoutTaskR *const & ttask)
{
	timeTask.push_back(ttask);
}

TimeoutP::_TaskCountGrp::PTTit TimeoutP::_TaskCountGrp::insert(const PTTit & pos, const PTTit & beg, const PTTit & end)
{
	return timeTask.insert(pos, beg, end);
}

void TimeoutP::_TaskCountGrp::remove(TimeoutTaskR * const & ttask)
{
	timeTask.remove(ttask);
}

TimeoutP::_TaskCountGrp::PTTit TimeoutP::_TaskCountGrp::erase(const PTTit & beg, const PTTit & end)
{
	return timeTask.erase(beg, end);
}

list<TimeoutTaskR*>::iterator TimeoutP::_TaskCountGrp::begin()
{
	return timeTask.begin();
}

list<TimeoutTaskR*>::iterator TimeoutP::_TaskCountGrp::end()
{
	return timeTask.end();
}

