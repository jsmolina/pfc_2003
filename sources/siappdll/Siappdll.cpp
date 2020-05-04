// Siappdll.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#define SPW_DEFINE_COPYRIGHT
#define SPW_DEFINE_GLOBALS

#include "Siappdll.h"
#include "exports.h"
#include <Windows.h>

bool unload=false;
//static CSiappwrap * pCSiappwrap;
static enum InitResult gInitStatus = NOT_LOADED;

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			ghDll = (HINSTANCE ) hModule;
			// TODO: Add extra initialization here
			if(IsInitialized()) 
			{
				//MessageBox(NULL,"[SiappDLL] Driver ja carregat", "Configuració de dispositiu", MB_OK);
				// JSM
				//Initialize();
				SiBeep(0, NULL);
			}
			else 
			{
				MessageBox(NULL, "[SiappDLL] Driver must be loaded before any 3dware compatible application....", "[SiappDLL]", MB_OK);
				unload=true;
			}
			
		break;

		case DLL_THREAD_ATTACH:
			break;
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
// sembla que si no està aquí, al process_detach no surt (curiosament)
#ifdef _DEBUG
		LogBuffer("Process Detach, Unregistering Application\r\n");
		if (log_file!=NULL) fclose(log_file);
#endif
		CDTerminate(hwnd_owner);
    }
    return TRUE;
}

// This is the constructor of a class that has been exported.
// see Siappdll.h for the class definition



//////////////////////////////////////////////////////////////////////
/////////////////////// CODI DE FUNCIONS 3DWARE //////////////////////
//////////////////////////////////////////////////////////////////////
enum SpwRetVal _stdcall SiInitialize(void)
{
  // Inicialitza la DLL per utilitzar les funcions
#ifdef _DEBUG
	LogBuffer("SiInitialize called, calling wrapper (no parameters)...\r\n");
#endif

	if ( CDInitialize()) return SPW_NO_ERROR;
	else return SPW_ERROR;
}
////////////////////////////////////////////////////////////////////////
void _stdcall SiTerminate(void)
{
	// Cridada quan es vol tancar la DLL
#ifdef _DEBUG	
	LogBuffer("SiTerminate called (no parameters)...\r\n");
#endif
   //FreeLibrary(ghDll);
//	PostQuitMessage(0);

   gInitStatus = NOT_LOADED;
}
////////////////////////////////////////////////////////////////////////
int _stdcall SiGetNumDevices (void)
{
   /* Retorna el número de dispositius de tipus spaceware
	  en el meu cas, no té sentit emular més d'un a la vegada
   */
	int tmpRetVal;
#ifdef _DEBUG
	char buffer[1024];
	sprintf(buffer, "SiGetNumDevices called, returns 1 always\r\n");
	LogBuffer(buffer);
#endif

   tmpRetVal = 1;
   SpwErrorVal = SPW_NO_ERROR;
   return tmpRetVal;
}
////////////////////////////////////////////////////////////////////////
SiDevID _stdcall SiGetDeviceID (SiHdl hdl)
{
   SiDevID tmpRetVal;  /* temporary return value */
/* Obté un identificador de dispositiu, només útil quan 
   n'hi ha més d'un dispositiu SpaceMouse.
   */

#ifdef _DEBUG
   LogBuffer("--> SiGetDeviceID\r\n");
	char buffer[1024];
	sprintf(buffer, "SiGetDeviceID called, hdl=%x, returns 1 always.\r\n", hdl);
   	LogBuffer(buffer);
#endif
   tmpRetVal = 1;
   SpwErrorVal = SPW_NO_ERROR;
   return tmpRetVal;
}
////////////////////////////////////////////////////////////////////////
 SiDevID _stdcall SiDeviceIndex (int idx)
{
   SiDevID tmpRetVal;  /* temporary return value */
	
/* Retorna el número del dispositiu, donat un índex
   */
#ifdef _DEBUG
   LogBuffer("--> SiGetDeviceIndex\r\n");
   char buffer[1024];
   sprintf(buffer, "SiDeviceIndex called  idx=%d\r\n", idx);
   LogBuffer(buffer);
#endif

   tmpRetVal = 1;
   SpwErrorVal = SPW_NO_ERROR;
   return tmpRetVal;
}
////////////////////////////////////////////////////////////////////////
int _stdcall	SiDispatch (SiHdl hdl, SiGetEventData *pData,
                SiSpwEvent *pEvent, SiSpwHandlers *pDHandlers)
{
   int tmpRetVal;  /* temporary return value */

   /*
   Amb companyia de SiGetEvent, aquesta funció crida 
   el handler apropiat per processar el event retornat 
   per SiGetEvent a la manera per defecte.     
   */
    // no cridaré al wrapper des d'aquesta funció, donat que l'únic
   // que cal fer és cridar una funció interna del programa que fa 
   // servir aquesta llibreria
#ifdef _DEBUG
   LogBuffer("--> SiDispatch\r\n");
   char buffer[1024];
   sprintf(buffer, "SiDispatch called (hdl=%x, pData, pEvent, pDHandlers)\r\n", hdl);
   LogBuffer(buffer);
#endif

   SiEventHandler * eventhandler=NULL; // punter als event handler
	// l'event no pot existir, si pData==NULL	
   if (pData == NULL) return 0; 
	if (pEvent==NULL) return 0;
	// pEvent->spwData enviar al callback	
	switch(pEvent->type)
	{
	case SI_BUTTON_EVENT:
		if (siopendata==NULL) MessageBox(NULL, "OpenData NULL", "SiDispatch", MB_OK);
		eventhandler = &(pDHandlers->button);
		if (eventhandler->func==NULL) MessageBox(NULL, "Callback func NULL", "SiDispatch", MB_OK);
		tmpRetVal=eventhandler->func(siopendata, pData, pEvent, eventhandler->data);
#ifdef _DEBUG
		LogBuffer("Enviat un event de boto al callback");
#endif
	break;

	case SI_MOTION_EVENT:
		if (siopendata==NULL) MessageBox(NULL, "OpenData NULL", "SiDispatch", MB_OK);
		eventhandler = &(pDHandlers->motion);
		if (eventhandler->func==NULL) MessageBox(NULL, "Callback func NULL", "SiDispatch", MB_OK);
		tmpRetVal=eventhandler->func(siopendata, pData, pEvent, eventhandler->data);
#ifdef _DEBUG
		LogBuffer("Enviat un event de moviment al callback");
#endif
	break;

	case SI_ZERO_EVENT:
		if (siopendata==NULL) MessageBox(NULL, "OpenData NULL", "SiDispatch", MB_OK);
		eventhandler = &(pDHandlers->zero);
		if (eventhandler->func==NULL) MessageBox(NULL, "Callback func NULL", "SiDispatch", MB_OK);
		tmpRetVal=eventhandler->func(siopendata, pData, pEvent, eventhandler->data);
#ifdef _DEBUG
		LogBuffer("Enviat un event de zero al callback");
#endif
	break;
	}
	
	/* Estructura SiOpenData;
		   HWND hWnd;               
		   SiTransCtl transCtl;
		   DWORD processID;
		   char exeFile[MAX_PATH];
		   SPWint32 libFlag;    
	*/

   
   SpwErrorVal = SPW_NO_ERROR;
   return tmpRetVal;
}
////////////////////////////////////////////////////////////////////////
void _stdcall
	SiOpenWinInit (SiOpenData *pData, HWND hWnd)
{
	/*
	Funció específica de windows de la DLL SpaceMouse, i el que
	fa és rebre un handle a la finestra que està utilitzant
	la DLL, de tal manera que es poden fer els SendMessage a la
	finestra concreta.
	*/
	//GW_HWNDNEXT
HWND hwnd_real = GetForegroundWindow();

#ifdef _DEBUG	
	char filename[2048];
	char clname1[255];
	char clname2[255];
	
	sprintf(filename, "Log%x.txt", hWnd);
	log_file = fopen(filename, "a+");	
	LogBuffer("--> SiOpenWinInit\r\n");
	GetClassName(hWnd, clname1, 255);
	GetClassName(hwnd_real, clname2, 255);
	sprintf(filename, "SiOpenWinInit called. hWnd=%x GetFore=%x GetClassNameh=%s GetClassNameFore=%s\r\n", hWnd, hwnd_real, clname1, clname2);
	LogBuffer(filename);	
#endif
	
	// guarda la finestra que controla
	hwnd_owner=hWnd;
	CDOpenWinInit(hWnd);
	
   SpwErrorVal = SPW_NO_ERROR;
}
////////////////////////////////////////////////////////////////////////
SiHdl _stdcall SiOpen (char *pAppName, SiDevID devID, SiTypeMask *pTMask, int mode, 
              SiOpenData *pData)
{
   /* Es fa servir per a poder capturar un dispositiu, donada una
	aplicació, i donats un flags que encara no estàn suportats*/
#ifdef _DEBUG
	LogBuffer("--> SiOpen\r\n");
   char buffer[1024];
   HWND hwnd;
   DWORD procid;
   DWORD procid2;
   hwnd=GetForegroundWindow();
   GetWindowThreadProcessId(hwnd, &procid);
   GetWindowThreadProcessId(pData->hWnd, &procid2);
   sprintf(buffer, "SiOpen called. devID=%d  mode=%d  pData->processID=%x  pData->hWnd=%x GetForeProcID=%x  GetProcessIDhwnd=%x\r\n",  devID, mode, pData->processID, pData->hWnd, procid, procid2);
   LogBuffer(buffer);
#endif
	siopendata = pData; // openData gravada
	SiHdl tmpRetVal;  /* temporary return value */
	Chandling * ch = new Chandling();
   if (unload==true) PostQuitMessage(0);
   tmpRetVal = (Chandling *) ch; 
   SpwErrorVal = SPW_NO_ERROR;
   return tmpRetVal;

}
////////////////////////////////////////////////////////////////////////
enum SpwRetVal _stdcall SiClose (SiHdl hdl)
{
   enum SpwRetVal tmpRetVal;  /* temporary return value */

	/* si es tanca el dispositiu, vol dir que no es volen rebre
       més missatges del dispositiu 3d */
#ifdef _DEBUG
   LogBuffer("--> SiClose\r\n");
    char buffer[1024];
	sprintf(buffer, "SiClose called hdl=%x calling wrapper\r\n", hdl);
   	LogBuffer(buffer);
#endif
   CDClose(hwnd_owner);
   tmpRetVal = SPW_NO_ERROR;
   SpwErrorVal = SPW_NO_ERROR;
   return tmpRetVal;

}
////////////////////////////////////////////////////////////////////////
SPWbool _stdcall SiIsSpaceWareEvent(SiGetEventData *pData, SiHdl *pHdl)
{
	/*
		Si un programa comprova si un event és SpaceWare, retornarà true
		sempre que el missatge contingui un tipus vàlid, o bé que
		el seu identificador sigui major a zero, donat que és un
		pre-requisit.
	*/
#ifdef _DEBUG
	LogBuffer("--> SiIsSpaceWareEvent\r\n");
	char buffer[1024];
	sprintf(buffer, "SiIsSpaceWareEvent called pData->lParam=%d  pData->wParam  pData->msg  pHdl=%x\r\n",pData->lParam, pData->msg, *pHdl);
	LogBuffer(buffer);
#endif
	if (pData->lParam == SI_ZERO_EVENT) return SPW_TRUE;
	if (pData->lParam>-1) {		
		if (pData->wParam==WRAPPER_EVENTID) return SPW_TRUE;		
	}
   
   SpwErrorVal = SPW_NO_ERROR;
   return SPW_FALSE;
}
////////////////////////////////////////////////////////////////////////
void  _stdcall SiGetEventWinInit (SiGetEventData *pData, UINT msg, WPARAM wParam, 
                   LPARAM lParam)
{	
	/*
	Aquesta funció és tan senzilla com copiar el missatge de windows
	a una estructura tipus pData, però cridaré al wrapper per si alguna
	vegada volgués fer una tasca més complicada.
	*/
#ifdef _DEBUG
	LogBuffer("--> SiGetEventWinInit\r\n");
	char buffer[1024];
	sprintf(buffer, "SiGetEventWinInit called  msg=%d wParam=%d lParam=%d\r\n", msg, wParam, lParam);
  	LogBuffer(buffer);
#endif
   CDGetEventWinInit(pData, msg, wParam, lParam);
   // no pot haver cap error a la funció, retornem sempre per la 
   // variable global que no n'hi ha cap error per evitar problemes.
   SpwErrorVal = SPW_NO_ERROR;
}
////////////////////////////////////////////////////////////////////////
enum SpwRetVal _stdcall SiGetEvent (SiHdl hdl, int flags, SiGetEventData *pData, 
                           SiSpwEvent *pEvent)
{
   enum SpwRetVal tmpRetVal;  /* temporary return value */
	// no em preocupo ni del handle ni dels events

   /*
   Aquesta altra funció, grava a la pEvent el event actual, 
   incloent el tipus, i pot conèixer el tipus i el identificador 
   a través de pData
   Retorna SI_IS_EVENT quan s'ha establert que realment era un
   missatge vàlid.
   */
#ifdef _DEBUG
   LogBuffer("--> SiGetEvent\r\n");
  	char buffer[1024];
	sprintf(buffer, "SiGetEvent called  hdl=%d flags=%d pData->msg=%d  pData->lParam=%d  pData->wParam=%d pEvent és la sortida\r\n", hdl, flags, pData->msg, pData->lParam, pData->wParam);
	LogBuffer(buffer);
#endif
   tmpRetVal =  CDGetEvent(pData, pEvent);
   
   SpwErrorVal = SPW_NO_ERROR;
   return tmpRetVal;
}
////////////////////////////////////////////////////////////////////////
enum SpwRetVal _stdcall SiBeep(SiHdl hdl, char *pString)
{
	/*
	Util per avisar de la càrrega del driver, imprescindible tenir
	altaveus de l'ordinador encesos per poder escoltar la funció.
	*/
#ifdef _DEBUG	
	   LogBuffer("--> SiBeep called\r\n");
#endif
	MessageBeep(0xFFFFFFFF);	
   enum SpwRetVal tmpRetVal;  /* temporary return value */
   tmpRetVal =  SPW_NO_ERROR; 
   SpwErrorVal = SPW_NO_ERROR;
   return tmpRetVal;
}
////////////////////////////////////////////////////////////////////////
enum SpwRetVal _stdcall SiRezero (SiHdl hdl) 
{
	/*
	Funció que el que situa la zona de descans del dispositiu
	en la posició actual del mateix.
	No n'hi ha suport per aquesta funció en el meu sistema.
	*/
   enum SpwRetVal tmpRetVal;  /* temporary return value */

#ifdef _DEBUG
   LogBuffer("--> SiRezero\r\n");
   char buffer[1024];
   sprintf(buffer, "SiRezero called hdl=%d\r\n", hdl);
	   LogBuffer(buffer);
#endif

   tmpRetVal = SPW_NO_ERROR; 
   SpwErrorVal = SPW_NO_ERROR;
   return tmpRetVal;
}
////////////////////////////////////////////////////////////////////////
enum SpwRetVal _stdcall SiGrabDevice (SiHdl hdl, SPWbool exclusive)
{
	/*
	Funció que inicia la captura, i pot demanar exclusivitat sobre
	el dispositiu. Donat que tinc diferents dispositius, en 
	principi no serà implementada la seva funcionalitat.
	*/

   enum SpwRetVal tmpRetVal;  /* temporary return value */
	
#ifdef _DEBUG
   LogBuffer("--> SiGrabDevice\r\n");
   char buffer[1024];
   sprintf(buffer, "SiGrabDevice called hdl=%d  exclusive=%d\r\n", hdl, exclusive);
   LogBuffer(buffer);
#endif
	
   tmpRetVal = SPW_NO_ERROR;
   SpwErrorVal = SPW_NO_ERROR;
   return tmpRetVal;
}
////////////////////////////////////////////////////////////////////////
enum SpwRetVal _stdcall SiReleaseDevice (SiHdl hdl)
{
	/*
	Allibera el dispositiu capturat amb SiGrabDevice
	Crido directament a CDTerminate, per indicar que la finestra
	ja no vol més informació del driver.
	*/
   enum SpwRetVal tmpRetVal;  /* temporary return value */
#ifdef _DEBUG
   LogBuffer("--> SiReleaseDevice\r\n");
   char buffer[1024];
   sprintf(buffer, "SiReleaseDevice called hdl=%d\r\n", hdl);
   LogBuffer(buffer);
#endif
	CDTerminate(hwnd_owner);

   tmpRetVal = SPW_NO_ERROR;
   SpwErrorVal = SPW_NO_ERROR;
   return tmpRetVal;
}
////////////////////////////////////////////////////////////////////////
int _stdcall SiButtonPressed (SiSpwEvent *pEvent)
{
	/*
	Retorna el botó inferior pitjat durant el event actual
	*/
   int tmpRetVal;  /* temporary return value */
#ifdef _DEBUG
   LogBuffer("--> SiButtonPressed\r\n");

   char buffer[1024];
   sprintf(buffer, "SiButtonPressed called. pEvent->u.spwData.bData.last=%d   pEvent->u.spwData.bData.pressed=%d[1000->P, 2000->R]\r\n", pEvent->u.spwData.bData.last, pEvent->u.spwData.bData.pressed);
   LogBuffer(buffer);
#endif

   tmpRetVal = CDButtonPressed(pEvent);
   SpwErrorVal = SPW_NO_ERROR;
   return tmpRetVal;
}
////////////////////////////////////////////////////////////////////////

int _stdcall SiButtonReleased (SiSpwEvent *pEvent)
{
	/*
	Retorna el botó inferior alliberat durant el event actual
	*/
   int tmpRetVal;  /* temporary return value */
#ifdef _DEBUG
   LogBuffer("--> SiButtonReleased\r\n");
  char buffer[1024];
   sprintf(buffer, "SiButtonReleased called. pEvent->u.spwData.bData.last=%d   pEvent->u.spwData.bData.pressed=%d[1000->P, 2000->R]\r\n", pEvent->u.spwData.bData.last, pEvent->u.spwData.bData.pressed);
   LogBuffer(buffer);
#endif

   tmpRetVal = CDButtonReleased(pEvent);
   SpwErrorVal = SPW_NO_ERROR;
   return tmpRetVal;
}
////////////////////////////////////////////////////////////////////////
enum SpwRetVal _stdcall SiSetUiMode (SiHdl hdl, SPWuint32 mode)
{
	/*
	Actua sobre la interfície d'usuari i la pot modificar, té alguns
	flags qeu poden ser utilitzats:
	*/
	/*
    SI_UI_ALL_CONTROLS    0xffffffffL
	SI_UI_NO_CONTROLS     0x00000000L
	SI_UI_FILTERS         0x00000001L
	SI_UI_FUNC_BUTTONS    0x00000002L
	SI_UI_RESET_BUTTONS   0x00000004L
	SI_UI_SENSITIVITY     0x00000008L
	SI_UI_TUNING          0x00000010L
	SI_UI_DIALOG_POPUP    0x00000020L*/
   enum SpwRetVal tmpRetVal;  /* temporary return value */
#ifdef _DEBUG
   LogBuffer("--> SiSetUIMode\r\n");
   char buffer[1024];
	sprintf(buffer, "SiSetUiMode called\r\n");
    LogBuffer(buffer);
#endif
   
/// per ara no farà res
   
   tmpRetVal = SPW_NO_ERROR;
   SpwErrorVal = SPW_NO_ERROR ;
   return tmpRetVal;
}
////////////////////////////////////////////////////////////////////////

enum SpwRetVal _stdcall SiSetTypeMask (SiTypeMask *pTMask, int type1, ...)
{
	/*
	Funció que ara mateix no té cap ús, retornarà un valor
	que identifica que no té cap error, simplement.
	*/
#ifdef _DEBUG
	LogBuffer("--> SiSetTypeMask\r\n");
   LogBuffer("SiSetTypeMask called--> funció obsoleta mantinguda per compatibilitat\r\n");
#endif

   /* stub function -> return a happy value */
   return SPW_NO_ERROR;
}
////////////////////////////////////////////////////////////////////////
enum SpwRetVal _stdcall SiGetDevicePort (SiDevID devID, SiDevPort *pPort)
{
   enum SpwRetVal tmpRetVal;  /* temporary return value */

   /*
   Funció que retorna alguna informació sobre el dispositiu
   */
  /*SiDevID devID;             // Device ID 
   int devType;               // Device type 
   int devClass;              // Device class 
   char devName[SI_STRSIZE];  // Device name
   char portName[SI_STRSIZE]; // Port name */
#ifdef _DEBUG
   LogBuffer("--> SiGetDevicePort\r\n");
    char buffer[1024];
	sprintf(buffer, "SiGetDevicePort called  devID=%d\r\n", devID);
    LogBuffer(buffer);   
#endif
	// crida al wrapper per obtenir la informació
	// JSM ---> TODO canviar la interfície per poder canviar aquestes dades
   pPort = CDGetVirtualDevicePort();

   tmpRetVal = SPW_NO_ERROR;
   SpwErrorVal = SPW_NO_ERROR;
   return tmpRetVal;
}
////////////////////////////////////////////////////////////////////////
enum SpwRetVal _stdcall SiGetDriverInfo (SiVerInfo *pInfo)
{
   /*
   Obté informació específica del driver
   */
	enum SpwRetVal tmpRetVal;  /* temporary return value */
#ifdef _DEBUG
	LogBuffer("--> SiGetDriverInfo\r\n");
   LogBuffer("GetDriverInfo called.\r\n");
#endif
  // JSM ---> TODO canviar la interfície per poder canviar aquestes dades
   sprintf(pInfo->date, "March 24, 2003");
   pInfo->build=5;    
   pInfo->major = 3;
   pInfo->minor = 2;
   sprintf(pInfo->version, "1.0");
   
   tmpRetVal = SPW_NO_ERROR;
   SpwErrorVal = SPW_NO_ERROR;
   return tmpRetVal;
}
////////////////////////////////////////////////////////////////////////
void _stdcall SiGetLibraryInfo (SiVerInfo *pInfo)
{
  /*
  Obté la informació de la llibreria
  */
#ifdef _DEBUG	 
	LogBuffer("--> SiGetLibraryInfo\r\n");
    LogBuffer("SiGetLibraryInfo Called \r\n");
#endif
  // JSM ---> TODO canviar la interfície per poder canviar aquestes dades

	pInfo=CDGetVirtualLibraryInfo();
   
   SpwErrorVal = SPW_NO_ERROR;
}
////////////////////////////////////////////////////////////////////////
enum SpwRetVal _stdcall SiGetDeviceInfo (SiHdl hdl, SiDevInfo *pInfo)
{
	/*
	Obté informació sobre el dispositiu
	*/
   enum SpwRetVal tmpRetVal;  /* temporary return value */
#ifdef _DEBUG  
   LogBuffer("--> SiGetDeviceInfo\r\n");
   char buffer[1024];
   sprintf(buffer, "SiGetDeviceInfo Called hdl=%d\r\n ", hdl);
   LogBuffer(buffer);
#endif
   //obtenir_configuracio_del_driver_per_la_minor_major...
   pInfo = CDGetVirtualDeviceInfo();
   
   tmpRetVal = SPW_NO_ERROR;
   SpwErrorVal = SPW_NO_ERROR ;
   return tmpRetVal;
}

////////////////////////////////////////////////////////////////////////
char * _stdcall SpwErrorString (enum SpwRetVal val)
{
/*
   Retorna un string explicatiu sobre el darrer error
*/
#ifdef _DEBUG
	LogBuffer("--> SpwErrorString\r\n");
	LogBuffer("SpwErrorString Called\r\n ");
#endif
	char *buffer=new char [60];
	sprintf(buffer, "Error SiappDll, can't be more descriptive.");
  
return buffer;
}
////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
void LogBuffer(char buffer[4096])
{
	if (buffer==NULL) return;
	fprintf(stderr, buffer);
	if (log_file!=NULL)
		fprintf(log_file, buffer);	
}
#endif

 Chandling::Chandling()
 {
	 a = 0;
 }