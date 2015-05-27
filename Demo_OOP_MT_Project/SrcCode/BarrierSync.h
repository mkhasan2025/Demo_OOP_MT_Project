//contact: mkhasan2025@gmail.com

#ifndef __BARRIER_SYNC_ 
#define __BARRIER_SYNC_

/*
The BarrierSync Class demonstrates an elegant way to utilize the
'conditional-wait' & 'notify' functionalities in multi-threading
scenario. This can be an effective method to synchronize the works
of
	(1) Multiple worker-threads: which will perform some
	parallelizable tasks and

	(2) A control-thread: which will control the starting
	of those parallelizable tasks and wait until all the
	worker-threads finish their tasks.

These concepts of binding thread control / synchronization activities
in 'one single class' can inspire some new type of ideas in different
multi-threading scenarios. This is a very convenient way to reuse the
code in a complex project. In addition to that, this class is an example
of hiding the implementation detail and providing user with a simple &
easy multi-thread control mechanism.
*/

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