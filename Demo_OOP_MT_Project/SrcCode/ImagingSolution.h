//contact: mkhasan2025@gmail.com

#ifndef __IMAGING_SOLUTION
#define __IMAGING_SOLUTION

/*
ImagingSolution class is one of the classes derived from the abstract
base class named ImagingSolutionInterface. This class contains the 
functionality of a certain feature (eg. ImageProcessingClass) or a 
combination of features or a certain version. It will act as a 
polymorphically derived class of ImagingSolutionInterface. That is
why, it overrides all the pure virtual function of its base class. 
*/

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