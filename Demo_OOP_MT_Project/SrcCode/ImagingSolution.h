#ifndef __IMAGING_SOLUTION
#define __IMAGING_SOLUTION

#include<iostream>
#include "ImagingSolutionInterface.h"
#include "ImageProcessingClass.h"
#include "ConfigParameter.h"

class ImagingSolution : public ImagingSolutionInterface
{
private:
	ConfigParameter *ImageConfigParam;

	ImageProcessingClass *ImageProcessing1;

public:
	ImagingSolution();
	~ImagingSolution();

	virtual void ImagingInit(int nInWidth, int nInHeight, int nOutWidth, int nOutHeight);
	virtual void ImagingProcess(char* pSrc, char* pDst);
	virtual void ImagingDeinit();
};

#endif //__IMAGING_SOLUTION