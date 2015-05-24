#include "Profiler.h"

using namespace std;

Profiler::Profiler()
{
	nProfilerState = PROFILE_NOOP;
}


Profiler::~Profiler()
{
	nProfilerState = PROFILE_NOOP;
}

void Profiler::Profile_Start(){
	if (nProfilerState == PROFILE_NOOP)
		//chrono::steady_clock::time_point nStartTime = chrono::steady_clock::now();
		nStartTime = GetTickCount();
		nProfilerState = PROFILE_START;
}
void Profiler::Profile_End(){
	
	if (nProfilerState == PROFILE_START){
		//chrono::steady_clock::time_point nEndTime = chrono::steady_clock::now();
		nEndTime = GetTickCount();
		nProfilerState = PROFILE_END;
	}
}
void Profiler::Profile_Print(int nID){
	if (nProfilerState == PROFILE_END)
	{
		nTimeDiff = nEndTime - nStartTime;
		//cout << "[" << nID << "] nTimeDiff: " << nTimeDiff		 
			//<< "  START: " << nStartTime << "  END: " << nEndTime << endl;

		cout << "[" << nID << "] nTimeDiff: " << nTimeDiff
			<< "  START: " << nStartTime << "  END: " << nEndTime << endl;
	}
}