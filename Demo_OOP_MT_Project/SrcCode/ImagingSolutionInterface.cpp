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
	//Here different cases may instantiate different 
	//child classes which represents different features
	//and version of the ImageProcessing solution.

	case IMAGING_SOLUTION_1:
		return static_cast<ImagingSolutionInterface*> (new ImagingSolution);
		break;

	case IMAGING_SOLUTION_2:
		return NULL; //TEMP
		//For practice, a new class named 'ImagingSolution2'
		//can be created which may compose a newly created
		//class 'ImageProcessingClass2'. That new class may
		//support a different algorithm for processing an
		//image / video frame or it may denote a new version
		//'ImageProcessingClass1'.
		break;

	case IMAGING_SOLUTION_3:
		return NULL; //TEMP
		break;

	default:
		return NULL;
		break;
	}
}
