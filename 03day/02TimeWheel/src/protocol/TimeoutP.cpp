#include "../../inc/protocol/TimeoutMsg.h"
#include "../../inc/protocol/TimeoutP.h"
#include "../../inc/protocol/TimeoutDisprP.h"

using namespace std;

TimeoutP::TimeoutP()
{
}

TimeoutP::~TimeoutP()
{
	for (std::pair<int, _TaskData*> p : timeout_map)
	{
		if (NULL != p.second)
		{
			delete p.second->pcount;
			delete p.second;
		}
	}
}

TimeoutP TimeoutP::s_timeout;
std::map<int, TimeoutP::_TaskData*> TimeoutP::timeout_map;

TimeoutP & TimeoutP::getInstance()
{
	return s_timeout;
}

void TimeoutP::registerTask(TimeoutTaskR & tt)
{
	if (timeout_map.end() == timeout_map.find(tt.getTimeoutSec()))
	{
		tt.setPCount(new int(tt.getTimeoutSec()));
		timeout_map[tt.getTimeoutSec()] = new _TaskData;
		timeout_map[tt.getTimeoutSec()]->pcount = tt.getPCount();
		timeout_map[tt.getTimeoutSec()]->ptt_list.push_back(&tt);
	}
	else
	{
		tt.setPCount(timeout_map[tt.getTimeoutSec()]->pcount);
		timeout_map[tt.getTimeoutSec()]->ptt_list.push_back(&tt);
	}
}

void TimeoutP::unregisterTask(const TimeoutTaskR & tt)
{
	if (timeout_map.end() ==
		timeout_map.find(tt.getTimeoutSec()))
		return;
	timeout_map[tt.getTimeoutSec()]->ptt_list.remove((TimeoutTaskR*)&tt);
}

UserData * TimeoutP::raw2request(std::string _szInput)
{
	uint64_t count = *(uint64_t*)_szInput.data();
	for (int i = 0; i < count; i++)
	{
		for (std::pair<const int, _TaskData*>& p : timeout_map)
		{
			if (0 >= (*p.second->pcount -= 1))
			{
				*p.second->pcount = p.first;
				for (TimeoutTaskR* tt : p.second->ptt_list)
				{
					char buf[sizeof(TimeoutTaskR*)];
					memcpy(buf, &tt, sizeof(TimeoutTaskR*));
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

bool TimeoutP::findInList(const TimeoutTaskR* const & ptt, 
	const std::list<TimeoutTaskR*>& ptt_list)
{
	for (TimeoutTaskR* p : ptt_list)
	{
		if (p == ptt) return true;
	}
	return false;
}
