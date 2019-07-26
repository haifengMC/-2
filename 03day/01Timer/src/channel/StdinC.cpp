#include <iostream>

#include "../../inc/channel/StdinC.h"
#include "../../inc/protocol/CmdPrsP.h"


StdinC::StdinC()
{
}


StdinC::~StdinC()
{
}

bool StdinC::Init()
{
	return true;
}

bool StdinC::ReadFd(std::string & _input)
{
	std::cin >> _input;

	return true;
}

bool StdinC::WriteFd(std::string & _output)
{
	return false;
}

void StdinC::Fini()
{
}

int StdinC::GetFd()
{
	return STDIN_FILENO;
}

std::string StdinC::GetChannelInfo()
{
	return "stdin_channel";
}

AZinxHandler * StdinC::GetInputNextStage(BytesMsg & _oInput)
{
	return &CmdPrsP::getInstance();
}
