#ifndef __IMAGE_PROCESSING_CLASS
#define __IMAGE_PROCESSING_CLASS

#include <iostream>
#include <thread>
#include <mutex>

#include "ConfigParameter.h"
#include "BarrierSync.h"
#include "Profiler.h"

using namespace std;

static const int IP_THREAD_NUM = 3;

class ImageProcessingClass{
private:
	int ip_thread_num;
	
	ConfigParameter *ImageConfigParam;
	Profiler IP_Profile[IP_THREAD_NUM];
	
	thread tImageProcessingControlThread;
	thread tImageProcessingThread[IP_THREAD_NUM];
	mutex muImageProcessingThread;

	void ImageProcessingThreadFunc(const int& nThreadID);
	void ImageProcessingCore(char* pImageDstBlock, char* pImageSrcBlock, 
		int& nStartLine, int& nEndLine, int nThreadID);

	static void ImageProcessingThreadFuncWrapper(void *arg, const int& nThreadID){
		ImageProcessingClass *IPClass = static_cast<ImageProcessingClass*>(arg);
		IPClass->ImageProcessingThreadFunc(nThreadID);
	}

public:
	BarrierSync *BarrierSyncStart;
	BarrierSync *BarrierSyncEnd;

	ImageProcessingClass();
	~ImageProcessingClass();

	void ImageProcessingInit();

};

#endif //__IMAGE_PROCESSING_CLASS