#include<iostream>
#include<memory>
#include "ImagingSolutionInterface.h"

void PrintImage(int& nWidth, int& nHeight, char *pImage);

//This is the beginning of this demo project

void main()
{
	cout << "Imaging Solution" << endl;
	cout << endl << endl << endl << endl;

	//Setting the basic configuration
	//parameters of this project
	int nFrameNum = 10;

	int nInImageWidth = 1920;// 40;
	int nInImageHeight = 1080;// 30;
	int nOutImageWidth = 1920;// 40;
	int nOutImageHeight = 1080;// 30;
	
	int nInputFrameSize = nInImageWidth*nInImageHeight;
	int nOutputFrameSize = nOutImageWidth*nOutImageHeight;

	char *pImageSrc = new char[nInputFrameSize];
	char *pImageDst = new char[nOutputFrameSize];

	memset(pImageSrc, 0x0, nInputFrameSize);
	memset(pImageDst, 0x0, nOutputFrameSize);
	//=======================================================

	//From the outside world (in this example, the main function; in other
	//cases it can be outside of a library), the only known (shared outside
	//of the library) information is the definition of the abstract base
	//class 'ImagingSolutionInterface'.

	//In this design pattern, the base class will polymorphically represent
	//the child classes. All that a user has to know is the function (pure
	//virtual) members of the base class 'ImagingSolutionInterface'. All the
	//implementation details are hidden inside the child classes.
	
	//The child classes represent different feature / version of a certain
	//software solution. For example, we want to develop a solution which
	//has two different use-case scenarios. Those two use-case scenarios
	//are defined in two different child classes (which may combine a few
	//more classes in different arrangement via inheritance and composition).
	//Now the user (who only knows the simple interface of the abstract base
	//class) can instantiate the class (of a scenario) of his/her choice by 
	//selecting a proper member from the enum 'ImagingSolutionEnum'. After
	//that, they can interact with the child class with 3 simple function
	//interfaces: init, process and deinit.

	ImagingSolutionInterface *ImagingIF;
	ImagingIF = ImagingSolutionInterface::GetImagingSolutionInstance(IMAGING_SOLUTION_1);
	
	//Initialization of Imaging Solution
	ImagingIF->ImagingInit(nInImageWidth, nInImageHeight, nOutImageWidth, nOutImageHeight);

	//In this example: this loop represents the incoming Video Frames
	for (int i = 0; i < nFrameNum; i++)
	{
		//Create an imaginary video frame for this demo version.
		//In actual case, we can read the raw video data from a
		//file or invoke video frame from a camera device.
		memset(pImageSrc, i + 1, nInputFrameSize);
		
		//Send Video Frame to Library (or in this case internal
		//class implementation) for Processing for the scenario
		//enum 'IMAGING_SOLUTION_1' >> 'ImagingSolutionClass'
		ImagingIF->ImagingProcess(pImageSrc, pImageDst);

		//Print the output video frame. In actual case, we can write
		//the raw video data to a file or send the output frame to
		//the encoder or display hardware.
		PrintImage(nOutImageWidth, nOutImageHeight, pImageDst);
	}

	//Deinitialization of Imaging Solution 
	ImagingIF->ImagingDeinit();

	//We should never forget to delete / free all
	//the memory spaces that we have allocated.
	delete[] pImageSrc;
	delete[] pImageDst;

	delete ImagingIF;

	system("pause");
}

void PrintImage(int& nWidth, int& nHeight, char *pImage){
	//for (int i = 0; i < nHeight; i++){
	for (int i = 0; i < 2; i++){
		for (int j = 0; j < 30; j++){
		//for (int j = 0; j < nWidth; j++){
			int nPixelValue = *(pImage + (i*nWidth) + j);
			cout << nPixelValue;
		}
		cout << endl;
	}
	cout << endl << endl;
}