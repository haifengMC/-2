#include<iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "../../inc/channel/TimeoutDispOC.h"

#include "../../inc/role/TimeoutTaskR.h"



TimeoutDispOC::TimeoutDispOC()
{
}


TimeoutDispOC::~TimeoutDispOC()
{
}

int TimeoutDispOC::getIFd()
{
	return pipefd[0];
}

bool TimeoutDispOC::Init()
{
	return 0 == pipe(pipefd);
}

bool TimeoutDispOC::ReadFd(std::string & _input)
{
	return false;
}

bool TimeoutDispOC::WriteFd(std::string & _output)
{
	TimeoutTaskR* tt_str = (TimeoutTaskR*)_output.data();

	return -1 != write(pipefd[1], _output.data(), sizeof(TimeoutTaskR*));
}

void TimeoutDispOC::Fini()
{
	close(pipefd[1]);
}

int TimeoutDispOC::GetFd()
{
	return pipefd[1];
}

std::string TimeoutDispOC::GetChannelInfo()
{
	return "timeout_dispO_channel";
}

AZinxHandler * TimeoutDispOC::GetInputNextStage(BytesMsg & _oInput)
{
	return nullptr;
}
