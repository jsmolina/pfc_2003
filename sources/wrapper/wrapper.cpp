// wrapper.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "wrapper.h"
#include <si.h>
#include <mmsystem.h>		 // -------------------- Multimedia stuff
#include <math.h>
#include <stdlib.h>
#define SLEEP_EXE 1000/80
#define SLEEP_DLL 1000/80
#define BUT_PRESSED 1000
#define BUT_RELEASED 2000

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:			
		case DLL_THREAD_ATTACH:			
			break;
		case DLL_THREAD_DETACH:
			break;
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}
////////////////////////////////////////////////////////////////////////
bool WRAPPER_API IsInitialized()
{
	return initialized;
}
////////////////////////////////////////////////////////////////////////
void WRAPPER_API Initialize()
{
	initialized = true;	


}

void WRAPPER_API Terminate()
{
	initialized = false;	


}

////////////////////////////////////////////////////////////////////////
void WRAPPER_API ExeInit()
{
	exe_init			=true;
	fdone_registerapp	=false;
	fmod_registerapp	=false;
	///////////////////////////////

#ifdef _DEBUG
		flog = fopen("LOG_WRAP-MFC.txt", "a+");
		LogBuffer("[wrapper] MFC Application Registered\r\n\0");
#endif
}
////////////////////////////////////////////////////////////////////////
bool  CDSetMode(bool veure_interficie)
{
	return true;
}
////////////////////////////////////////////////////////////////////////
int   CDOpen(bool polling)
{
	return 1;
}
////////////////////////////////////////////////////////////////////////
bool WRAPPER_API CDClose(HWND h)
{
	// haurà de poder desregistrar una finestra
	
	return (CDTerminate(h));
}
////////////////////////////////////////////////////////////////////////
void  CDGetEventWinInit(SiGetEventData *pData, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// prerequisits: pData no hauria de ser NULL
	// copia el missatge a un tipus pData
    // SiGetEventWinInit(&EData, msg.message, msg.wParam, msg.lParam);
	/*
	- UINT msg;
	- WPARAM wParam;
	- LPARAM lParam;
	*/
	// retornem per pData el missatge de Windows 'comprimit'
	if (pData==NULL) pData = new SiGetEventData();
	pData->msg		= msg;
	pData->lParam	= lParam;
	pData->wParam	= wParam;
	
}
////////////////////////////////////////////////////////////////////////
enum SpwRetVal   CDGetEvent(SiGetEventData * pData, SiSpwEvent * pRetorn)
{
	// aquí puc saber si era un event de moviment o bé era	
	// de botó només consultant el pData->msg
	// i amb pData->lParam puc saber el identificador únic
	// per tal d'assegurar que no retorno un d'incorrecte
	// Només són vàlids aquells events que siguin button o motion
	// i en aquest cas es retornarà SI_IS_EVENT
	
	// descartem totes les classes d'events
	SiButtonData sib;
	
	
	if (((pData->lParam <0)&&(pData->lParam!=SI_ZERO_EVENT))|| (pData->lParam>LONG_QUEUE+1)) return SI_NOT_EVENT;	
	if (pData->wParam != WRAPPER_EVENTID) return SI_NOT_EVENT;

	if (pData->lParam == SI_ZERO_EVENT) 
	{
		pRetorn->type = SI_ZERO_EVENT;
#ifdef _DEBUG
		LogBuffer("Zero Event!\r\n");
#endif
		return SI_IS_EVENT;
	}
	if (pRetorn ==NULL) pRetorn = new SiSpwEvent();


	Event  e;
	e = PopEventById(pData->lParam);

	if (e.motion < 0) return SI_NOT_EVENT;
	
	
	switch(e.motion)
	{
//////   CASE 1 -- MOVIMENT ///////////////////////////////////////
	case 1:
#ifdef _DEBUG
			char buffer[LONG_STRING];
			sprintf(buffer, "Motion Event received ID=%d!\r\n", pData->lParam);
			LogBuffer(buffer);
#endif	
		pRetorn->type = SI_MOTION_EVENT;
		pRetorn->u.spwData.mData[SI_TX]=e.tx;
		pRetorn->u.spwData.mData[SI_TY]=e.ty;
		pRetorn->u.spwData.mData[SI_TZ]=e.tz;
		pRetorn->u.spwData.mData[SI_RX]=e.rx;
		pRetorn->u.spwData.mData[SI_RY]=e.ry;
		pRetorn->u.spwData.mData[SI_RZ]=e.rz;
		
		if (e.tx==0 && e.ty==0 && e.tz==0 && e.rx==0 && e.ry==0 && e.rz==0)
		{
#ifdef _DEBUG
				fprintf(stderr, "CAN'T POP=%d ID=%d\r\n", e.motion, e.id);			
#endif
		}
		pRetorn->u.spwData.period = abs(lasttime - timeGetTime());
		lasttime=timeGetTime();
	break;
//////   CASE 2 -- PUSH ///////////////////////////////////////
	case 2:
#ifdef _DEBUG
			LogBuffer("Button PUSH Event received!\r\n");		
#endif
		if (e.id==-1) 
		{
#ifdef _DEBUG
				LogBuffer("Button Event refused\r\n");
#endif
			return SI_NOT_EVENT;
		}
		
#ifdef _DEBUG
		sprintf(buffer, "[wrp]BUTTON POP=%d ID=%d B=%d\r\n", e.motion, e.id, e.boto);
		LogBuffer(buffer);
#endif
		pRetorn->type = SI_BUTTON_EVENT;
		// falta controlar el darrer botó, i quan s'allibera!!
		
		sib.last = lastbutton;	
		sib.current=e.boto;
		sib.pressed=BUT_PRESSED;
		lastbutton=e.boto;

		pRetorn->u.spwData.bData=sib;
		pRetorn->u.spwData.period = abs(lasttime - timeGetTime());
		lasttime=timeGetTime();

	break;
//////   CASE 3 -- RELEASE////////////////////////////
	case 3:
		#ifdef _DEBUG
			LogBuffer("Button PUSH Event received!\r\n");		
#endif

		if (e.id==-1) 
		{
#ifdef _DEBUG
				LogBuffer("Button Event refused\r\n");
#endif
			return SI_NOT_EVENT;
		}
		
#ifdef _DEBUG
		sprintf(buffer, "[wrp]BUTTON POP=%d ID=%d B=%d\r\n", e.motion, e.id, e.boto);
		LogBuffer(buffer);
#endif
		pRetorn->type = SI_BUTTON_EVENT;
		// falta controlar el darrer botó, i quan s'allibera!!
		
		sib.last = lastbutton;	
		sib.current=e.boto;
		sib.pressed=BUT_RELEASED;
		lastbutton=e.boto;

		pRetorn->u.spwData.bData=sib;
		pRetorn->u.spwData.period = abs(lasttime - timeGetTime());
		lasttime=timeGetTime();
		
	break;

	}
	/* Descripció de  SiButtonData
				- unsigned long last
					Dona el anterior botó alliberat. Per al botó 1, he 	obtingut resultats empírics de 2 (10b), per al botó 2,	he obtingut valors de 4 (100b).
				- unsigned long current					
					Dona el actual botó pitjat.
				- unsigned long pressed
					Dona el actual botó pitjat.
				- unsigned long released
					Dona el botó alliberat.
		*/

	/*   Descripció de SiSpwEvent * pRetorn
		- int type
		-  SiSpwData spwData
		   On s'especifiquen les dades esperades (SiSpwData):
	    union {	
		- SiButtonData bData
			No cal en aquest cas.		
		- long mData[6] (on el índex va des de SI_TX, a SI_RZ)
		- unsigned long period
		On s'especifica el període en milisegons. En proves, he obtingut un període de 48-50 ms.
		}u;
	*/
	//retornem que sí és un event


	return SI_IS_EVENT;
}
////////////////////////////////////////////////////////////////////////
bool  CDSendMessage()
{
	return true;
}
////////////////////////////////////////////////////////////////////////
SiDevInfo *  CDGetVirtualDeviceInfo()
{
	SiDevInfo * cdinfo;
	cdinfo=new SiDevInfo();
	cdinfo->canBeep =dcan_beep;
	cdinfo->devType =dmodel;
	strcpy(cdinfo->firmware, dbios);
	cdinfo->majorVersion=dmajor;
	cdinfo->minorVersion=dminor;
	cdinfo->numButtons  =dbotons;
	cdinfo->numDegrees  =deixos;
	return (cdinfo);
}

SiVerInfo * CDGetVirtualLibraryInfo()
{
	SiVerInfo * cdinfo;
	cdinfo = new SiVerInfo();
	
	sprintf(cdinfo->date, "September 6, 2001");
	cdinfo->major = dllmajor;
	cdinfo->minor = dllminor;
	cdinfo->build = 0;
	sprintf(cdinfo->version, "SpaceWare Library");

	return cdinfo;
}
//////////////////////////////////////////////////////////////////
SiDevPort * CDGetVirtualDevicePort()
{
   SiDevPort * pPort = new SiDevPort();

#ifdef _DEBUG
	LogBuffer("CDGetVirtualDevicePort called");
#endif
   pPort->devID=1;
   pPort->devType=SI_ALL_TYPES;
   pPort->devType=dmodel;
   pPort->devClass=SI_HIGH_END;
	sprintf(pPort->devName, "%s", dmodel_str);
	sprintf(pPort->portName, "PS/2\0");
return(pPort);
}
////////////////////////////////////////////////////////////////////////
bool  CDInitialize()
{
#ifdef _DEBUG
		flog = fopen("LOG_SIAPP-WRAP.txt", "a+");
#endif
	return true;
}
////////////////////////////////////////////////////////////////////////
bool  CDTerminate(HWND h)
{
	// TODO: Dir al EXE que n'hi ha una desregistrada
	while (fblock_ureg==true){
		Sleep(SLEEP_DLL);
	}
	fblock_ureg=true;
	unregister_hwnd = h;	
	fdone_unregisterapp=false;
	fmod_unregisterapp=true;
	fblock_ureg=false;

 return true;
}
////////////////////////////////////////////////////////////////////////
bool  CDOpenWinInit(HWND hwnd)
{
	char * buffer;
	int len;
	HWND hWnd;
	/*int GetClassName(HWND hWnd,LPTSTR lpClassName,	// address of buffer for class name
    int nMaxCount 	// size of buffer, in characters
   );*/
	hWnd = GetForegroundWindow();
	len =  GetWindowTextLength(hwnd)+1;
	buffer = new char[len];
	GetWindowText(hwnd, buffer, len);


	while (fblock_reg==true){
		Sleep(SLEEP_DLL);
	}
	fblock_reg=true;
	registered_hwnd = hwnd;	
	strcpy(registered_exe, buffer);
	fdone_registerapp=false;	
	fmod_registerapp=true;
	fblock_reg=false;
	delete buffer;
 return true;
}

bool  IsNewRegister()
{
	// nou registre?
	return fmod_registerapp;
}

bool IsNewUnRegister()
{
	return fmod_unregisterapp;
}
/*
App_Register * GetApp()
{
	while(fblock_reg==true) Sleep(SLEEP_EXE);
	App_Register *app = new App_Register();
	strcpy(app->registered_exe, registered_exe);
	//app->registered_hwnd = registered_hwnd;
	memcpy(app->registered_hwnd, registered_hwnd, sizeof(HWND));
		char buf[255];
		sprintf(buf, "reg_hwnd=%x  registered_exe=%s", registered_hwnd, registered_exe);
		LogBuffer(buf);
	fdone_registerapp=true;
	fmod_registerapp =false;
	return app;
}
*/
HWND  GetApp()
{	
	while(fblock_reg==true) Sleep(SLEEP_EXE);
#ifdef _DEBUG
		char buf[255];
		sprintf(buf, "reg_hwnd=%x", registered_hwnd);
		LogBuffer(buf);
#endif
	fdone_registerapp=true;
	fmod_registerapp =false;
	return registered_hwnd;
}

/*
App_Register  GetUnApp()
{
	App_Register app;	
	sprintf(app.registered_exe, "");
	app.registered_hwnd = unregister_hwnd;
	fblock_ureg=false;
	fdone_unregisterapp=true;
	fmod_unregisterapp =false;	
	return app;
}
*/

HWND  GetUnApp()
{	
	while(fblock_reg==true) Sleep(SLEEP_EXE);
#ifdef _DEBUG
		char buf[255];
		sprintf(buf, "unreg_hwnd=%x", unregister_hwnd);
		LogBuffer(buf);
#endif
	fdone_unregisterapp=true;
	fmod_unregisterapp =false;	
	return unregister_hwnd;
}
////////////////////////////////////////////////////////////////////////
int CDButtonPressed (SiSpwEvent *pEvent)
{
	if (initialized==false) DispatchNotLoadedError();
#ifdef _DEBUG
		char buf[LONG_STRING];
		sprintf(buf, "Pressed=%d", pEvent->u.spwData.bData.last);
		LogBuffer(buf);
#endif
	if (pEvent->u.spwData.bData.pressed!=BUT_PRESSED)  {
		return SI_NO_BUTTON;
	}
	else {
		return (pEvent->u.spwData.bData.current);
	}	
}
////////////////////////////////////////////////////////////////////////
int CDButtonReleased (SiSpwEvent *pEvent)
{
	if (initialized==false) DispatchNotLoadedError();

#ifdef _DEBUG
		char buf[LONG_STRING];
		sprintf(buf, "Released=%d", pEvent->u.spwData.bData.last);
		LogBuffer(buf);
#endif

	if (pEvent->u.spwData.bData.pressed!=BUT_RELEASED)  {
		return SI_NO_BUTTON;
	}
	else {
		return (pEvent->u.spwData.bData.current);
	}
}

////////////////////////////////////////////////////////////////////////
//////////////////////QUEUE FUNCTIONS///////////////////////////////////
////////////////////////////////////////////////////////////////////////
void   PushEvent(Event *e)
{	
// TEMPORAL: No n'hi ha exclusió mútua
while(fblock_queue==true) Sleep(SLEEP_EXE);

	if (e->tx==0 && e->ty==0 && e->tz==0 && e->rx==0 && e->ry==0 && e->rz==0 && e->boto==-1)
	{	
#ifdef _DEBUG
			LogBuffer("**ERROR** All zero EVENT!!");		
#endif
	}
#ifdef _DEBUG
		char buffer[LONG_STRING];
		sprintf(buffer, "PUSHING- MOTION=%d IDPOS=%d\r\n", e->motion, e->id); 
		LogBuffer(buffer);
#endif
	//fprintf(stderr, "PUSHING- MOTION=%d IDPOS=%d\r\n", e->motion, e->id);
	if (e->id > LONG_QUEUE)
	{
#ifdef _DEBUG
			LogBuffer("**ERROR**  Invalid identificator for the event.");
#endif
	}
// si està ple
#ifdef _DEBUG
		if (eopened[e->id]==true) LogBuffer("Event already used, error Pushing\r\n");
#endif
	fblock_queue=true;
	eboto[e->id]   = e->boto;
	ehwnd[e->id] =e->hwnd;
	eid[e->id] =e->id;
	emotion[e->id] =e->motion;
	erx[e->id] =e->rx;
	ery[e->id] =e->ry;
	erz[e->id] =e->rz;
	etx[e->id] =e->tx;
	ety[e->id] =e->ty;
	etz[e->id] =e->tz;	
	eopened[e->id]  = true;
	fblock_queue=false;

		
}


Event  PopEventById(long ident)
{

	Event  e;
#ifdef _DEBUG
		char buf[LONG_STRING];
#endif
	
	if (ident>LONG_QUEUE) 
	{
#ifdef _DEBUG
			sprintf(buf, "Identificator %d exceeds LONG_QUEUE, contact programmer\r\n", ident);
			LogBuffer(buf);
#endif
		e.id=-1;
		return e;
	}
#ifdef _DEBUG
	if (eopened[ident]==false) 
	{		
		
			sprintf(buf, "This event was token before, or was not pushed ID=%d\r\n", ident);
			LogBuffer(buf);	
	}
#endif

	e.boto		=eboto[ident];
	e.hwnd		=ehwnd[ident];		
	e.motion	=emotion[ident];
	e.rx		=erx[ident];
	e.ry		=ery[ident];
	e.rz		=erz[ident];
	e.tx		=etx[ident];
	e.ty		=ety[ident];
	e.tz		=etz[ident];
	eopened[ident]  = false; // marquem l'event com utilitzat
	return e;
	
	
}

////////////////////////////////////////////////////////////////////////
void ChangeConfig(Devinfo * d)
{	

	strcpy(dbios, d->bios);
	strcpy(dmodel_str, d->model_str);
	dbotons   =	  d->botons;
	dcan_beep =   d->can_beep;
	deixos    =   d->eixos;
	dmajor    =   d->major;
	dminor    =   d->minor;
	dmodel    =   d->model;
	dllmajor  =   d->dll_major;
	dllminor  =   d->dll_minor;
}
////////////////////////////////////////////////////////////////////////
////////// LOGGING //////////////
#ifdef _DEBUG
void LogBuffer(char buf[LONG_STRING])
{

	if (flog!=NULL) fprintf(flog, buf);
	fprintf( stderr, buf);
}
#endif
////////// END OF LOGGING //////////////
////////////////////////////////////////////////////////////////////////
void DispatchNotLoadedError()
{
	MessageBox(NULL, "ConfigDriver not loaded, please load before 3dware applications.\nApplication will close now.", "Warning", MB_OK|MB_ICONEXCLAMATION);
#ifdef _DEBUG
	LogBuffer("ConfigDriver not loaded, please load before 3dware applications.\nApplication will close now.");
#endif
	PostQuitMessage(1);
}


//bool WRAPPER_API CDOpenWinInit(HWND hwnd, void (*pFn)(CBDades * bd))