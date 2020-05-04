#include "Window_Handles.h"
#include "CBDades.h" // class header file
#include <stdlib.h>


////////////////////////////////////////////////////////////////
CBDades::CBDades(void)
{
//	pCua_events=new Queue();
	cf = new CFilterDI(20);
//	theWindow_Handles = new Window_Handles();
}
////////////////////////////////////////////////////////////////
CBDades::~CBDades()
{
}
////////////////////////////////////////////////////////////////
/*bool CBDades::NouEvent(Event * pEvent) 
{
	if (pCua_events==NULL)
	{
		MessageBox(NULL, "Cua d'events no inicialitzada a CBDades::NouEvent", "Error", MB_OK);
		return false;		
	}
	pCua_events->Add(pEvent);		
		return true; 
}
////////////////////////////////////////////////////////////////
Event * CBDades::RecollirEvent() 
{
	Event * e = new Event();

	return e;
}*/
////////////////////////////////////////////////////////////////
Devinfo * CBDades::GetDevInfo() 
{
	return(&devinfo);
}
////////////////////////////////////////////////////////////////
CConfiguration * CBDades::GetDevConfig() 
{
	return (&config);
}
////////////////////////////////////////////////////////////////
bool CBDades::NovaConfig(Devinfo * pDevInfo, CConfiguration * pFiltersConfig) 
{


	// device information (només guarda informació sobre el seleccionat)
	ZeroMemory( &devinfo, sizeof(devinfo));
	strcpy(devinfo.bios, pDevInfo->bios);	
	devinfo.botons=pDevInfo->botons;
	devinfo.can_beep=pDevInfo->can_beep;
	devinfo.eixos = pDevInfo->eixos;
	devinfo.major = pDevInfo->major;
	devinfo.minor = pDevInfo->minor;
	devinfo.model = pDevInfo->model; // 18=personalitzat

	// general
	config.sensibilitat = pFiltersConfig->sensibilitat;
	// individual axis
	config.beep_act=pFiltersConfig->beep_act;
	config.hFilt_eixdominant=pFiltersConfig->hFilt_eixdominant;
	config.hRotacions=pFiltersConfig->hRotacions;
	config.hTraslacions=pFiltersConfig->hTraslacions;
	config.rx=pFiltersConfig->rx;
	config.ry=pFiltersConfig->ry;
	config.rz=pFiltersConfig->rz;
	config.tx=pFiltersConfig->tx;
	config.ty=pFiltersConfig->ty;
	config.tz=pFiltersConfig->tz;
	config.y_z_int=pFiltersConfig->y_z_int;
	// advanced config
	config.panoramitzar=pFiltersConfig->panoramitzar;
	config.rotacions = pFiltersConfig->rotacions;
	config.zooming = pFiltersConfig->zooming;
	
	/*config.theAsignBotons.SetList(pFiltersConfig->theAsignBotons.GetList(), pFiltersConfig->theAsignBotons.GetCount());
	config.theAsignEixos.SetList(pFiltersConfig->theAsignEixos.GetList(), pFiltersConfig->theAsignEixos.GetCount());
	config.theAsignEspecials.SetList(pFiltersConfig->theAsignEspecials.GetList(), pFiltersConfig->theAsignEspecials.GetCount());*/
	
	return true;
}
////////////////////////////////////////////////////////////////
CDirectInput ** CBDades::GetDI(void)
{
	return (pCDirectInput);
}
////////////////////////////////////////////////////////////////
Device_Selector * CBDades::GetSelector()
{
	return (theDevice_Selector);
}
////////////////////////////////////////////////////////////////
Window_Handles * CBDades::GetWindowHandles()
{
	return(&theWindow_Handles);
}
////////////////////////////////////////////////////////////////
CFilterDI * CBDades::GetCFilter()
{
	return (cf);
}
////////////////////////////////////////////////////////////////
void CBDades::SetSelector(Device_Selector * selector)
{
	theDevice_Selector =selector;
}
/////////////////////////////////////////////////////////////////
