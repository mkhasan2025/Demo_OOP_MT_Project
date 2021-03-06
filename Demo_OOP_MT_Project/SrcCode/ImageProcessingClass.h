//contact: mkhasan2025@gmail.com

#ifndef __IMAGE_PROCESSING_CLASS
#define __IMAGE_PROCESSING_CLASS

/*
This class contains (1) the core functionalities of the image
processing block and (2) the thread implementation to run the
image processing core in parallel. The techniques demonstrated
in this class can be used as a template to declare any other
class which can do any kind of tasks in parallel.
*/

#include <iostream>
#include <thread>
#include <mutex>

#include "ConfigParameter.h"
#include "BarrierSync.h"
#include "Profiler.h"

using namespace std;

//Total number of threads for running the core functionality
//of image processing class in parallel. The number of threads
//will be determined based on the system configuration and 
//experimentation through software profiling.
static const int IP_THREAD_NUM = 3;

class ImageProcessingClass{
private:

	//ConfigParameter's singletone instance is one 
	//of the class members of ImageProcessingClass.
	ConfigParameter *ImageConfigParam;
	Profiler IP_Profile[IP_THREAD_NUM];
	
	//thread tImageProcessingControlThread;
	thread tImageProcessingThread[IP_THREAD_NUM];
	mutex muImageProcessingThread;

	void ImageProcessingThreadFunc(const int& nThreadID);
	void ImageProcessingCore(char* pImageDstBlock, char* pImageSrcBlock, 
		int& nStartLine, int& nEndLine, int nThreadID);

	//All non-static class member functions have a hidden 'this' pointer.
	//That is why ImageProcessingThreadFunc() cannot be passed in as a
	//parameter to the thread-creation function. On the other hand, static
	//member functions do not have a 'this' pointer. So a static wrapper
	//function is needed for the ImageProcessingThreadFunc() when passing 
	//it as a parameter during the thread initiation.
	static void ImageProcessingThreadFuncWrapper(void *arg, const int& nThreadID){
		ImageProcessingClass *IPClass = static_cast<ImageProcessingClass*>(arg);
		IPClass->ImageProcessingThreadFunc(nThreadID);
	}

public:
	//These two BarrierSync objects will signal the fork
	//and join of multiple ImageProcessing Threads.
	BarrierSync *BarrierSyncStart;
	BarrierSync *BarrierSyncEnd;

	ImageProcessingClass();
	~ImageProcessingClass();

	void ImageProcessingInit();

};

#endif //__IMAGE_PROCESSING_CLASS
