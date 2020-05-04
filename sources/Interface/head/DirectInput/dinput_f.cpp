#include "dinput_f.h"
#include "../CBDades.h"
//CDirectInput		* interficie[MAX_DEVICES];

extern CBDades  dbase;

/////////////////////////////////////////////////////////// 
//  Classe Device_Sector -> dades sobre dispositius      //
///////////////////////////////////////////////////////////
// CONSTRUCTOR
	Device_Selector::Device_Selector(HWND hwnd, HINSTANCE hinstance)
	{
		int i;
		this->hinstance = hinstance;
		this->hwnd = hwnd;
		hr = DirectInput8Create(hinstance, DIRECTINPUT_VERSION, IID_IDirectInput8,(void**)&lpdi, NULL);
		if (hr == DIERR_OLDDIRECTINPUTVERSION) {
			MessageBox(NULL, "Necessita una versió més actualitzada de DirectInput.", "nfo", MB_OK|MB_ICONINFORMATION);
		}
		if (FAILED(hr)) {			
			MessageBox(NULL, "Problema amb la creació en DeviceSelector::DeviceSelector.", "nfo", MB_OK|MB_ICONASTERISK);
		}
/*		posy = 50;
		tmp = 1;*/
		enumerats=0;
		
		for (i = 0; i < MAX_DEVICES; i++)
		{
			seleccionats[i] = false;
		}
	}	
	////////////////////////////////////////////////////////////////////
	Device_Selector::Device_Selector()
	{
		int i;
/*		posy = 50;
		tmp = 1;*/
		enumerats=0;
		
		for (i = 0; i < MAX_DEVICES; i++)
		{
			seleccionats[i] = false;
		}

	}
	////////////////////////////////////////////////////////////////////
	void Device_Selector::NouDispositiu(LPCDIDEVICEINSTANCE lpddi)
	{	
		
		guid_list[enumerats] = lpddi->guidInstance;
		if ((GET_DIDEVICE_TYPE(lpddi->dwDevType) ==DI8DEVTYPE_MOUSE) || (GET_DIDEVICE_TYPE(lpddi->dwDevType) ==DI8DEVTYPE_SCREENPOINTER) || (GET_DIDEVICE_TYPE(lpddi->dwDevType) ==DI8DEVCLASS_DEVICE)) {
			dtype[enumerats] = RATOLI; // assignem el tipus
			sprintf(disp_list[enumerats], "%d - %s ", enumerats , lpddi->tszProductName);
		}
		else {
			dtype[enumerats] = JOYSTICK;
			sprintf(disp_list[enumerats], "%d - %s ", enumerats , lpddi->tszProductName);
		}	

		(enumerats)++;
		
	}
	////////////////////////////////////////////////////////////////////
	void Device_Selector::EnumerarDispositius(DWORD dwDevType)
	{
		if (lpdi==NULL) MessageBox(NULL, "[WRAPPER.DLL] Device_Selector::Enumerar Dispositius no hi ha cap objecte DirectInput (NULL)", "ERROR", MB_OK| MB_ICONEXCLAMATION);
		hr = lpdi->EnumDevices(dwDevType, DIEnumDevicesCallback,	NULL, DIEDFL_ALLDEVICES | DIEDFL_ATTACHEDONLY );
		//hr = lpdi->EnumDevices(DIDEVTYPE_JOYSTICK, DIEnumDevicesCallback,	NULL, DIEDFL_ALLDEVICES | DIEDFL_ATTACHEDONLY );
		if (FAILED(hr)) 
		{
			MessageBox(NULL, "Enum Devices Fallada!", "nfo", MB_OK|MB_ICONINFORMATION);
			
		}

	}

	////////////////////////////////////////////////////////////////////
	GUID Device_Selector::RetornarGUID(int i)
	{
		return(GUID_SysMouse);	
	}
	// DESTRUCTOR
	////////////////////////////////////////////////////////////////////
	Device_Selector::~Device_Selector() 
	{
		if (lpdi)
		{
			lpdi->Release();
		}
	}
////////////////////////////////////////////////////////////////
// FUNCIÓ GLOBAL PER GENERAR EL CALLBACK de enumeració        //
////////////////////////////////////////////////////////////////
	BOOL CALLBACK DIEnumDevicesCallback(LPCDIDEVICEINSTANCE lpddi, LPVOID pvRef)
	{
		Device_Selector *ds;
		ds=dbase.GetSelector();
		if (ds ==NULL) {
			MessageBox(NULL, "Device Selector NULL!!", "DiEnumDevicesCallBack", MB_OK|MB_ICONASTERISK);
			return (DIENUM_STOP);
		}
		ds->NouDispositiu(lpddi);	
		return(DIENUM_CONTINUE); // o DIENUM_STOP per parar
	}

///////////////////////////////////////////////////////////// 
// funcions per a llistar els botons i eixos d'un dispositiu //
/////////////////////////////////////////////////////////////

BOOL CALLBACK DIEnumDeviceComponentsCallback(LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef)
{
	CDirectInput * tmp; 
	tmp = (CDirectInput * ) pvRef;
	//tmp = (CDirectInput)pvRef;
	if (lpddoi->guidType == GUID_Button) {		
		tmp->MoreButtons(); // un botó més
		
	}
	else {
		tmp->MoreAxis(lpddoi->guidType);  // un eix més
		
	}
	return(DIENUM_CONTINUE);
}


