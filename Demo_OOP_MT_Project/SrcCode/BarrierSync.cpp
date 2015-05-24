#include "BarrierSync.h"


BarrierSync::BarrierSync(int nNum)
{
	nThreadNum = nNum;
	nArrivedSignal = 0;
}

BarrierSync::~BarrierSync()
{

}

void BarrierSync::BarrierSyncWait(bool& bRunProcessing){
	if (bRunProcessing){
		unique_lock<mutex> lk(BarrierMutex);
		nArrivedSignal++;

		if (nArrivedSignal < nThreadNum + 1) {
			BarrierCond.wait(lk); // [](){if (nArrivedSignal < nThreadNum + 1) return 1;}
		}
		else {
			BarrierCond.notify_all();
			nArrivedSignal = 0;
		}
	}
}

void BarrierSync::BarrierSyncReset(){
	BarrierCond.notify_all();
}