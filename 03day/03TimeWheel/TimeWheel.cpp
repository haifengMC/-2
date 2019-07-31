#include "TimeWheel.h"




TimeWheel::TimeWheel(const unsigned int & timeWheelLen) : 
	timeWheelLen(timeWheelLen)
{
	s_timewheel = new _Scale[timeWheelLen];
}

TimeWheel::~TimeWheel()
{
	for (int i = 0; i < timeWheelLen; i++)
	{
		_Scale& s = s_timewheel[i];
		for (_TaskGrp& tg : s)
		{
			for (_TaskCountGrp& tcg : tg)
			{
				delete tcg.pcount;
			}
		}

	}

	delete[] s_timewheel;
}

void TimeWheel::registerTask(TimeTask & ttask)
{
	int scale = (ttask.sec + timer) % timeWheelLen;
	int count = (ttask.sec + timer) / timeWheelLen;

	_Scale& s = s_timewheel[scale];

	if (s.empty())
	{
		_TaskCountGrp tcg(new int(count));
		ttask.pcount = tcg.pcount;
		tcg.pushback(&ttask);
		_TaskGrp tg(ttask.sec);
		tg.pushback(tcg);
		s.pushback(tg);

		return;
	}
	
	for (_TaskGrp& tg : s)
	{
		if (tg.sec_key == ttask.sec)
		{
			for (_TaskCountGrp& tcg : tg)
			{
				if (count == *tcg.pcount)
				{
					for (TimeTask*& pttask : tcg)
					{
						if (pttask == &ttask)return;
					}
					ttask.pcount = tcg.pcount;
					tcg.pushback(&ttask);

					return;
				}
			}
			_TaskCountGrp tcg(new int(count));
			ttask.pcount = tcg.pcount;
			tcg.pushback(&ttask);
			tg.pushback(tcg);
			
			return;
		}
	}
	_TaskCountGrp tcg(new int(count));
	ttask.pcount = tcg.pcount;
	tcg.pushback(&ttask);
	_TaskGrp tg(ttask.sec);
	tg.pushback(tcg);
	s.pushback(tg);

	return;
}

void TimeWheel::unregisterTask(TimeTask & ttask)
{
	for (int i = 0; i < timeWheelLen; i++)
	{
		_Scale& s = s_timewheel[i];
		for (_TaskGrp& tg : s)
		{
			if (tg.sec_key != ttask.sec) continue;
			for (_TaskCountGrp& tcg : tg)
			{
				if (tcg.pcount != ttask.pcount) continue;
				
				ttask.pcount = NULL;
				tcg.remove(&ttask);

				if (tcg.empty()) tg.remove(tcg);
			}
			if (tg.empty()) s.remove(tg);
		}
	}
}

bool TimeWheel::_Scale::empty()
{
	return taskGrp.empty();
}

void TimeWheel::_Scale::pushback(const _TaskGrp & tg)
{
	taskGrp.push_back(tg);
}

void TimeWheel::_Scale::remove(const _TaskGrp & tg)
{
	taskGrp.remove(tg);
}

list<TimeWheel::_TaskGrp>::iterator TimeWheel::_Scale::begin()
{
	return taskGrp.begin();
}

list<TimeWheel::_TaskGrp>::iterator TimeWheel::_Scale::end()
{
	return taskGrp.end();
}

TimeWheel::_TaskGrp::_TaskGrp(const int & sec_key) :
	sec_key(sec_key)
{
}

bool TimeWheel::_TaskGrp::empty()
{
	return taskCountGrp.empty();
}

void TimeWheel::_TaskGrp::pushback(const _TaskCountGrp & tcg)
{
	taskCountGrp.push_back(tcg);
}

void TimeWheel::_TaskGrp::remove(const _TaskCountGrp & tcg)
{
	taskCountGrp.remove(tcg);
}

list<TimeWheel::_TaskCountGrp>::iterator TimeWheel::_TaskGrp::begin()
{
	return taskCountGrp.begin();
}

list<TimeWheel::_TaskCountGrp>::iterator TimeWheel::_TaskGrp::end()
{
	return taskCountGrp.end();
}

TimeWheel::_TaskCountGrp::_TaskCountGrp(int * const & pcount) :
	pcount(pcount)
{

}

bool TimeWheel::_TaskCountGrp::empty()
{
	return timeTask.empty();
}

void TimeWheel::_TaskCountGrp::pushback(TimeTask *const & ttask)
{
	timeTask.push_back(ttask);
}

void TimeWheel::_TaskCountGrp::remove(TimeTask * const & ttask)
{
	timeTask.remove(ttask);
}

list<TimeTask*>::iterator TimeWheel::_TaskCountGrp::begin()
{
	return timeTask.begin();
}

list<TimeTask*>::iterator TimeWheel::_TaskCountGrp::end()
{
	return timeTask.end();
}
