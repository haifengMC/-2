#include "../../inc/role/ExitR.h"



ExitR::ExitR()
{
}


ExitR::~ExitR()
{
}

bool ExitR::Init()
{
	return true;
}

UserData * ExitR::ProcMsg(UserData & _poUserData)
{
	ZinxKernel::Zinx_Exit();

	return nullptr;
}

void ExitR::Fini()
{
}
