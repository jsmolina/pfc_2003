// ==============================================================
// File Name: CDInputMouse.cpp
// 
// Model Name: Treball de fi de Carrera
// 
// 
// 
// ==============================================================

#include "CDInputMouse.h" // class header file
// Class: CDInputMouse
// 
// Operations (Member Functions):

CDInputMouse::CDInputMouse(HWND hwnd2, HINSTANCE hinst2)
	: CDirectInput(hwnd2, hinst2)
{

}

bool CDInputMouse::ConcreteCreate(GUID id_disp, DWORD Flags) 
{
	if (Flags == (DISCL_BACKGROUND | DISCL_EXCLUSIVE)) {
		MessageBox(NULL, "El mode Exclusiu i BackGround alhora\nno és permés en el Mouse, sí en joysticks.\nNo ha pogut ser adquirit.  [CDInputMouse::ConcreteCreate]", "nfo", MB_OK|MB_ICONEXCLAMATION);
		return false;
	}
	
	if(!lpdi) 
	{
		MessageBox(NULL, "DirectInput no inicialitzat  [CDInputMouse::ConcreteCreate]", "nfo", MB_OK|MB_ICONINFORMATION);
		return false;
	}

	// mirem quants eixos té:
	// aquí hauria de funcionar amb el mouse	
	// igualo els punters per la funció enumDeviceObjects...

	if (FAILED(lpdidev->EnumObjects(DIEnumDeviceComponentsCallback, (LPVOID) this, DIDFT_AXIS | DIDFT_BUTTON))) {
		MessageBox(NULL, "No puc enumerar objectes de dispositiu  [CDInputMouse::ConcreteCreate]", "nfo", MB_OK|MB_ICONINFORMATION);
		return false;
	}
	// reservem memòria per TOTS els botons
	if (nbotons > 0) {
		estat.b = (int*) malloc(nbotons*sizeof(int));
	}
	else  {
		MessageBox(NULL, "No es possible reservar pels botons! [nbotons <= 0]  [CDInputMouse::ConcreteCreate]", "nfo", MB_OK|MB_ICONINFORMATION);
		return(false);
	}
	// establir el nivell cooperatiu
	if (FAILED(lpdidev->SetCooperativeLevel(hwnd, Flags))) {
		MessageBox(NULL, "No es pot establir el nivell cooperatiu dessitjat. [CDInputMouse::ConcreteCreate]", "nfo", MB_OK|MB_ICONINFORMATION);
		return false;
	}
	
	// establir el format de dades
	if (FAILED(lpdidev->SetDataFormat(&c_dfDIMouse)))	{
		MessageBox(NULL, "No puc establir el format [CDInputMouse::ConcreteCreate]", "nfo", MB_OK|MB_ICONINFORMATION);
		return false;
	}
	return(true);
}

void CDInputMouse::ConcreteMain() 
{
	int i;
	

	DIMOUSESTATE2 mousestate;

	if (disp_capt) 
	{		
		hr = lpdidev->GetDeviceState(sizeof(DIMOUSESTATE), (void *) &mousestate);
		if(FAILED(hr))
		{
			hr = lpdidev->Acquire();
			return;
		}
		// recollim per TOTS els botons
		for (i = 0; i < nbotons; i++)
		{				
			estat.b[i]= (mousestate.rgbButtons[i] & 0x80)/128;
			// això és per sortir, per ara queda anul·lat
			//if ((estat.b[0] == 1) && (estat.b[2] == 1))
			//	PostQuitMessage(0);
		}
		
		estat.x=mousestate.lX;
		estat.y=mousestate.lY;
		if (neixos > 2)
			estat.z = mousestate.lZ;
	}
}


void CDInputMouse::ConcreteMoreAxis() 
{
	MessageBox(NULL, "CONCRETE MORE AXIS MOUSE VERSION", "nfo", MB_OK|MB_ICONSTOP);
	return;
}

void  CDInputMouse::ConcreteMoreButtons()
{
	return;
}
