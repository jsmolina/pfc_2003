// ==============================================================
// File Name: CDirectInput.h
// 
// Model Name: Treball de fi de Carrera
// 
// 
// 
// ==============================================================

#ifndef CDirectInput_H
#define CDirectInput_H

#define DIRECTINPUT_VERSION 0x800 //versió mínima de DirectInput per l'usuari
#define MAX_DEVICES 10 // total de dispositius capturats
#include <dinput.h>
#include <windows.h>  // windows headers
#include <windowsx.h> // macros
#include <stdlib.h> // funciones matemáticas
#include <stdio.h> // funciones de entrada

BOOL CALLBACK DIEnumDevicesCallback(LPCDIDEVICEINSTANCE lpddi, LPVOID pvRef);
BOOL CALLBACK DIEnumDeviceMouseComponentsCallback(LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef);
BOOL CALLBACK DIEnumDeviceJoyCallback(LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef);


struct jsmstatus {
	int				nDevice;
	int				*b;
	int				x;
	int				y;
	int				z;
	int				raxis[3];
	int				eixpov[4];
	int				eixslider[2];
	bool			hasGUID_ZAxis;  // <bool> true si te eix Z
	bool			hasGUID_RxAxis; // <bool> true si te eix x de rotacio
	bool			hasGUID_RyAxis; // <bool> true si te eix y de rotacio
	bool			hasGUID_RzAxis; // <bool> true si te eix z de rotacio
	bool			hasGUID_Slider; // <bool> true si te slider
	bool			hasGUID_POV;    // <bool> true si te point-of-view
};
// Class Name: CDirectInput
// See file: 'CDirectInput.cpp' for the implementation of this class


class CDirectInput {
// Attributes:
	public:
	// public data members:
		bool exclusiu;
		bool background;
	protected:
	// private data members:		
		LPDIRECTINPUT8 lpdi;
		HRESULT hr;
		bool disp_capt;
		int nbotons;
		int neixos;
		HWND hwnd;
		HINSTANCE hinstance;
		jsmstatus estat;
		LPDIRECTINPUTDEVICE8 lpdidev;
	    DIDEVICEINSTANCE    diDeviceInstance;   // DIDEVICEINSTANCE
	
// Operations:

	public:
	// public member functions:
		bool Create_Device(GUID id_disp, DWORD Flags);
		bool Init(); // Inicialitza el dispositiu
		void Main(); // obté l'estat per polling
		void ShutDown(); // tanca el dispositiu i allibera recursos
		void MoreButtons(); // per incrementar el nombre de botons
		void MoreAxis(GUID type); // per incrementar el nombre d'eixos, GUID identifica el tipus (Z, Rx, POV, Slider, ...)
		int GetnBotons();  // retorna el nombre de botons
		int GetnEixos(); // retorna el nombre d'eixos
		void ControlPanel(); // crida al Control Panel
		jsmstatus * GetStatus(); // obté l'estat
		
		CDirectInput(HWND hwnd2, HINSTANCE hinst2);
		~CDirectInput();
	protected:
	// protected member functions:
		// Dienum podria ser estàtic, però llavors totes les variables han de ser estàtiques i això no
		// interessa
		//BOOL CALLBACK DIEnumDeviceComponentsCallback(LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef);
		virtual bool  ConcreteCreate(GUID id_disp, DWORD Flags) = 0; // VIRTUAL PUR. per funcionalitat pròpia de l'objecte
		virtual void  ConcreteMain() = 0;   // VIRTUAL PUR. per funcionalitat pròpia de l'objecte
		virtual void  ConcreteMoreAxis() = 0; // VIRTUAL PUR. per funcionalitat pròpia de l'objecte
		virtual void  ConcreteMoreButtons() = 0; // VIRTUAL PUR. per funcionalitat pròpia de l'objecte

		TCHAR* GetDIError(HRESULT error);
};

#endif // CDirectInput_H
