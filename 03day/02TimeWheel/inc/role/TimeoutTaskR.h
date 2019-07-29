#pragma once
#include "zinx.h"
class TimeoutTaskR :
	public Irole
{
public:
	TimeoutTaskR(const std::string& task_name, const int& sec);
	virtual ~TimeoutTaskR();



	// Í¨¹ý Irole ¼Ì³Ð
	virtual bool Init() override;

	virtual UserData * ProcMsg(UserData & _poUserData) override;

	virtual void Fini() override;

	const int& getTimeoutSec() const;
	int *const & getPCount() const;
	void setPCount(const int*const & pc);
private:
	const int timeout_sec = 0;
	int* pcount = NULL;
	std::string task_name;

};

