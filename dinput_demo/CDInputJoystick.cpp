// ==============================================================
// File Name: CDInputJoystick.cpp
// 
// Model Name: Treball de fi de Carrera
// 
// Model Location: C:\Jsm\Carrera\TfiCarrera\Treball de fi de Carrera.Uml
// 
// 
// ==============================================================

#include "CDInputJoystick.h" // class header file
// Class: CDInputJoystick
// 
// Operations (Member Functions):

CDInputJoystick::CDInputJoystick(HWND hwnd2, HINSTANCE hinst2)
	: CDirectInput(hwnd2, hinst2)
{
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CDInputJoystick::ConcreteCreate(GUID id_disp, DWORD Flags) 
{ //[CDInputJoystick::ConcreteCreate]
	if(!lpdi) 
	{
		MessageBox(NULL, "DirectInput no inicialitzat  [CDInputJoystick::ConcreteCreate]", "nfo", MB_OK|MB_ICONINFORMATION);
		return false;
	}
	diDeviceInstance.dwSize = sizeof( DIDEVICEINSTANCE );
	hr=lpdidev->GetDeviceInfo( &diDeviceInstance );
	if ( FAILED(hr)) {
		MessageBox(NULL, "Error en GetDeviceInfo [CDInputJoystick::ConcreteCreate]", "nfo", MB_OK|MB_ICONEXCLAMATION);
		return(false);
	}
	if (FAILED(lpdidev->SetDataFormat( &c_dfDIJoystick2 ))) {
		MessageBox(NULL, "No es possible establir el format Joystick [CDInputJoystick::ConcreteCreate]", "nfo", MB_OK|MB_ICONEXCLAMATION);
		return(false);
	}

	if (exclusiu)	{
		if (FAILED(lpdidev->SetCooperativeLevel(hwnd, Flags))) {
			MessageBox(NULL, "No puc fer exclusiu!!", "nfo", MB_OK|MB_ICONEXCLAMATION);
			return(false);
		}
	}
	else  
	{			
		if (FAILED(lpdidev->SetCooperativeLevel(hwnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE))) {
			MessageBox(NULL, "No puc fer no exclusiu!!", "nfo", MB_OK|MB_ICONEXCLAMATION);
			return(false);
		}
	}
	if (FAILED(lpdidev->EnumObjects(DIEnumDeviceComponentsCallback, (LPVOID) this, DIDFT_AXIS | DIDFT_BUTTON))) {
		MessageBox(NULL, "No puc enumerar objectes de dispositiu (CreateDevice)!!", "nfo", MB_OK|MB_ICONEXCLAMATION);
		return(false);
	}
	if (nbotons > 0) {
		estat.b = (int*) malloc(nbotons*sizeof(int));
	}
	else  {
		MessageBox(NULL, " Actualment nbotons te un valor incorrecte", "nfo", MB_OK|MB_ICONEXCLAMATION);
		return(false);
	}
	////////////////////////////////////////////////////
	//		ESTABLIMENT DE LES DADES PEL JOYSTICK     //
	////////////////////////////////////////////////////
		DIPROPRANGE diprg; 
 
		diprg.diph.dwSize       = sizeof( diprg ); 
		diprg.diph.dwHeaderSize = sizeof( diprg.diph ); 
		diprg.diph.dwObj        = 0; 
		diprg.diph.dwHow        = DIPH_DEVICE; 
		diprg.lMin              = JOYMIN; 
		diprg.lMax              = JOYMAX; 
 
		if ( FAILED( lpdidev->SetProperty( DIPROP_RANGE, &diprg.diph ) ) )
			return (false); 

		// Set deadzone.
		DIPROPDWORD dipdw;

		dipdw.diph.dwSize       = sizeof( dipdw ); 
		dipdw.diph.dwHeaderSize = sizeof( dipdw.diph ); 
		dipdw.diph.dwObj        = 0;
		dipdw.diph.dwHow        = DIPH_DEVICE;
		dipdw.dwData            = JOYDEAD;

		if ( FAILED( lpdidev->SetProperty( DIPROP_DEADZONE, &dipdw.diph ) ) )
			return (false);

		// Set saturation.
		dipdw.dwData            = JOYSAT;
		if ( FAILED( lpdidev->SetProperty( DIPROP_SATURATION, &dipdw.diph ) ) )
			return (false);

		// Find out if force feedback available.
		DIDEVCAPS didc;
		didc.dwSize = sizeof( DIDEVCAPS );
		if ( FAILED( lpdidev->GetCapabilities( &didc ) ) ) 
			return (false);
	////////////////////////////////////////////////////
	//	FI	ESTABLIMENT DE LES DADES PEL JOYSTICK     //
	////////////////////////////////////////////////////
	return(true);
}
////////////////////////////////////////////////////////////////////////////////////////////////
void CDInputJoystick::ConcreteMain() 
{
	DIJOYSTATE2 joystate;

	if (disp_capt)
	{
		ZeroMemory(&joystate,sizeof(joystate)); // resetejar la memòria
		
		if(FAILED(hr=lpdidev->Poll()))
			MessageBox(NULL, GetDIError(hr), "nfo", MB_OK|MB_ICONEXCLAMATION);
		
		int i;
		hr = lpdidev->GetDeviceState(sizeof(DIJOYSTATE2), (void *) &joystate);
		
		if(FAILED(hr))
		{
			hr = lpdidev->Acquire();
			MessageBox(NULL, GetDIError(hr), "nfo", MB_OK|MB_ICONEXCLAMATION);
			return;
		}
		// recollim per TOTS els botons
		for (i = 0; i < nbotons; i++)
		{
			estat.b[i]= (joystate.rgbButtons[i] & 0x80)/128;
		}
		estat.x = joystate.lX;			
		estat.y = joystate.lY;
		if (estat.hasGUID_ZAxis) {
			estat.z = joystate.lZ;
		}
		if (estat.hasGUID_POV) {
			for (i = 0; i < 5; i++)
				estat.eixpov[i] = joystate.rgdwPOV[i];
		}
		if (estat.hasGUID_Slider) {
			for (i = 0; i < 3; i++)
				estat.eixslider[i] = joystate.rglSlider[i];
		}
		if (estat.hasGUID_RxAxis) {
			estat.raxis[0] = joystate.lRx;
		}
		if (estat.hasGUID_RyAxis) {
			estat.raxis[1] = joystate.lRy;
		}
		if (estat.hasGUID_RzAxis) {
			estat.raxis[2] = joystate.lRz;
		}
	} // fi de if (disp_capt)
} 
///////////////////////////////////////////////////////////////////////////////////////
void CDInputJoystick::ConcreteMoreAxis() 
{
	MessageBox(NULL, "CONCRETE MORE AXIS", "nfo", MB_OK|MB_ICONSTOP);

	return;
}
////////////////////////////////////////////////////////////////
void  CDInputJoystick::ConcreteMoreButtons()
{
	return;
}