#include <iostream>


#include "../../inc/role/TimeoutTaskR.h"
#include "../../inc/protocol/TimeoutP.h"

using namespace std;

TimeoutTaskR::TimeoutTaskR(const std::string& task_name, const int& sec): 
	timeout_sec(sec), task_name(task_name)
{
	TimeoutP::registerTask(*this);
}


TimeoutTaskR::~TimeoutTaskR()
{
	TimeoutP::unregisterTask(*this);
}

bool TimeoutTaskR::Init()
{

	return true;
}

UserData * TimeoutTaskR::ProcMsg(UserData & _poUserData)
{
	cout << task_name << "[" << timeout_sec << "]" << endl;

	return nullptr;
}

void TimeoutTaskR::Fini()
{
}

const int & TimeoutTaskR::getTimeoutSec() const
{
	return timeout_sec;
}

int *const & TimeoutTaskR::getPCount() const
{
	return pcount;
}

void TimeoutTaskR::setPCount(const int *const & pc)
{
	pcount = (int*)pc;
}
