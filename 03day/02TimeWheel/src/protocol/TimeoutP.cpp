#include "../../inc/protocol/TimeoutMsg.h"
#include "../../inc/protocol/TimeoutP.h"
#include "../../inc/protocol/TimeoutDisprP.h"



TimeoutP::TimeoutP()
{
}

TimeoutP::~TimeoutP()
{
	for (list<multimap<_TaskKey, TimeoutTaskR*>*>& scale : s_timeWheel)
	{
		if (scale.empty())continue;
		for (multimap<_TaskKey, TimeoutTaskR*>* & timeout_map : scale)
		{
			for (pair<const _TaskKey, TimeoutTaskR*>& p : *timeout_map)
			{
				if (NULL != p.second)
				{
					delete p.second;
					p.second = NULL;
				}
			}

			delete timeout_map;
		}
	}

}

TimeoutP TimeoutP::s_timeout;
uint64_t TimeoutP::s_oldScale;
uint64_t TimeoutP::s_timeWheelScale = 0;
array<list<multimap<TimeoutP::_TaskKey, TimeoutTaskR*>*>,
	TIME_WHEEL_LEN> TimeoutP::s_timeWheel;
//std::map<int, TimeoutP::_TaskData*> TimeoutP::timeout_map;

TimeoutP & TimeoutP::getInstance()
{
	return s_timeout;
}

void TimeoutP::registerTask(TimeoutTaskR & tt)
{
	cout << tt.getTimeoutSec() << endl;
	int scale = (s_timeWheelScale + tt.getTimeoutSec()) % TIME_WHEEL_LEN;
	int count = (s_timeWheelScale + tt.getTimeoutSec()) / TIME_WHEEL_LEN;
	
	list<multimap<_TaskKey, TimeoutTaskR*>*>& s_wheelList = s_timeWheel[scale];

	if (s_wheelList.empty())
	{
		insertNewMap(tt, s_wheelList);
	}
	else
	{
		for (multimap<_TaskKey, TimeoutTaskR*>*& timeout_map : 
			s_wheelList)
		{
			multimap<_TaskKey, TimeoutTaskR*>::iterator timeout_it = 
				timeout_map->begin();

			if (findInMap(&tt, timeout_it, *timeout_map))
			{
				tt.setPCount(timeout_it->first.pcount);
				timeout_map->insert({ timeout_it->first, &tt });
			}
			else
			{
				insertNewMap(tt, s_wheelList);
			}
		}
	}
}

void TimeoutP::unregisterTask(const TimeoutTaskR & tt)
{
	for (list<multimap<_TaskKey, TimeoutTaskR*>*>& scale : s_timeWheel)
	{
		for (multimap<_TaskKey, TimeoutTaskR*>* & timeout_map : scale)
		{
			multimap<_TaskKey, TimeoutTaskR*>::iterator timeout_it =
				timeout_map->begin();
			
			if (!findInMap(&tt, timeout_it, *timeout_map))continue;

			timeout_map->erase(timeout_it);

		}
	}
}

UserData * TimeoutP::raw2request(std::string _szInput)
{
	s_oldScale = s_timeWheelScale;
	s_timeWheelScale += *(uint64_t*)_szInput.data();

	for (int i = 0; i < s_timeWheelScale - s_oldScale; i++)
	{
		for (list<multimap<_TaskKey, TimeoutTaskR*>*>& scale_list : s_timeWheel)
		{
			if (scale_list.empty())continue;
			for (multimap<_TaskKey, TimeoutTaskR*>* &task_map : scale_list)
			{
				if (task_map->empty())continue;
				for (pair<_TaskKey, TimeoutTaskR*> task_pair : *task_map)
				{
					char buf[sizeof(TimeoutTaskR*)];
					memcpy(buf, task_pair.second, sizeof(TimeoutTaskR*));
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

bool TimeoutP::findInMap(
	const TimeoutTaskR * const & ptt,
	multimap<const _TaskKey, TimeoutTaskR*>::iterator& ptt_it,
	multimap<_TaskKey, TimeoutTaskR*>& ptt_list)
{
	ptt_it = ptt_list.begin();

	do 
	{
		if (ptt == ptt_it->second)
			return true;
	}
	while (ptt_list.end() != ++ptt_it);

	ptt_it = ptt_list.end();

	return false;
}

void TimeoutP::insertNewMap(
	TimeoutTaskR & tt, 
	list<multimap<_TaskKey, TimeoutTaskR*>*>& s_wheelList)
{
	int count = (s_timeWheelScale + tt.getTimeoutSec()) / TIME_WHEEL_LEN;

	multimap<_TaskKey, TimeoutTaskR*>* p_timeout_map =
		new multimap<_TaskKey, TimeoutTaskR*>;

	_TaskKey tk = 
	{
		tt.getTimeoutSec(), 
		new int(count)
	};

	tt.setPCount(tk.pcount);

	p_timeout_map->insert({ tk, &tt });

	s_wheelList.push_back(p_timeout_map);
}

