#include <iostream>

#include "../../inc/channel/StdoutC.h"

using namespace std;

StdoutC::StdoutC()
{
}


StdoutC::~StdoutC()
{
}

bool StdoutC::Init()
{
	return true;
}

bool StdoutC::ReadFd(std::string & _input)
{
	return false;
}

bool StdoutC::WriteFd(std::string & _output)
{
	cout << _output << endl;

	return true;
}

void StdoutC::Fini()
{
}

int StdoutC::GetFd()
{
	return STDOUT_FILENO;
}

std::string StdoutC::GetChannelInfo()
{
	return "stdout_channel";
}

AZinxHandler * StdoutC::GetInputNextStage(BytesMsg & _oInput)
{
	return nullptr;
}
