#ifndef __BARRIER_SYNC_ 
#define __BARRIER_SYNC_

#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>

using namespace std;

class BarrierSync
{
private:
	condition_variable BarrierCond;
	mutex BarrierMutex;
	int nArrivedSignal;
	int nThreadNum;

public:
	BarrierSync(int nThreadNum);
	~BarrierSync();

	void BarrierSyncWait(bool& bRunProcessing);
	void BarrierSync::BarrierSyncReset();
};

#endif //__BARRIER_SYNC_