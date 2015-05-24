#ifndef __IMAGING_SOLUTION_INTERFACE_
#define __IMAGING_SOLUTION_INTERFACE_

using namespace std;

enum ImagingSolutionEnum
{
	IMAGING_SOLUTION_1 = 1,
	IMAGING_SOLUTION_2 = 2,
	IMAGING_SOLUTION_3 = 3,
};

class ImagingSolutionInterface
{
public:
	ImagingSolutionInterface();
	virtual ~ImagingSolutionInterface();

	virtual void ImagingInit(int nInWidth, int nInHeight, int nOutWidth, int nOutHeight) = 0;	
	virtual void ImagingProcess(char* pSrc, char* pDst) = 0;
	virtual void ImagingDeinit() = 0;

	static ImagingSolutionInterface* GetImagingSolutionInstance(int nSolutionID);
};

#endif //__IMAGING_SOLUTION_INTERFACE_