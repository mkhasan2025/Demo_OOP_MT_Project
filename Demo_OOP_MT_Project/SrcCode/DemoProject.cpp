#include<iostream>
#include<memory>
#include "ImagingSolutionInterface.h"

void PrintImage(int& nWidth, int& nHeight, char *pImage);

//This is the beginning of this demo project


void main()
{
	cout << "Imaging Solution" << endl;
	cout << endl << endl << endl << endl;

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

	//Instantiate Object for Imaging Solution 1
	ImagingSolutionInterface *ImagingIF;
	ImagingIF = ImagingSolutionInterface::GetImagingSolutionInstance(IMAGING_SOLUTION_1);
	
	//Initialization of Imaging Solution
	ImagingIF->ImagingInit(nInImageWidth, nInImageHeight, nOutImageWidth, nOutImageHeight);

	//This loop represents the incoming Video Frames
	for (int i = 0; i < nFrameNum; i++)
	{
		//Create Video Frame: demo version
		memset(pImageSrc, i + 1, nInputFrameSize);
		
		//Send Video Frame to Library for Processing
		ImagingIF->ImagingProcess(pImageSrc, pImageDst);

		PrintImage(nOutImageWidth, nOutImageHeight, pImageDst);
	}

	//Deinitialization of Imaging Solution 
	ImagingIF->ImagingDeinit();

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