#include "StdAfx.h"
#include "Resource.h"
#include "captchaMainDialog.h"

CAppModule _AppModule;


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR lpCmdLine, int nCmdShow)
{
	// Init WTL app module
	::InitCommonControls();
	_AppModule.Init(NULL, hInstance);

	//srand
	srand(::GetTickCount());

	// Show main dialog
	CMainDialog dlgMain;
	dlgMain.DoModal();

	// Close WTL app module
	_AppModule.Term();
	return 0;
}
