/*
ConfigParameter class contains all the basic configuration
parameters of a the image/video frames. This is designed to
be a singletone class so that only one instance of the class
can be instantiated throughout the project and that single
object will be used (modified, read) by all other classes.
*/

#ifndef __CONFIG_PARAM
#define __CONFIG_PARAM

#include <iostream>

using namespace std;

class ConfigParameter{
private:
	int nInImageWidth, nInImageHeight;
	int nOutImageWidth, nOutImageHeight;
	char *pImageSrc, *pImageDst;

	// As a singletone class, the constructor of this
	// class has been declared as private to disable 
	// the instantiation of this class via contructor.
	ConfigParameter();

	// cpInstanceFlag will be used to control the object
	// instantiation of this singletone class.
	static bool cpInstanceFlag;
	// static member cpInstance denotes the pointer to the
	// only object that will be instantiated from this class 
	static ConfigParameter *cpInstance;

public:
	~ConfigParameter();

	bool bRunProcessing;

	static ConfigParameter* getSingletoneInstance();

	void setImageConfigParam(int& nInWidth, int& nInHeight, int& nOutWidth, int& nOutHeight);
	void setVideoFrame(char *pSrc, char *pDst);

	int getInImageWidth();
	int getInImageHeight();
	int getOutImageWidth();
	int getOutImageHeight();
	
	char* getImageSrc();
	char* getImageDst();
	
	//Disable the default copy-constructor and copy-assignment-operator
	//for this singletone class.
	ConfigParameter(const ConfigParameter&) = delete;
	ConfigParameter & operator=(const ConfigParameter&) = delete;
};


#endif //__CONFIG_PARAM