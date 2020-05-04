#ifndef DINPUT_F
#define DINPUT_F
#define KEYDOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1:0)
#define KEYUP(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000)   ? 0:1)

#define DIRECTINPUT_VERSION 0x800 //versi� m�nima de DirectInput per l'usuari
#define MAX_DEVICES 10 // total de dispositius capturats
#include <dinput.h>
#include <windows.h>  // windows headers
#include <windowsx.h> // macros
#include <stdlib.h> // funciones matem�ticas
#include <stdio.h> // funciones de entrada
#include "CDirectInput.h"
#include "CDInputMouse.h"
#include "CDInputJoystick.h"
#include "resource.h" // para los recursos (men�, ...)

#define GET_DIDEVICE_TYPE(dwDevType)  LOBYTE(dwDevType) // per a obtenir el tipus de dispositiu directament
#define RATOLI	 1 // pel dtype
#define JOYSTICK 2 // pel dtype




class Device_Selector;
BOOL CALLBACK DIEnumDevicesCallback(LPCDIDEVICEINSTANCE lpddi, LPVOID pvRef);
BOOL CALLBACK DIEnumDeviceComponentsCallback(LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef);
//BOOL CALLBACK DIEnumDeviceJoyCallback(LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef);

//////////////////////////////////////////////////////////
////       CLASSE PER LA DECISI� DE DISPOSITIUS       ////
////												  ////
//////////////////////////////////////////////////////////
class Device_Selector
{
public:
	GUID						guid_list[MAX_DEVICES];     // <GUID[]> de tots els llistats
	char						disp_list[MAX_DEVICES][50]; // <char[][]> llista a alt nivell dels dispositius
	int							enumerats; // <int> quants han escollit?
	bool						seleccionats[MAX_DEVICES]; // <bool[]> per saber quins ha seleccionat l'usuari		
	int							dtype[MAX_DEVICES]; // <DWORD[]> per saber quina versi� cridar
	int							posy; // <int> variable per imprimir en una posici�
	int							tmp; // <int> variable per altres usos 'extras'
	
	void NouDispositiu(LPCDIDEVICEINSTANCE lpddi);
	void EnumerarDispositius(DWORD dwDevType); // funci� per generar la enumeraci�
	void RetornarLlista(HDC hdc); // funci� per retornar dades a alt nivell
	GUID RetornarGUID(int i); // funci� per retornar una GUID concreta
	void Comprovar_Tecles(); // funci� per assignar dispositius, i seleccionar-los
	Device_Selector(HWND hwnd, HINSTANCE hinstance); // constructor
	Device_Selector::~Device_Selector(); // destructor

private:		
	LPDIRECTINPUT				lpdi;  // <LPDIRECTINPUT> objecte de DirectInput
	HRESULT						hr; // <HRESULT> resultat crides
	HWND						hwnd; // <HWND> handle Window de la finestra actual
	HINSTANCE					hinstance; // <HINSTANCE> handle instance del programa

};
//////////////////////////////////////////////////////////////
//     Classe WinFunc, per treballar sobre la API r�pidament//
//////////////////////////////////////////////////////////////
class WinFunc
{
public:	
	void WinCls();	//	FUNCI� PER NETEJAR EL TEXT DE LA PANTALLA  
	void WinPrintf(int x, int y, char * buffer); // FUNCI� PER COL�LOCAR TEXT A LA PANTALLA
	void HandleKeyboard(); // Agafa dades del teclat
	void HandlePaint();  // per repintar
	void printstatus(HDC hdc, int i); // per pintar per pantalla les coordenades i botons.
	bool HandleMenu(WPARAM wparam, LPARAM lparam); // per control�lar les opcions del men�
	TEXTMETRIC GetTextMetricsJ(HDC hdc);
	WinFunc(HWND hwnd, HINSTANCE hinstance);
private:
	void Instantiate (DWORD Flags);
	HINSTANCE					hinst;
	HWND						hwnd;
	TEXTMETRIC					tm;
};


#endif