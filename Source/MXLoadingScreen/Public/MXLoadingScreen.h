#ifndef _MXLOADINGSCREEN_H_
#define _MXLOADINGSCREEN_H_


#include "ModuleInterface.h"
#include "ModuleManager.h"

class IMXLoadingScreenModule : public IModuleInterface

{

public :
	virtual void StartInGameLoadingScreen() = 0;
	virtual void ShutDownLoadingScreen()=0;

};

#endif // _MXLOADINGSCREEN_H_