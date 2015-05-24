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

void ImageProcessingClass::ImageProcessingThreadFunc(const int& nThreadID){

	//lock_guard<mutex> locker(muImageProcessingThread);

	int nInWidth = ImageConfigParam->getInImageWidth();
	int nInHeight = ImageConfigParam->getInImageHeight();
	int nOutWidth = ImageConfigParam->getOutImageWidth();
	int nOutHeight = ImageConfigParam->getOutImageHeight();

	int nStartLine = (nInHeight / IP_THREAD_NUM)*nThreadID;
	int nEndLine = (nInHeight / IP_THREAD_NUM)*(nThreadID + 1);

	cout << ">>>>>>>>> Inside ImageProcessingThreadFunc: " << nThreadID << ": "
		<< nStartLine << " -->> " << nEndLine << endl;

	while (ImageConfigParam->bRunProcessing) {
		
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

		BarrierSyncEnd->BarrierSyncWait(ImageConfigParam->bRunProcessing);
	}
}

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

#if 0
void ImageProcessingClass::ImageProcessingCore(char* pImageDstBlock,
	char* pImageSrcBlock, int& nStartLine, int& nEndLine, int nThreadID){

	int nInWidth = ImageConfigParam->getInImageWidth();
	int nInHeight = ImageConfigParam->getInImageHeight();
	int nOutWidth = ImageConfigParam->getOutImageWidth();
	int nOutHeight = ImageConfigParam->getOutImageHeight();

	if (nThreadID == 0){
		for (int i = 0; i < (nEndLine - nStartLine); i++){
			memcpy(pImageDstBlock + (i*nInWidth), pImageSrcBlock + (i*nOutWidth), nOutWidth);
		}
	}
	else if (nThreadID == 1){
		for (int i = 0; i < (nEndLine - nStartLine); i++){
			memset(pImageDstBlock + (i*nInWidth), 0x7, nOutWidth);
		}
	}
	else{
		for (int i = 0; i < (nEndLine - nStartLine); i++){
			memset(pImageDstBlock + (i*nInWidth), 0x3, nOutWidth);
		}
	}
}
#endif