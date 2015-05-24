#ifndef __PROFILER_
#define __PROFILER_

#include<iostream>
#include<chrono>
#include<Windows.h>

enum Profile_State
{
	PROFILE_NOOP = 0,
	PROFILE_START =1,
	PROFILE_END	=2,
};

class Profiler
{
private:
	int nProfilerState;
	//long long int nStartTime, nEndTime, nTimeDiff;
	unsigned long nStartTime, nEndTime, nTimeDiff;
public:
	Profiler();
	~Profiler();

	void Profile_Start();
	void Profile_End();
	void Profile_Print(int nID);
};

#endif //__PROFILER_