#include "ImagingSolution.h"

ImagingSolution::ImagingSolution()
{
	ImageConfigParam = ConfigParameter::getSingletoneInstance();
	ImageProcessing1 = new ImageProcessingClass();

	cout << endl << endl << endl << endl;
}

ImagingSolution::~ImagingSolution(){
	
	delete ImageProcessing1;
	delete ImageConfigParam;

	cout << "Inside Destructor ImagingSolution" << endl;
}

void ImagingSolution::ImagingInit(int nInWidth, int nInHeight, int nOutWidth, int nOutHeight){

	ImageConfigParam->setImageConfigParam(nInWidth, nInHeight, nOutWidth, nOutHeight);
	ImageProcessing1->ImageProcessingInit();

	ImageConfigParam->bRunProcessing = true;
}

void ImagingSolution::ImagingDeinit(){
	ImageConfigParam->bRunProcessing = false;
}

void ImagingSolution::ImagingProcess(char* pSrc, char *pDst){
	
	ImageConfigParam->setVideoFrame(pSrc, pDst);

	//BarrierSyncStart->BarrierSyncWait will signal the starting of the
	//image processing operation (fork) in multiple image processing threads.
	//BarrierSyncEnd->BarrierSyncWait will signal the ending of the
	//image processing operation (join) in multiple image processing threads.
	ImageProcessing1->BarrierSyncStart->BarrierSyncWait(ImageConfigParam->bRunProcessing);
	ImageProcessing1->BarrierSyncEnd->BarrierSyncWait(ImageConfigParam->bRunProcessing);
}