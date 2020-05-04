#define WIN32_LEAN_AND_MEAN
#define INITGUID

#include <string>
#include "resource.h" // para los recursos (menú, ...)
#include "dinput_f.h"


using namespace std;
// tipus d'objectes per funcionar
Device_Selector		* d_sel;
CDirectInput		* interficie[MAX_DEVICES]; 
//HINSTANCE			hinst2;
WinFunc				*winfunc;



LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam); // Manegador d'events

int WINAPI WinMain (HINSTANCE hinstance, HINSTANCE hprevinstance, LPSTR lpcmdline, int ncmdshow)
{
	
	//hinst2 = hinstance;
	int i;
 
	WNDCLASSEX winclass;
		winclass.cbSize = sizeof(WNDCLASSEX);
		winclass.style = CS_VREDRAW | CS_HREDRAW | CS_OWNDC;
		winclass.lpfnWndProc = WindowProc; // assignem punter a funció
		winclass.cbClsExtra = 0;
		winclass.cbWndExtra = 0;
		winclass.hInstance = hinstance;
		winclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);		
		winclass.hCursor = LoadCursor(NULL, IDC_ARROW);		
		//winclass.hbrBackground = (HBRUSH)COLOR_WINDOW;
		winclass.hbrBackground = (HBRUSH ) GetStockObject(BLACK_BRUSH);		
		winclass.lpszMenuName = NULL;		
		winclass.lpszClassName = "WINCLASS1";		
		winclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);		
	// avisa a Windows sobre la nova classe  //
		RegisterClassEx(&winclass);
	// ara es Crea la Finestra               //
		HWND hwnd;
	// CENTREM PRIMER EL CURSOR A LA PANTALLA!!
		SetCursorPos(GetSystemMetrics(SM_CXSCREEN)/ 2, GetSystemMetrics(SM_CYSCREEN)/ 2);
		if (!(hwnd = CreateWindowEx(NULL, "WINCLASS1", "DirectX |escape|->anul·lar captura   |botó 1 i del mig|->per sortir", 
									WS_OVERLAPPEDWINDOW | WS_VISIBLE , 0,0, GetSystemMetrics(SM_CXSCREEN),400, NULL,  LoadMenu(hinstance, MAKEINTRESOURCE(IDR_MENU1)), hinstance, NULL)))
				return 0; // si ha fallat, sortim!!
	// mostrem la finestra              //
		ShowWindow(hwnd, ncmdshow);
	//	creem el objecte per Llistar dispositius  //
	d_sel = new Device_Selector(hwnd, hinstance);
	winfunc = new WinFunc(hwnd, hinstance);
	// ENUMERACIO DE DISPOSITIUS
	d_sel->EnumerarDispositius(DI8DEVCLASS_POINTER);
	d_sel->EnumerarDispositius(DI8DEVCLASS_DEVICE);
	d_sel->EnumerarDispositius(DI8DEVCLASS_GAMECTRL);	
	
	// DEMANEM REPINTAR
	SendMessage(hwnd, WM_PAINT, 0,0);
// ara ja entrem al bucle principal //
		MSG msg;		
		// REAL-TIME PROCESSING (existeix també la versió Standard)
			while(TRUE)
			{
				if (PeekMessage(&msg, NULL, 0,0, PM_REMOVE))
				{
					// provar si sortim
					if (msg.message == WM_QUIT)					
						break;	
					// funcions normals
					TranslateMessage(&msg);
					DispatchMessage(&msg);
					
				}

				for (i = 0; i < d_sel->enumerats; i++) 
				{
					if ((interficie[i] != NULL))
					{						
						if (d_sel->seleccionats[i]) {
								interficie[i]->Main();							
						} // fi del if
					}
				}// fi del for			
				Sleep(1000 / 15);
			}	// fi del while
	return(0);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch(msg)
	{
		case WM_CREATE:
			// TODO: inicialitzacions
			return(0); 
			break;
		case WM_KEYDOWN: // per control de teclat
			winfunc->HandleKeyboard();
			return(0);
			break;
		case WM_PAINT:
			winfunc->HandlePaint();
			return(0);
			break;
		case WM_DESTROY:
			PostQuitMessage(0); // mata la aplicació
			return(0);
			break;
		case WM_CLOSE:
			{	
			//	int result = MessageBox(hwnd, "Segur?", "WMCLOSE", MB_YESNO | MB_ICONQUESTION);
			//	if (result == IDYES)
					return(DefWindowProc(hwnd,msg,wparam,lparam));
			//	else
			//		return(0);
			}break; 
		case WM_COMMAND: // per els menús!!!
			if(winfunc->HandleMenu(wparam, lparam)) 
				return(0);
		
		case WM_TIMER:
			SendMessage(hwnd, WM_PAINT, 0,0);
			
			break;
		default: 
			break;
	}
	//////////// processa els altres events per defecte
	  return  DefWindowProc(hwnd, msg,wparam, lparam);
	}
