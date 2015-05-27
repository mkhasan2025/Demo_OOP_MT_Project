//contact: mkhasan2025@gmail.com

#ifndef __IMAGING_SOLUTION_INTERFACE_
#define __IMAGING_SOLUTION_INTERFACE_

/*
ImagingSolutionInterface is an abstract class, which means it cannot
be instantiated. This class has been created to polymorphically provide
an interface for its various child classes. All the interfaces are
provided via pure virtual functions which are overridden by the functions
in the clild classes. This is how the implementation detail has been
hidden from the outside world.
*/

using namespace std;

//enum ImagingSolutionEnum denotes different features / different 
//versions of this software solution. This is part of the interface
//and will be sent in as a parameter to decide the polymorphical
//instantiation of a particular child class.
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

	//virtual destructor will make sure that, the destructor of the
	//child classes will be invoked when the base class's destructor
	//will be called. This is mandatory in any polymorphism case to
	//make sure that no memory leak happens.
	virtual ~ImagingSolutionInterface();

	//The following three functions are declared as pure virtual functions
	//without any definition. These functions are defined in the overridden
	//functions in the child classes.
	virtual void ImagingInit(int nInWidth, int nInHeight, int nOutWidth, int nOutHeight) = 0;	
	virtual void ImagingProcess(char* pSrc, char* pDst) = 0;
	virtual void ImagingDeinit() = 0;

	//Static member function of a class can be called without instantiating
	//the class. So when the following function will be called from the outside
	//world, there will be no need to instantiate an object of this abstract
	//class. Inside the function definition, instance of the child classes
	//(which will define various features or different version of the same
	//feature) will be returned polymorphically by casting them as a base class.
	//The parameter nSolutionID which is passed in from the outside will be
	//used to decide which child class will be instantiated and then returned.
	
	static ImagingSolutionInterface* GetImagingSolutionInstance(int nSolutionID);
};

#endif //__IMAGING_SOLUTION_INTERFACE_