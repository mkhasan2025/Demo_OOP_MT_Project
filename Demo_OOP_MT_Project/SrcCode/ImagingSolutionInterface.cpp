#include "ImagingSolutionInterface.h"
#include"ImagingSolution.h"

ImagingSolutionInterface::ImagingSolutionInterface()
{

}

ImagingSolutionInterface::~ImagingSolutionInterface()
{
	cout << "Inside Destructor ImagingSolutionInterface" << endl;
}

ImagingSolutionInterface* ImagingSolutionInterface::GetImagingSolutionInstance(int nSolutionID)
{
	switch (nSolutionID)
	{
	case IMAGING_SOLUTION_1:
		return static_cast<ImagingSolutionInterface*> (new ImagingSolution);
		break;

	case IMAGING_SOLUTION_2:
		return NULL; //TEMP
		break;

	case IMAGING_SOLUTION_3:
		return NULL; //TEMP
			break;

	default:
		return NULL;
		break;
	}
}