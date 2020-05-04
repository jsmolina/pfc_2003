#ifndef SIAPP_DLL_LIB
#define SIAPP_DLL_LIB

#define OS_WIN32
#include <windows.h>
#include <si.h> // això apuntarà a on estigui instal·lat el header
#include <spwerror.h> // però ara per comoditat, els he ficat 
#include <version.h>  // al directori de la aplicació.
//#include "spwmacro.h"
//#include "spwdata.h"
///////////////////////////////////////////////////
// ADDED INFO
///////////////////////////////////////////////////

enum InitResult 
   {
   NOT_LOADED, 
   FAILED, 
   LOADED
   };

enum ErrorCode 
   {
   NO_DLL_ERROR=0,
   DLL_LOAD_FAILURE,
   DLL_FUNCTION_LOAD_FAILURE,
   DLL_VAR_LOAD_FAILURE
   };
enum SpwRetVal *pDllSpwRetVal;



/*
 *  Static version strings for executable identification.
 */
/*
static char SpwLibVersion[] = SPW_LIB_VERSION;
static char SiiLibVersion[] = SII_LIB_VERSION;
static char SiiLibDate[] = SII_LIB_DATE;
static LPCTSTR DllLibrary = "siappdll";
static LPCSTR strDLLRetVal          = "SpwErrorVal";

static LPCSTR fnSiBeep              = "SiBeep";
static LPCSTR fnSiInitialize        = "SiInitialize";
 static LPCSTR fnSiTerminate         = "SiTerminate";
 static LPCSTR fnSiGetDeviceID       = "SiGetDeviceID";
 static LPCSTR fnSiGetNumDevices     = "SiGetNumDevices";
 static LPCSTR fnSiDeviceIndex       = "SiDeviceIndex";
 static LPCSTR fnSiDispatch          = "SiDispatch";
 static LPCSTR fnSiIsSpaceWareEvent  = "SiIsSpaceWareEvent";
 static LPCSTR fnSiOpenWinInit       = "SiOpenWinInit";
 static LPCSTR fnSiOpen              = "SiOpen";
 static LPCSTR fnSiClose             = "SiClose";
 static LPCSTR fnSiGetEventWinInit   = "SiGetEventWinInit";
 static LPCSTR fnSiGetEvent          = "SiGetEvent";
 static LPCSTR fnSiRezero            = "SiRezero";
 static LPCSTR fnSiGrabDevice        = "SiGrabDevice";
 static LPCSTR fnSiReleaseDevice     = "SiReleaseDevice";
 static LPCSTR fnSiButtonPressed     = "SiButtonPressed";
 static LPCSTR fnSiButtonReleased    = "SiButtonReleased";
 static LPCSTR fnSiSetUIMode         = "SiSetUiMode";
 static LPCSTR fnSiGetDevicePort     = "SiGetDevicePort";
 static LPCSTR fnSiGetDriverInfo     = "SiGetDriverInfo";
 static LPCSTR fnSiGetLibraryInfo    = "SiGetLibraryInfo";
 static LPCSTR fnSiGetDeviceInfo     = "SiGetDeviceInfo";
 static LPCSTR fnSpwErrorString      = "SpwErrorString";

*/

/* DLL handle */
// VARIABLES GLOBALS
HINSTANCE ghDll;
enum SpwRetVal SpwErrorVal;
SiOpenData * siopendata;
HWND hwnd_owner;
#ifdef _DEBUG
	FILE * log_file=NULL;
#endif


////////////////////////////////////////////////////////////////////
enum SpwRetVal _stdcall SiInitialize(void);
void _stdcall SiTerminate(void);
int _stdcall SiGetNumDevices (void);
SiDevID _stdcall SiGetDeviceID (SiHdl hdl);
SiDevID _stdcall SiDeviceIndex (int idx);
int _stdcall SiDispatch (SiHdl hdl, SiGetEventData *pData,SiSpwEvent *pEvent, SiSpwHandlers *pDHandlers);
void _stdcall SiOpenWinInit (SiOpenData *pData, HWND hWnd);
SiHdl _stdcall SiOpen (char *pAppName, SiDevID devID, SiTypeMask *pTMask, int mode,SiOpenData *pData);
enum  SpwRetVal _stdcall _SiClose (SiHdl hdl);
SPWbool _stdcall SiIsSpaceWareEvent(SiGetEventData *pData, SiHdl *pHdl);
void _stdcall SiGetEventWinInit (SiGetEventData *pData, UINT msg, WPARAM wParam,LPARAM lParam);
 enum SpwRetVal _stdcall SiGetEvent (SiHdl hdl, int flags, SiGetEventData *pData, SiSpwEvent *pEvent);
 enum SpwRetVal _stdcall SiBeep(SiHdl hdl, char *pString);
 enum SpwRetVal _stdcall SiRezero (SiHdl hdl);
 enum SpwRetVal _stdcall SiGrabDevice (SiHdl hdl, SPWbool exclusive);
 enum SpwRetVal _stdcall SiReleaseDevice (SiHdl hdl);
 int _stdcall SiButtonPressed (SiSpwEvent *pEvent);
 int _stdcall SiButtonReleased (SiSpwEvent *pEvent);
 enum  SpwRetVal _stdcall SiSetUiMode (SiHdl hdl, SPWuint32 mode);
 enum  SpwRetVal _stdcall SiSetTypeMask (SiTypeMask *pTMask, int type1, ...);
 enum  SpwRetVal _stdcall SiGetDevicePort (SiDevID devID, SiDevPort *pPort);
 enum  SpwRetVal _stdcall SiGetDriverInfo (SiVerInfo *pInfo);
 void  _stdcall SiGetLibraryInfo  (SiVerInfo *pInfo);
 enum  SpwRetVal _stdcall SiGetDeviceInfo (SiHdl hdl, SiDevInfo *pInfo);
 char * _stdcall SpwErrorString (enum SpwRetVal val);
// per escriure al buffer
#ifdef _DEBUG
	void LogBuffer(char buffer[255]);
#endif
///////////////////////////////////////////////////
// END METHODS
///////////////////////////////////////////////////
extern  int nSiappdll;

 int fnSiappdll(void);

class Chandling
{
public:
	Chandling();
	int a;
};

#endif // ifndef SIAPP_DLL_LIB