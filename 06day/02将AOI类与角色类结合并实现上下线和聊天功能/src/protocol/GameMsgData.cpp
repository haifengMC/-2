#include "../../inc/protocol/GameMsgData.h"

GameMsgData::~GameMsgData()
{
}


SyncPlyrIdData::SyncPlyrIdData(const int & plyrId, const string & usrName) :
	plyrId(plyrId), usrName(usrName)
{
}

SyncPlyrIdData::~SyncPlyrIdData()
{
}

ChatData::~ChatData()
{
}

PlyrPosData::~PlyrPosData()
{
}

BroadCastData::~BroadCastData()
{ 
}

PlyrData::~PlyrData()
{
}

SyncPlyrsData::~SyncPlyrsData()
{
}
