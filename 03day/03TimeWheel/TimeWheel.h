#pragma once
#include <iostream>
#include <list>

using namespace std;

struct TimeTask
{
	friend class TimeWheel;
	TimeTask(const uint64_t& sec) : sec(sec)
	{

	}
private:
	const uint64_t sec;
	int* pcount;
};


class TimeWheel
{
	struct _TaskCountGrp
	{
		int* pcount;
		list<TimeTask*> timeTask;

		_TaskCountGrp(int *const &pcount);

		bool empty();
		void pushback(TimeTask * const & ttask);
		void remove(TimeTask * const & ttask);
		list<TimeTask*>::iterator begin();
		list<TimeTask*>::iterator end();
	};
	struct _TaskGrp
	{
		int sec_key;
		list<_TaskCountGrp> taskCountGrp;

		_TaskGrp(const int& sec_key);

		bool empty();
		void pushback(const _TaskCountGrp & tcg);
		void remove(const _TaskCountGrp & tcg);
		list<_TaskCountGrp>::iterator begin();
		list<_TaskCountGrp>::iterator end();
	};
	struct _Scale
	{
		list<_TaskGrp> taskGrp;

		bool empty();
		void pushback(const _TaskGrp & tg);
		void remove(const _TaskGrp & tg);
		list<_TaskGrp>::iterator begin();
		list<_TaskGrp>::iterator end();

	};
public:
	TimeWheel(const unsigned int& timeWheelLen);
	~TimeWheel();

	void registerTask(TimeTask& ttask);
	void unregisterTask(TimeTask& ttask);

private:
	unsigned int timeWheelLen;
	unsigned int  timer = 0;
	static _Scale* s_timewheel;
};

