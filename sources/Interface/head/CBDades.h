#ifndef CBDades_H
#define CBDades_H
//#include "Queue.h"
#include "CConfiguration.h"
#include "DirectInput/dinput_f.h"
#include "Window_Handles.h"
#include "CFilterDI.h"

#define LONG_STRING 255

// Estructura de dades per guardar informació sobre el dispositiu
typedef struct {
	char bios [LONG_STRING];
	char model_str[LONG_STRING];
	int dll_major;
	int dll_minor;
	int model;
	int eixos;
	int botons;
	int major;
	int minor;
	bool can_beep;
}Devinfo;


	class CBDades 
	{
			private:
				 //Queue * pCua_events; // per guardar els events
				 Devinfo devinfo; // guardar la informació del dispositiu virtual
				 CConfiguration config; // guardar la configuració del dispositiu
				 CDirectInput * pCDirectInput[MAX_DEVICES]; // guardar array de dispositius DirectInput
 				 Device_Selector* theDevice_Selector; // guardar selector de dispositius
				 Window_Handles   theWindow_Handles;
			 	 CFilterDI * cf;

			public:				
				// membres
				HWND	  hwnd_exe;  // necessari per directinput tenir qui té el hwnd
				HINSTANCE hinst_exe; // necessari per directinput tenir qui té el hinstance
				bool mfc_init; // per aconseguir saber si ja ha entrat el MFC
				// functions
				CBDades();
				~CBDades();
				//bool NouEvent(Event *pEvent); // afegeix un nou event a la cua
				//Event * RecollirEvent();      // recull el event primer entrat a la cua
				Devinfo * GetDevInfo();      // recull el punter a la informació del disp virtual
				CConfiguration * GetDevConfig(); // recull el punter a la configuració del disp virtual
				Window_Handles * GetWindowHandles(); // recull el punter a la llista de handles de finestres que utilitzen el programa
				bool NovaConfig(Devinfo * pDevInfo, CConfiguration * pFiltersConfig); // assigna una nova configuració
				CDirectInput ** GetDI(); // retorna el array de punters a dispositius directinput
				Device_Selector * GetSelector(); // retorna el punter al selector de dispositius
				CFilterDI * GetCFilter();
				void SetSelector(Device_Selector * selector); // estableix el selector de dispositius
		};


#endif // CBDades_H
