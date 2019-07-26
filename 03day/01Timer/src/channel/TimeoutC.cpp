#include "../../inc/channel/TimeoutC.h"
#include "../../inc/protocol/CmdPrsP.h"
#include "../../inc/protocol/TimeoutP.h"
#include "sys/timerfd.h"


TimeoutC::TimeoutC()
{
}


TimeoutC::~TimeoutC()
{
}

bool TimeoutC::Init()
{
	timerfd = timerfd_create(CLOCK_MONOTONIC, 0);
	if (-1 == timerfd) return false;
	itimerspec newtime =
	{
		{1, 0},
		{1, 0}
	};
	if (-1 == timerfd_settime(timerfd, 0, &newtime, NULL))
	{
		close(timerfd);
		timerfd = -1;

		return false;
	}
	return true;
}

bool TimeoutC::ReadFd(std::string & _input)
{
	char buf[sizeof(uint64_t)];
	if (sizeof(buf) ==
		read(timerfd, buf, sizeof(buf)))
	{
		_input.append(buf, sizeof(buf));
		return true;
	}
	return false;
}

bool TimeoutC::WriteFd(std::string & _output)
{
	return false;
}

void TimeoutC::Fini()
{
	if (-1 != timerfd)
	{
		close(timerfd);
		timerfd = -1;
	}
}

int TimeoutC::GetFd()
{
	return timerfd;
}

std::string TimeoutC::GetChannelInfo()
{
	return "timeout_channel";
}

AZinxHandler * TimeoutC::GetInputNextStage(BytesMsg & _oInput)
{
	return &TimeoutP::getInstance();
}
