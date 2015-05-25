#include "ImageProcessingClass.h"

ImageProcessingClass::ImageProcessingClass(){
	
	//cout << "Inside ImageProcessing Class Contructor" << endl;

	ImageConfigParam = ConfigParameter::getSingletoneInstance();

	BarrierSyncStart = new BarrierSync(IP_THREAD_NUM);
	BarrierSyncEnd	 = new BarrierSync(IP_THREAD_NUM);
}

ImageProcessingClass::~ImageProcessingClass(){
	
	//cout << "Inside ImageProcessing Class Destructor" << endl;
	BarrierSyncStart->BarrierSyncReset();
	BarrierSyncEnd->BarrierSyncReset();
	
	for (int i = 0; i < IP_THREAD_NUM; i++){
		tImageProcessingThread[i].join();
		//cout << "ImageProcessingThread Join: " << i << endl;
	}

	delete BarrierSyncStart;
	delete BarrierSyncEnd;
}

void ImageProcessingClass::ImageProcessingInit(){

	for (int i = 0; i < IP_THREAD_NUM; i++){
		tImageProcessingThread[i] = thread(ImageProcessingThreadFuncWrapper, this, i);
		//cout << "ImageProcessingThread Create: " << i << endl;
	}
}

//This 'ImageProcessingThreadFunc' function will be called from multiple
//threads multiple times to perform the internal core operations in parallel.
void ImageProcessingClass::ImageProcessingThreadFunc(const int& nThreadID){

	//lock_guard<mutex> locker(muImageProcessingThread);

	int nInWidth = ImageConfigParam->getInImageWidth();
	int nInHeight = ImageConfigParam->getInImageHeight();
	int nOutWidth = ImageConfigParam->getOutImageWidth();
	int nOutHeight = ImageConfigParam->getOutImageHeight();

	//For optimizing the code in a homogeneous multicore system, one of the
	//strategies will be to divide the image rows in equal number of lines and 
	//run them in parallel in multiple threads. nStartLine and nEndLine will
	//indicate the starting and ending row-number of each image slice.
	int nStartLine = (nInHeight / IP_THREAD_NUM)*nThreadID;
	int nEndLine = (nInHeight / IP_THREAD_NUM)*(nThreadID + 1);

	cout << ">>>>>>>>> Inside ImageProcessingThreadFunc: " << nThreadID << ": "
		<< nStartLine << " -->> " << nEndLine << endl;

	while (ImageConfigParam->bRunProcessing) {
		//BarrierSyncStart->BarrierSyncWait will signal the starting of the
		//image processing operation (fork) in multiple image processing threads.
		BarrierSyncStart->BarrierSyncWait(ImageConfigParam->bRunProcessing);
		
		char* pImageSrc = ImageConfigParam->getImageSrc();
		char* pImageDst = ImageConfigParam->getImageDst();

		char* pImageSrcBlock = pImageSrc + (nStartLine*nInWidth);
		char* pImageDstBlock = pImageDst + (nStartLine*nOutWidth);
		
		if (!ImageConfigParam->bRunProcessing) break;
		
		//IP_Profile[nThreadID].Profile_Start();
		ImageProcessingCore(pImageDstBlock, pImageSrcBlock, nStartLine, nEndLine, nThreadID);
		//IP_Profile[nThreadID].Profile_End();
		//IP_Profile[nThreadID].Profile_Print(nThreadID);

		//BarrierSyncEnd->BarrierSyncWait will signal the ending of the
		//image processing operation (join) in multiple image processing threads.
		BarrierSyncEnd->BarrierSyncWait(ImageConfigParam->bRunProcessing);
	}
}

//ImageProcessingCore function contains the computation and memory intensive
//parts of the code. This function will act on the image slice determined by
//the nStartLine and nEndLine.
void ImageProcessingClass::ImageProcessingCore(char* pImageDstBlock, 
	char* pImageSrcBlock, int& nStartLine, int& nEndLine, int nThreadID){
	
	int nInWidth = ImageConfigParam->getInImageWidth();
	int nInHeight = ImageConfigParam->getInImageHeight();
	int nOutWidth = ImageConfigParam->getOutImageWidth();
	int nOutHeight = ImageConfigParam->getOutImageHeight();

	if (nThreadID == 0){
		for (int i = 0; i < (nEndLine - nStartLine); i++){
			for (int j = 0; j < nInWidth; j++){
				*(pImageDstBlock + (i*nInWidth)+j) = *(pImageSrcBlock + (i*nOutWidth)+j) + 10;
				float f = 999.999 / 222.111;
			}
		}
	}
	else if (nThreadID == 1){
		for (int i = 0; i < (nEndLine - nStartLine); i++){
			for (int j = 0; j < nInWidth; j++){
				*(pImageDstBlock + (i*nInWidth) + j) = *(pImageSrcBlock + (i*nOutWidth) + j) + 5;
				int f = 999 / 222;
			}
		}
	}
	else{
		for (int i = 0; i < (nEndLine - nStartLine); i++){
			for (int j = 0; j < nInWidth; j++){
				*(pImageDstBlock + (i*nInWidth) + j) = *(pImageSrcBlock + (i*nOutWidth) + j) + 0;
				float f = 999.999 / 222.111;
			}
		}
	}
}
