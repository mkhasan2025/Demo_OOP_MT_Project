#include "BarrierSync.h"


BarrierSync::BarrierSync(int nNum)
{
	nThreadNum = nNum;
	nArrivedSignal = 0;
}

BarrierSync::~BarrierSync()
{

}

//This BarrierSync method levearages the conditional wait and broadcast
//(notify_all) mechanism. This will be used when a control thread has 
//to signal multiple worker threads (at waiting status) to start 
//working. On the other hand, it can also be used when the worker 
//threads (after their job is done) has to signal back to the control 
//thread (which is at a waiting state) and notify that the worker 
//threads have finished doing their work.

//Here, the mutex must be locked to make sure that the increament 
//of nArrivedSignal variable is an atomic operation. As conditional
//wait has been used here, the unique_lock template class (instead 
//of lock_guard) should be used for locking the mutex. Because the 
//mutex will be unlocked immediately when the condition will go to
//waiting state in the subsequent line.

void BarrierSync::BarrierSyncWait(bool& bRunProcessing){
	if (bRunProcessing){
		unique_lock<mutex> lk(BarrierMutex);
		nArrivedSignal++;

		if (nArrivedSignal < nThreadNum + 1) {
			BarrierCond.wait(lk); // Need to take care of the spurious wake up scenario
		}
		else {
			BarrierCond.notify_all();
			nArrivedSignal = 0;
		}
	}
}

//BarrierSyncReset will be used to call a notify_all function
//when the thread related jobs are all done and the thread is
//about to join. The main purpose is to send notification to 
//all the other threads which are in waiting state.
void BarrierSync::BarrierSyncReset(){
	BarrierCond.notify_all();
}
