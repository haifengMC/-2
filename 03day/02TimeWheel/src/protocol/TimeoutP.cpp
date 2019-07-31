#include "../../inc/protocol/TimeoutMsg.h"
#include "../../inc/protocol/TimeoutP.h"
#include "../../inc/protocol/TimeoutDisprP.h"

#define D(X) std::cout << X << ", " << __LINE__ << endl;

TimeoutP::TimeoutP()
{
}

TimeoutP::~TimeoutP()
{
	for (list<map<int, TaskData_List>*>& scale_list : s_timeWheel)
	{
		if (scale_list.empty())continue;
		for (map<int, TaskData_List>*& ptask_map : scale_list)
		{
			if (NULL == ptask_map)continue;
			for (pair<const int, TaskData_List>& tdl_pair : *ptask_map)
			{
				for (_TaskData* td : tdl_pair.second)
				{
					if (NULL == td)continue;

					delete td;
				}
			}

			delete ptask_map;
		}
	}

}

TimeoutP TimeoutP::s_timeout;
uint64_t TimeoutP::s_oldScale;
uint64_t TimeoutP::s_timeWheelScale = 0;
list<map<int, TimeoutP::TaskData_List>*> TimeoutP::s_timeWheel[TIME_WHEEL_LEN];
//std::map<int, TimeoutP::_TaskData*> TimeoutP::timeout_map;

TimeoutP & TimeoutP::getInstance()
{
	return s_timeout;
}

void TimeoutP::registerTask(TimeoutTaskR & tt)
{
	int scale = (s_timeWheelScale + tt.getTimeoutSec()) % TIME_WHEEL_LEN;
	int count = (s_timeWheelScale + tt.getTimeoutSec()) / TIME_WHEEL_LEN;
	
	//cout << tt.getTaskName() << ", scale" << scale << "count" << count << endl;

	list<map<int, TaskData_List>*>&  scale_list = s_timeWheel[scale];

	if (scale_list.empty())
	{
		insertNewMap(tt, scale_list);
		return;
	}
	else
	{
		for (map<int, TaskData_List>*& ptask_map : scale_list)
		{
			if (NULL == ptask_map)continue;
	
			map<int, TaskData_List>::iterator task_it;

			if (ptask_map->end() != 
				(task_it = ptask_map->find(tt.getTimeoutSec())))
			{
				TaskData_List& tdl = task_it->second;
				for (_TaskData*& td : tdl)
				{
					if (count == *td->pcount)
					{
						tt.setPCount(td->pcount);
						td->task_list.push_back(&tt);

						return;
					}
				}
				_TaskData* td = new _TaskData(new int(count));
				td->task_list.push_back(&tt);
				tdl.push_back(td);

				return;
			}
			else
			{
				insertNewMap(tt, scale_list);
				return;
			}
		}
	}

}

void TimeoutP::unregisterTask(const TimeoutTaskR & tt)
{
	for (list<map<int, TaskData_List>*>& scale_list : s_timeWheel)
	{
		for (map<int, TaskData_List>*& ptask_map : scale_list)
		{
			if (ptask_map->end() == ptask_map->find(tt.getTimeoutSec()))
				continue;

			TaskData_List& tdl = (*ptask_map)[tt.getTimeoutSec()];

			for (_TaskData*& ptd : tdl)
			{
				ptd->task_list.remove(&tt);
				if (ptd->task_list.empty())
				{
					tdl.remove(ptd);
					break;
				}
			}

			if (tdl.empty())
			{
				ptask_map->erase(tt.getTimeoutSec());
				if (ptask_map->empty())
				{
					scale_list.remove(ptask_map);
					delete ptask_map;
				}
				break;
			}
		}
	}
}

UserData * TimeoutP::raw2request(std::string _szInput)
{
	s_oldScale = s_timeWheelScale;
	s_timeWheelScale += *(uint64_t*)_szInput.data();

	for (int i = 0; i < s_timeWheelScale - s_oldScale; i++)
	{
		for (list<map<int, TaskData_List>*>& scale_list : s_timeWheel)
		{
			if (scale_list.empty())continue;
			for (map<int, TaskData_List>*& ptask_map : scale_list)
			{
				if (NULL == ptask_map)continue;
				for (pair<const int, TaskData_List>& tdl_pair : *ptask_map)
				{
					for (_TaskData* td : tdl_pair.second)
					{
						for (const TimeoutTaskR*& ppt : td->task_list)
						{
							char buf[sizeof(TimeoutTaskR*)];
							memcpy(buf, &ppt, sizeof(TimeoutTaskR*));
							std::string str(buf, sizeof(buf));

							Ichannel* ch = ZinxKernel::
								Zinx_GetChannel_ByInfo("timeout_dispO_channel");

							ZinxKernel::Zinx_SendOut(str, *ch);
						}

					}
		
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

void TimeoutP::insertNewMap(
	TimeoutTaskR & tt,
	list<map<int, TaskData_List>*>& scale_list)
{
	int count = 
		(s_timeWheelScale + tt.getTimeoutSec()) / 
		TIME_WHEEL_LEN;

	map<int, TaskData_List>* ptask_map =
		new map<int, TaskData_List>;

	TaskData_List& tdl = (*ptask_map)[tt.getTimeoutSec()];
	_TaskData* td = new _TaskData(new int(count));
	td->task_list.push_back(&tt);
	tdl.push_back(td);


	scale_list.push_back(ptask_map);
}

