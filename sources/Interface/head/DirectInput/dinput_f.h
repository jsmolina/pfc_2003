#ifndef DINPUT_F
#define DINPUT_F
#define KEYDOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1:0)
#define KEYUP(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000)   ? 0:1)

#define DIRECTINPUT_VERSION 0x800 //versió mínima de DirectInput per l'usuari
#define MAX_DEVICES 10 // total de dispositius capturats
#include <dinput.h>
#include <windows.h>  // windows headers
#include <windowsx.h> // macros
#include <stdlib.h> // funciones matemáticas
#include <stdio.h> // funciones de entrada
#include "CDirectInput.h"
#include "CDInputMouse.h"
#include "CDInputJoystick.h"
#include "resource.h" // para los recursos (menú, ...)

#define GET_DIDEVICE_TYPE(dwDevType)  LOBYTE(dwDevType) // per a obtenir el tipus de dispositiu directament
#define RATOLI	 1 // pel dtype
#define JOYSTICK 2 // pel dtype

#ifdef WRAPPER_EXPORTS
#define WRAPPER_API __declspec(dllexport)
#else
#define WRAPPER_API __declspec(dllimport)
#endif



class Device_Selector;
BOOL CALLBACK DIEnumDevicesCallback(LPCDIDEVICEINSTANCE lpddi, LPVOID pvRef);
BOOL CALLBACK DIEnumDeviceComponentsCallback(LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef);
//BOOL CALLBACK DIEnumDeviceJoyCallback(LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef);

//////////////////////////////////////////////////////////
////       CLASSE PER LA DECISIÓ DE DISPOSITIUS       ////
////												  ////
//////////////////////////////////////////////////////////
class Device_Selector
{
public:
	GUID						guid_list[MAX_DEVICES];     // <GUID[]> de tots els llistats
	char						disp_list[MAX_DEVICES][50]; // <char[][]> llista a alt nivell dels dispositius
	volatile int				enumerats; // <int> quants han escollit?
	bool						seleccionats[MAX_DEVICES]; // <bool[]> per saber quins ha seleccionat l'usuari		
//	int							utilitzables; //  quins seràn utilitzables
	int							dtype[MAX_DEVICES]; // <DWORD[]> per saber quina versió cridar
//	int							posy; // <int> variable per imprimir en una posició
//	int							tmp; // <int> variable per altres usos 'extras'
	
	void NouDispositiu(LPCDIDEVICEINSTANCE lpddi);
	void EnumerarDispositius(DWORD dwDevType); // funció per generar la enumeració
	GUID RetornarGUID(int i); // funció per retornar una GUID concreta
	Device_Selector(HWND hwnd, HINSTANCE hinstance); // constructor
	Device_Selector(); // constructor
	Device_Selector::~Device_Selector(); // destructor

private:		
	LPDIRECTINPUT				lpdi;  // <LPDIRECTINPUT> objecte de DirectInput
	HRESULT						hr; // <HRESULT> resultat crides
	HWND						hwnd; // <HWND> handle Window de la finestra actual
	HINSTANCE					hinstance; // <HINSTANCE> handle instance del programa

};


#endif