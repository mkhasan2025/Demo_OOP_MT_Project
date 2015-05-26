#include "BarrierSync.h"


BarrierSync::BarrierSync(int nNum)
{
	nThreadNum = nNum;
	nArrivedSignal = 0;
}

BarrierSync::~BarrierSync()
{

}

//BarrierSyncWait method leverages the conditional wait and broadcast
//(notify_all) mechanism. This will be used when a control thread has 
//to signal multiple worker threads (waiting for the wake-up call) to 
//start working. On the other hand, it can also be used when the worker 
//threads (after their job is done) has to signal back to the control 
//thread (which is waiting for wake-up call) and notify that the worker 
//threads have finished doing their work.

//Here, the mutex must be locked to make sure that the increment of
//nArrivedSignal variable is an atomic operation. As conditional wait
//has been used, the unique_lock template class(instead of lock_guard 
//has to be used for locking the mutex. Because the mutex will be un-
//locked immediately when the condition will go to waiting state later.

void BarrierSync::BarrierSyncWait(bool& bRunProcessing){
	//Only proceed when the processing is going on.
	if (bRunProcessing){
		unique_lock<mutex> lk(BarrierMutex);
		nArrivedSignal++;

		//Here (nThreadNum + 1) signifies all the worker-threads + 1 control-thread
		if (nArrivedSignal < nThreadNum + 1) {
			BarrierCond.wait(lk);
			// To-do: Need to take care of the spurious wake up scenario
		}
		else {
			//notify_all() is called when all the threads (including all worker-
			//threads and control-threads) reach the BarrierSyncWait(). And thus
			//all threads that are involved get the wake-up call to proceed further.
			BarrierCond.notify_all();
			nArrivedSignal = 0;
		}
	}
}

//BarrierSyncReset calls a notify_all function when the thread related jobs
//are all done and the thread is about to join. The main purpose here is to
//send notification to all the other threads which are in waiting state now.
void BarrierSync::BarrierSyncReset(){
	BarrierCond.notify_all();
}
