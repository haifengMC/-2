#include "../../inc/protocol/TimeoutMsg.h"
#include "../../inc/protocol/TimeoutP.h"
#include "../../inc/protocol/TimeoutDisprP.h"

#define D(X) std::cout << #X", " << X << ", " << __LINE__ << endl;
#define Darr(X, func) \
	std::cout << #X"[" << __LINE__ << "], "; \
	for (auto a : X) std::cout << func << "\t";\
	std::cout << std::endl


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
	int count = tt.getTimeoutSec() / TIME_WHEEL_LEN;
	
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
	//D(tt.getTaskName());

	for (int i = 0; i < TIME_WHEEL_LEN; i++)
	{
		_Scale& s = s_timewheel[i];
		if (s.empty()) continue;
		for (_TaskGrp& tg : s)
		{
			if (tg.empty()) continue;
			if (tg.sec_key != tt.getTimeoutSec()) continue;
			for (_TaskCountGrp& tcg : tg)
			{
				if (tcg.empty()) continue;
				if (tcg.pcount != tt.getPCount()) continue;

				//std::cout << "[" << __LINE__ << "], "; 
				//for (auto a : tcg)
				//	std::cout << a->getTaskName() << " "; 
				//std::cout << std::endl;

				for (TimeoutTaskR* ptt : tcg)
				{
					if (ptt == &tt)
					{
						//D(ptt->getTaskName());
						tt.setPCount(NULL);
						tcg.remove(&tt);

						//D("remove ok");
						break;
					}
				}

				if (tcg.empty()) tg.remove(tcg);
				break;
			}
			if (tg.empty()) s.remove(tg);
			break;
		}
	}


	//std::cout << "[" << __LINE__ << "], ";
	//for (int i = 0; i < TIME_WHEEL_LEN; i++)
	//{
	//	cout << s_timewheel[i].getState() << " ";
	//}
	//cout << endl;
}

UserData * TimeoutP::raw2request(std::string _szInput)
{
	s_oldScale = s_timeWheelScale;
	s_timeWheelScale += *(uint64_t*)_szInput.data();
	if (TIME_WHEEL_LEN == s_timeWheelScale)
	{
		int temp = s_timeWheelScale - s_oldScale;
		s_timeWheelScale = 0;
		s_oldScale = s_timeWheelScale - temp;
	}

	//if (s_timeWheelScale == 0)
	//{
	//	D(s_timeWheelScale);

	//}

	int scale = s_timeWheelScale % TIME_WHEEL_LEN;

	//std::cout << "[" << __LINE__ << "], ";
	//for (int i = 0; i < TIME_WHEEL_LEN; i++)
	//{
	//	cout << s_timewheel[i].getState() << " ";
	//}
	//cout << endl;

	for (int i = s_timeWheelScale - s_oldScale - 1; i >= 0; i--)
	{

		_Scale& s = s_timewheel[scale - i];
		//D(scale - i);

		//Darr(s);

		for (_TaskGrp& tg : s)
		{
			if (tg.empty()) continue;
			for (_TaskCountGrp& tcg : tg)
			{
				if (tcg.empty()) continue;
				if (0 < *tcg.pcount) continue;
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

		updataScale(s);
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
	//std::cout << s_timeWheelScale << "[" << __LINE__ << "], ";
	//for (int i = 0; i < TIME_WHEEL_LEN; i++)
	//{
	//	cout << s_timewheel[i].getState() << " ";
	//}
	//cout << endl;

	//if (s_timeWheelScale == 15)
	//{
	//	D(s_timeWheelScale);

	//}



	//list<_TaskGrp*> tgDel;

	//for (_TaskGrp& tg : scale)
	//{
	//	if (tg.empty()) continue;
	//	//D(tg.sec_key);

	//	int m_scale = (s_timeWheelScale + tg.sec_key) % TIME_WHEEL_LEN;
	//	int m_count = tg.sec_key / TIME_WHEEL_LEN;
	//	list<_TaskCountGrp*> tcgDel;

	//	for (_TaskCountGrp& tcg : tg)
	//	{
	//		
	//		if (tcg.empty()) continue;
	//		//Darr(tcg, a->getTaskName());
	//		*tcg.pcount -= 1;
	//		if (0 > *tcg.pcount)
	//		{
	//			*tcg.pcount = m_count;
	//			_TaskGrp tgTmp(tg.sec_key);
	//			tgTmp.pushback(tcg);
	//			s_timewheel[m_scale].pushback(tgTmp);
	//			tcgDel.push_back(&tcg);
	//		}
	//	}
	//	for (_TaskCountGrp* &ptcg : tcgDel)
	//	{
	//		tg.remove(*ptcg);
	//	}

	//	if (tg.empty())
	//		tgDel.push_back(&tg);

	//}

	//for (_TaskGrp* &ptg : tgDel)
	//{
	//	scale.remove(*ptg);
	//}

	for (_Scale::TGit tgIt = scale.begin(); tgIt != scale.end();)
	{
		if (tgIt->empty()) continue;
		int m_scale = (s_timeWheelScale + tgIt->sec_key) % TIME_WHEEL_LEN;
		int m_count = tgIt->sec_key / TIME_WHEEL_LEN;
		for (_TaskGrp::TCGit tcgIt = tgIt->begin(); tcgIt != tgIt->end();)
		{
			if (tcgIt->empty()) continue;
			int& tcgCount = *tcgIt->pcount;

			//D(tcgCount);
			tcgCount -= 1;
			//D(tcgCount);
			if (0 > tcgCount)
			{
				//D(tgIt->sec_key);
				//D(tcgCount);
				tcgCount = m_count;
				_TaskGrp tgTmp(tgIt->sec_key);
				tgTmp.pushback(*tcgIt);
				s_timewheel[m_scale].pushback(tgTmp);
				tcgIt = tgIt->erase(tcgIt);
			}
			else
				++tcgIt;
		}
		if (tgIt->empty())
			tgIt = scale.erase(tgIt);
		else
			++tgIt;
	}


	//list<_TaskGrp*> del_tg;

	//if (scale.empty()) return;
	//for (_TaskGrp& tg : scale)
	//{
	//	if (tg.empty()) continue;

	//	int m_scale = (s_timeWheelScale + tg.sec_key) % TIME_WHEEL_LEN;
	//	int m_count = (s_timeWheelScale + tg.sec_key) / TIME_WHEEL_LEN;


	//	for (_TaskGrp& tgDest : s_timewheel[m_scale])
	//	{
	//		if (tgDest.empty()) break;

	//		if (tg.sec_key == tgDest.sec_key)
	//		{
	//			for (_TaskCountGrp& tcg : tg)
	//			{
	//				if (tcg.empty()) continue;
	//				if (*tcg.pcount) continue;
	//				for (_TaskCountGrp& tcgDest : tgDest)
	//				{
	//					if (tcgDest.empty()) break;
	//					if (*tcgDest.pcount == *tcg.pcount)
	//					{
	//						tcgDest.insert(tcgDest.end(), tcg.begin(), tcg.end());
	//						tcg.clear();
	//					}
	//				}
	//			}
	//			tgDest.insert(tgDest.end(), tg.begin(), tg.end());
	//			tg.clear();
	//		}

	//		
	//		list<_TaskCountGrp*> tcgDel;
	//		for (_TaskCountGrp& tcg : tg)
	//		{
	//			if (tcg.empty()) continue;
	//			if (0 == *tcg.pcount)
	//			{
	//				*tcg.pcount = m_count;
	//				_TaskGrp tgTmp(tg.sec_key);
	//				tgTmp.pushback(tcg);
	//				s_timewheel[m_scale].pushback(tgTmp);
	//				tcgDel.push_back(&tcg);
	//			}
	//		}
	//		for (_TaskCountGrp* &ptcg : tcgDel)
	//		{
	//			tg.remove(*ptcg);
	//		}
	//		
	//		//s_timewheel[m_scale].pushback(tg);
	//		if (tg.empty())
	//			del_tg.push_back(&tg);
	//	}
	//}

	//for (_TaskGrp* &ptg : del_tg)
	//{
	//	scale.remove(*ptg);
	//}
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

int TimeoutP::_Scale::getState()
{
	return taskGrp.size();
}

bool TimeoutP::_Scale::empty()
{
	return taskGrp.empty();
}

void TimeoutP::_Scale::clear()
{
	return taskGrp.clear();
}

void TimeoutP::_Scale::pushback(_TaskGrp & tg)
{
	if (tg.empty()) return;
	for (_TaskGrp tgTmp : taskGrp)
	{
		if (tgTmp == tg)
		{
			for (_TaskCountGrp& tcg : tg)
					tgTmp.pushback(tcg);
			return;
		}
	}
	taskGrp.push_back(tg);

}

TimeoutP::_Scale::TGit TimeoutP::_Scale::insert(const TGit & pos, const TGit & beg, const TGit & end)
{
	return taskGrp.insert(pos, beg, end);
}

TimeoutP::_Scale::TGit TimeoutP::_Scale::insertIf(const TGit & pos, const TGit & beg, const TGit & end, bool(*ifProc)(const TGit &ifpos))
{
	TGit new_pos = pos;
	for (TGit tmp = beg; tmp != end; tmp++)
	{
		if (ifProc(tmp)) new_pos = taskGrp.insert(new_pos, *tmp);
	}
	return new_pos;
}

void TimeoutP::_Scale::remove(const _TaskGrp & tg)
{
	taskGrp.remove(tg);
}

TimeoutP::_Scale::TGit TimeoutP::_Scale::erase(const TGit & beg, const TGit & end)
{
	return taskGrp.erase(beg, end);
}

TimeoutP::_Scale::TGit TimeoutP::_Scale::erase(const TGit & pos)
{
	return taskGrp.erase(pos);
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

int TimeoutP::_TaskGrp::getState()
{
	return sec_key;
}

bool TimeoutP::_TaskGrp::empty()
{
	return taskCountGrp.empty();
}

void TimeoutP::_TaskGrp::clear()
{
	return taskCountGrp.clear();
}

void TimeoutP::_TaskGrp::pushback(_TaskCountGrp & tcg)
{
	if (tcg.empty()) return;
	for (_TaskCountGrp tcgTmp : taskCountGrp)
	{
		if (tcgTmp == tcg)
		{
			bool next = false;
			for (TimeoutTaskR*& ptt : tcg)
			{
				for (TimeoutTaskR*& pttTmp : tcgTmp)
				{
					if (ptt == pttTmp)
					{
						next = true;
						break;
					}
				}
				if (next) continue;
				
				tcgTmp.pushback(ptt);
			}
			return;
		}
	}
	taskCountGrp.push_back(tcg);
}

TimeoutP::_TaskGrp::TCGit TimeoutP::_TaskGrp::insert(const TCGit & pos, const TCGit & beg, const TCGit & end)
{
	return taskCountGrp.insert(pos, beg, end);
}

TimeoutP::_TaskGrp::TCGit TimeoutP::_TaskGrp::insertIf(const TCGit & pos, const TCGit & beg, const TCGit & end, bool(*ifProc)(const TCGit &ifpos))
{
	TCGit new_pos = pos;
	for (TCGit tmp = beg; tmp != end; tmp++)
	{
		if (ifProc(tmp)) new_pos = taskCountGrp.insert(new_pos, *tmp);
	}
	return new_pos;
}

void TimeoutP::_TaskGrp::remove(const _TaskCountGrp & tcg)
{
	taskCountGrp.remove(tcg);
}

TimeoutP::_TaskGrp::TCGit TimeoutP::_TaskGrp::erase(const TCGit & beg, const TCGit & end)
{
	return taskCountGrp.erase(beg, end);
}

TimeoutP::_TaskGrp::TCGit TimeoutP::_TaskGrp::erase(const TCGit & pos)
{
	return taskCountGrp.erase(pos);
}

list<TimeoutP::_TaskCountGrp>::iterator TimeoutP::_TaskGrp::begin()
{
	return taskCountGrp.begin();
}

list<TimeoutP::_TaskCountGrp>::iterator TimeoutP::_TaskGrp::end()
{
	return taskCountGrp.end();
}

bool TimeoutP::_TaskGrp::operator==(const _TaskGrp & tg)
{
	if (sec_key == tg.sec_key)
	{
		return true;
	}

	return false;
}

TimeoutP::_TaskCountGrp::_TaskCountGrp(int * const & pcount) :
	pcount(pcount)
{

}

TimeoutP::_TaskCountGrp::~_TaskCountGrp()
{
	if (timeTask.empty())
	{
		delete pcount;
	}
}

int TimeoutP::_TaskCountGrp::getState()
{
	return *pcount;
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

TimeoutP::_TaskCountGrp::PTTit TimeoutP::_TaskCountGrp::insertIf(const PTTit & pos, const PTTit & beg, const PTTit & end, bool(*ifProc)(const PTTit &ifpos))
{
	PTTit new_pos = pos;
	for (PTTit tmp = beg; tmp != end; tmp++)
	{
		if (ifProc(tmp)) new_pos = timeTask.insert(new_pos, *tmp);
	}
	return new_pos;
}

void TimeoutP::_TaskCountGrp::remove(TimeoutTaskR * const & ttask)
{
	timeTask.remove(ttask);
}

TimeoutP::_TaskCountGrp::PTTit TimeoutP::_TaskCountGrp::erase(const PTTit & beg, const PTTit & end)
{
	return timeTask.erase(beg, end);
}

TimeoutP::_TaskCountGrp::PTTit TimeoutP::_TaskCountGrp::erase(const PTTit & pos)
{
	return timeTask.erase(pos);
}

list<TimeoutTaskR*>::iterator TimeoutP::_TaskCountGrp::begin()
{
	return timeTask.begin();
}

list<TimeoutTaskR*>::iterator TimeoutP::_TaskCountGrp::end()
{
	return timeTask.end();
}

bool TimeoutP::_TaskCountGrp::operator==(const _TaskCountGrp & tcg)
{
	if (pcount == tcg.pcount)
	{
		return true;
	}

	return false;
}

