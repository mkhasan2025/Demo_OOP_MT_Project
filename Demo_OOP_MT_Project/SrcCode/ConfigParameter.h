//contact: mkhasan2025@gmail.com

#ifndef __CONFIG_PARAM
#define __CONFIG_PARAM

/*
This class demonstrates a single-tone design pattern where ONE object of
a singletone class is used throughout the project to coordinate and share
information. In this design pattern, only one instance of the class can be
instantiated and later that instance will be used (read / write / modify 
data member and invoke methods) everywhere by other classes.

ConfigParameter class contains all the basic configuration parameters in
the project (in this example, config-parameters of image/video frames). It
can be always extended by adding new data or function members depending
on the nature of the project. This is an example on, how we can easily use
the same instance of a class throughout the project instead of passing it 
by pointer as a parameter during the function (of different classes) call.
*/

#include <iostream>

using namespace std;

class ConfigParameter{
private:
	int nInImageWidth, nInImageHeight;
	int nOutImageWidth, nOutImageHeight;
	char *pImageSrc, *pImageDst;

	//As a singletone class, the constructor of this class
	//has been declared as private to disable any kind of
	//instantiation of this class via constructor.
	ConfigParameter();

	//static bool cpInstanceFlag will be used as a flag to
	//track object instantiation status of this class.
	static bool cpInstanceFlag;

	//static member cpInstance denotes the pointer to the
	//only object that can be instantiated from this class 
	static ConfigParameter *cpInstance;

public:
	~ConfigParameter();

	bool bRunProcessing;

	static ConfigParameter* getSingletoneInstance();

	//Disable the default copy-constructor and copy-assignment
	//operator for this class to protect its singletone nature.
	ConfigParameter(const ConfigParameter&) = delete;
	ConfigParameter & operator=(const ConfigParameter&) = delete;
	
	//These two setter-functions set the basic config parameters to the member
	//of ConfigParameters class. Once set, as the same instance will be used
	//in every other class, these assigned values can be accessed everywhere
	//using the following get functions.
	void setImageConfigParam(int& nInWidth, int& nInHeight, int& nOutWidth, int& nOutHeight);
	void setVideoFrame(char *pSrc, char *pDst);

	int getInImageWidth();
	int getInImageHeight();
	int getOutImageWidth();
	int getOutImageHeight();
	
	char* getImageSrc();
	char* getImageDst();
};


#endif //__CONFIG_PARAM
