#include <sys/types.h>
#include <sys/stat.h>

#include "../../inc/channel/TimeoutDispIC.h"
#include "../../inc/channel/TimeoutDispOC.h"
#include "../../inc/protocol/TimeoutDisprP.h"
#include "../../inc/role/TimeoutTaskR.h"



TimeoutDispIC::TimeoutDispIC()
{
}


TimeoutDispIC::~TimeoutDispIC()
{
}

bool TimeoutDispIC::Init()
{
	Ichannel* channel = 
		ZinxKernel::Zinx_GetChannel_ByInfo("timeout_dispO_channel");
	fd = ((TimeoutDispOC*)channel)->getIFd();

	return true;
}

bool TimeoutDispIC::ReadFd(std::string & _input)
{
	char ch_i[sizeof(TimeoutTaskR*)] = { 0 };
	//printf("%d\n", read(fd, ch_i, sizeof(ch_i)));
	if (-1 == read(fd, ch_i, sizeof(ch_i))) return false;

	_input.append(ch_i, sizeof(ch_i));

	return true;
}

bool TimeoutDispIC::WriteFd(std::string & _output)
{
	return false;
}

void TimeoutDispIC::Fini()
{
	close(fd);
}

int TimeoutDispIC::GetFd()
{
	return fd;
}

std::string TimeoutDispIC::GetChannelInfo()
{
	return "timeout_dispI_channel";
}

AZinxHandler * TimeoutDispIC::GetInputNextStage(BytesMsg & _oInput)
{
	return &TimeoutDisprP::getInstance();
}
