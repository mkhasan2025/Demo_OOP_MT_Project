#include "ConfigParameter.h"

ConfigParameter::ConfigParameter(){
}

ConfigParameter::~ConfigParameter(){
	cpInstanceFlag = false;
}

//static class members have to be always initiated outside the 
//definition of the class. The static member 'cpInstanceFlag'
//and 'cpInstance' will make sure that it will always have a 
//single instance regardless of how many times the object has
//been instantiated in different other classes. Thus it will
//ensure the singletone design objective of this ConfigParameter
//class.
bool ConfigParameter::cpInstanceFlag = false;
ConfigParameter* ConfigParameter::cpInstance = NULL;

ConfigParameter* ConfigParameter::getSingletoneInstance(){
	
	if (!cpInstanceFlag){
		cout << "Inside ConfigParameter::getInstance()" << endl;
		cpInstance = new ConfigParameter();
		cpInstanceFlag = true;
	}
	
	return cpInstance;
}

void ConfigParameter::setImageConfigParam(int& nInWidth, int& nInHeight, int& nOutWidth, int& nOutHeight){

	nInImageWidth = nInWidth;
	nInImageHeight = nInHeight;
	nOutImageWidth = nOutWidth;
	nOutImageHeight = nOutHeight;

	cout << "Inside setImageConfigParam: " 
		<< nInImageWidth << " x " << nInImageHeight << " -->> "
		<< nOutImageWidth << " x " << nOutImageHeight << endl;
}

void ConfigParameter::setVideoFrame(char* pSrc, char* pDst){
	
	pImageSrc = pSrc;
	pImageDst = pDst;
}

int ConfigParameter::getInImageWidth(){
	//cout << "Inside getImageWidth: "<< nInImageWidth << endl;
	return nInImageWidth;
}

int ConfigParameter::getInImageHeight(){
	//cout << "Inside getImageHeight: " << nInImageHeight << endl;
	return nInImageHeight;
}

int ConfigParameter::getOutImageWidth(){
	//cout << "Inside getOutImageWidth: " << nOutImageWidth << endl;
	return nOutImageWidth;
}

int ConfigParameter::getOutImageHeight(){
	//cout << "Inside getOutImageHeight: " << nOutImageHeight << endl;
	return nOutImageHeight;
}

char* ConfigParameter::getImageSrc(){
	//cout << "Inside getImageSrc: 0x" << hex <<int(pImageSrc) << endl;
	return pImageSrc;
}

char* ConfigParameter::getImageDst(){
	//cout << "Inside getImageDst: 0x" << hex << int(pImageDst) << endl;
	return pImageDst;
}