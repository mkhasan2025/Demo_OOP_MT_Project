#ifndef __CONFIG_PARAM
#define __CONFIG_PARAM

#include <iostream>

using namespace std;

class ConfigParameter{
private:
	int nInImageWidth, nInImageHeight;
	int nOutImageWidth, nOutImageHeight;
	char *pImageSrc, *pImageDst;

	ConfigParameter();

	static bool cpInstanceFlag;
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
	
	ConfigParameter(const ConfigParameter&) = delete;
	ConfigParameter & operator=(const ConfigParameter&) = delete;
};


#endif //__CONFIG_PARAM