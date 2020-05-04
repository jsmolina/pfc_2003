#ifndef WRAPPER_H
#define WRAPPER_H
#define MAX 255
#define WRAPPER_EVENTID 949689

	bool  IsInitialized();
	void  Initialize();
// EL DESTRUCTOR ESTÀ A DLL_PROCESS_DETACH

// mètodes Siapp estàndard RW[SIAPP->WRAPPER]
bool			CDSetMode(bool veure_interficie);
int				CDOpen(bool polling);
void			CDGetEventWinInit(SiGetEventData *pData, UINT msg, WPARAM wParam, LPARAM lParam);
enum SpwRetVal	CDGetEvent(SiGetEventData * pData, SiSpwEvent * pRetorn);
bool			CDSendMessage();
SiDevInfo *		CDGetVirtualDeviceInfo();
SiDevPort *		CDGetVirtualDevicePort();
SiVerInfo *		CDGetVirtualLibraryInfo();
bool			CDInitialize();
bool			CDTerminate(HWND h);
bool			CDOpenWinInit(HWND hwnd);
int				CDButtonPressed (SiSpwEvent *pEvent);
int				CDButtonReleased (SiSpwEvent *pEvent);
bool			CDClose(HWND h);



bool IsNewRegister();


#endif