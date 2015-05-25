#ifndef __PROFILER_
#define __PROFILER_

/*
This class works for the purpose of software profiling.
Having a profiler class of this type is very important 
in any project. I am trying to use the C++11 here for 
this purpose instead of the C codes which I have always
used in the past. For some reasons, it is not working
right now. I will make it work in future.
*/

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