#include "dinput_f.h"

//class Mouse_Interface;
extern Device_Selector		*d_sel;
extern CDirectInput		* interficie[MAX_DEVICES];


/////////////////////////////////////////////////////////// 
//  Classe Device_Sector -> dades sobre dispositius      //
///////////////////////////////////////////////////////////
// CONSTRUCTOR
	Device_Selector::Device_Selector(HWND hwnd, HINSTANCE hinstance)
	{
		int i;

		hr = DirectInput8Create(hinstance, DIRECTINPUT_VERSION, IID_IDirectInput8,(void**)&lpdi, NULL);
		if (hr == DIERR_OLDDIRECTINPUTVERSION) {
			MessageBox(NULL, "Necessita una versió més actualitzada de DirectInput.", "nfo", MB_OK|MB_ICONINFORMATION);
		}
		if (FAILED(hr)) {			
			
		}
		posy = 50;
		tmp = 1;
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
		/*if ((lpddi->dwDevType ==DI8DEVTYPE_MOUSE) || (lpddi->dwDevType ==DI8DEVTYPE_SCREENPOINTER))  {
			MessageBox(NULL, "Es de tipus mouse.", "nfo", MB_OK|MB_ICONINFORMATION);
		}
		else if ( (lpddi->dwDevType ==DI8DEVTYPE_DRIVING) || (lpddi->dwDevType ==DI8DEVTYPE_FLIGHT)||(lpddi->dwDevType ==DI8DEVTYPE_GAMEPAD)||(lpddi->dwDevType ==DI8DEVTYPE_JOYSTICK) ){
			MessageBox(NULL, "Tipus Joystick.", "nfo", MB_OK|MB_ICONINFORMATION);
		}*/
		
		if ((GET_DIDEVICE_TYPE(lpddi->dwDevType) ==DI8DEVTYPE_MOUSE) || (GET_DIDEVICE_TYPE(lpddi->dwDevType) ==DI8DEVTYPE_SCREENPOINTER) || (GET_DIDEVICE_TYPE(lpddi->dwDevType) ==DI8DEVCLASS_DEVICE)) {
			dtype[enumerats] = RATOLI; // assignem el tipus
		}
		else {
			dtype[enumerats] = JOYSTICK;
		}
		sprintf(disp_list[enumerats], "%d - %s", enumerats + 1, lpddi->tszProductName);		
		enumerats++;
	}
	////////////////////////////////////////////////////////////////////
	void Device_Selector::EnumerarDispositius(DWORD dwDevType)
	{
		hr = lpdi->EnumDevices(dwDevType, DIEnumDevicesCallback,	NULL, DIEDFL_ALLDEVICES | DIEDFL_ATTACHEDONLY );
		//hr = lpdi->EnumDevices(DIDEVTYPE_JOYSTICK, DIEnumDevicesCallback,	NULL, DIEDFL_ALLDEVICES | DIEDFL_ATTACHEDONLY );
		if (FAILED(hr)) 
		{
			MessageBox(NULL, "Enum Devices Fallada!", "nfo", MB_OK|MB_ICONINFORMATION);
			
		}

	}
	////////////////////////////////////////////////////////////////////
	void Device_Selector::RetornarLlista(HDC hdc) 
	{
		int i;		
		posy= 50;
		TextOut(hdc,  30, d_sel->posy-20, "Escull un o mes dispositius de la llista",40 ); 		
		// 1-> primer dispositiu
		
		
		for (i = 0; i < enumerats; i++)
		{					
			if (seleccionats[i] == false) 
			{
				SetTextColor(hdc, RGB(0,255,0));
			}
			else
			{
				SetTextColor(hdc, RGB(255,0,0));
			}
			TextOut(hdc,  30, d_sel->posy, disp_list[i], strlen(disp_list[i])); 
			posy += 20;
		}
		SetTextColor(hdc, RGB(0,255,0));
		posy += 20;
		TextOut(hdc,  30, d_sel->posy, "Una vegada seleccionat, escull la opcio del menu Adquirir.", 58); 
	}
	////////////////////////////////////////////////////////////////////
	void Device_Selector::Comprovar_Tecles()
	{ 
		
	} // fi del bloc d'assignació de dispositius
	
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
		d_sel->NouDispositiu(lpddi);	
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

/////////////////////////////////////////////////////////// 
//              Classe WinFunc                           //
///////////////////////////////////////////////////////////

void WinFunc::WinCls() 
{
	int i;
	HDC hdc;
	RECT rect;		

	hdc = GetDC(hwnd);
SetBkColor(hdc, RGB(0,0,0));
	for (i = 0; i < 400; i +=tm.tmHeight)
		TextOut(hdc,  0, i, "                                                                                                                                                                                                                            ", 220);
	ReleaseDC(hwnd, hdc);
	GetClientRect(hwnd, &rect); // obtenir àrea de client
	ValidateRect(hwnd, &rect);	
}
//////////////////////////////////////////////////////////
//			FUNCIÓ PER COL·LOCAR TEXT A LA PANTALLA     //
//////////////////////////////////////////////////////////
void WinFunc::WinPrintf(int x, int y, char * buffer) 
{
	HDC hdc;
	RECT rect;		
	if (buffer == NULL) {
		MessageBox(hwnd, "Entrada NULL!!.", "nfo",  MB_OK|MB_ICONSTOP);
	}
	hdc = GetDC(hwnd);
SetBkColor(hdc, RGB(255,255,255));
	TextOut(hdc,  x, y, buffer, strlen(buffer));
	ReleaseDC(hwnd, hdc);
	GetClientRect(hwnd, &rect); // obtenir àrea de client
	ValidateRect(hwnd, &rect);	
}


bool WinFunc::HandleMenu(WPARAM wparam, LPARAM lparam)
{
	int i;
	/*HINSTANCE hinstance = hinst2;*/
	//WinCls(hwnd);
	HIWORD(wparam);
	switch(LOWORD(wparam))
	{
	case ID_ARCHIVO_ABRIR: // take a look a SCRIPT1.RC
		if (d_sel!=NULL)
			delete d_sel;
		d_sel = new Device_Selector(hwnd, hinst);
		d_sel->EnumerarDispositius(DI8DEVCLASS_POINTER);
		d_sel->EnumerarDispositius(DI8DEVCLASS_DEVICE);
		d_sel->EnumerarDispositius(DI8DEVCLASS_GAMECTRL);
		WinCls();
		//MessageBox(hwnd, "La llista dels dispositius ha estat reinicialitzada.", "nfo",  MB_OK|MB_ICONINFORMATION);
		break;
	case ID_ADQUIRIR_EXCLUSIUIBACKGROUND:
		// creem els dispositius escollits, en mode background
		// cridar a funció que agafi tots els llistats
		// i els cridi en un mode--- DISCL_FOREGROUND | DISCL_EXCLUSIVE 
		Instantiate ( DISCL_BACKGROUND | DISCL_EXCLUSIVE);
		break;
	case ID_ADQUIRIR_EXCLUSIUIFOREGROUND:		
		Instantiate (DISCL_FOREGROUND | DISCL_EXCLUSIVE);		
		break;
	case ID_ADQUIRIR_NOEXCLUSIUIBACKGROUND:
		Instantiate (DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);
		break;
	case ID_ADQUIRIR_NOEXCLUSIUIFOREGROUND:
		Instantiate (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);		
		break;
	case ID_ARCHIVO_SALIR:
		{
			int result = MessageBox(hwnd, "Segur?", "WMCLOSE", MB_YESNO | MB_ICONQUESTION);
			if (result == IDYES)
				PostQuitMessage(0);	
			else
				return(true);
		}break;
	case ID_INFORMACIO_CPANEL:
		bool entrat = false;
		for (i = 0; i < d_sel->enumerats; i++) 
		{
			if (d_sel->seleccionats[i]) {
				entrat = true;				
				if (interficie[i] != NULL)
					interficie[i]->ControlPanel();
				else 
					MessageBox(hwnd, "Per poder executar aquesta opció\nes necessita tenir inicialitzat els dispositius.\nAixò es fa amb el menú Adquirir.", "nfo",  MB_OK|MB_ICONINFORMATION);
			}
		}
		if (entrat == false) {
			MessageBox(hwnd, "Per poder executar aquesta opció necessita:\n* Tenir algun dispositiu escollit. [Això es fa amb el teclat]\n* Tenir inicialitzats els dispositius. [Això es fa amb el menú Adquirir]", "nfo",  MB_OK|MB_ICONINFORMATION);
		}
	break;
	}


	InvalidateRect(hwnd,NULL,FALSE);
	return(true);
}

void WinFunc::HandlePaint()
{
	HDC hdc;
	RECT rect;		
	int i;

	hdc = GetDC(hwnd);	
	
	SetBkColor(hdc, RGB(10,10,10));	
	SetTextColor(hdc, RGB(0,255,0));
	
	d_sel->RetornarLlista(hdc);
	// segons els enumerats, llistar-los:
	d_sel->posy+=20;
	SetTextColor(hdc, RGB(255,255,255));
	TextOut(hdc, 20, d_sel->posy, "Valors:", 7);	
	SetTextColor(hdc, RGB(0,255,255));
	
	for (i = 0; i < d_sel->enumerats; i++) {
		if (d_sel->seleccionats[i]) {			
			d_sel->posy+=tm.tmHeight; // una línia més
			if (interficie[i] == NULL) {
				return;
			}
			printstatus(hdc, i);				
		}
	}
	
	ReleaseDC(hwnd, hdc);
	GetClientRect(hwnd, &rect); // obtenir àrea de client
	ValidateRect(hwnd, &rect);			
}


TEXTMETRIC WinFunc::GetTextMetricsJ(HDC hdc)
{	
	return(tm);
}


void WinFunc::HandleKeyboard()
{
	if (KEYDOWN(VK_F1)) 
	{
		SetTimer(hwnd, 1, 20, NULL);
		MessageBox(NULL, "TIMER INICIALITZAT", "EL MEU PRIMER PROGRAMA WINDOWS", MB_OK|MB_ICONINFORMATION);
		return;
	}
	if (KEYDOWN(VK_F2)) 
	{
		KillTimer(hwnd, 1);
		MessageBox(NULL, "TIMER MATAT", "EL MEU PRIMER PROGRAMA WINDOWS", MB_OK|MB_ICONINFORMATION);
	}
	if (KEYDOWN(VK_F3)) 
	{
		DWORD a;
		DWORD b;
		a = (DWORD) 780;
		b = (DWORD) 580;
		SendMessage(0, WM_LBUTTONUP,0,0);		
	}
	
	if (KEYDOWN(VK_ESCAPE)) 
	{
		int i;
		for (i = 0; i < d_sel->enumerats; i++) 
		{
			if ((interficie[i] != NULL) || (interficie[i] != NULL))
			{						
				if (d_sel->seleccionats[i]) {
					
						delete interficie[i];
						interficie[i] = NULL;					
				} // fi del if
			}
		}// fi del for		
		MessageBox(NULL, "Captura alliberada", "EL MEU PRIMER PROGRAMA WINDOWS", MB_OK|MB_ICONINFORMATION);
		WinCls();
	}
				
	{ // bloc de recollida de números del teclat
		int j;
		for (DWORD i = 0x31; i < 0x40; i++)
		{
			j= (int) i - 48;	
			if (KEYDOWN(i) && (j <= d_sel->enumerats))
			{				
				d_sel->seleccionats[j-1] = !d_sel->seleccionats[j-1];
				PostMessage(hwnd, WM_PAINT, 0,0);
				Sleep(1000/10);				
			}
		}
	}
	HandlePaint();
}

WinFunc::WinFunc(HWND hwnd, HINSTANCE hinstance)
{
	HDC hdc;

	this->hwnd		= hwnd;
	this->hinst		= hinstance;	
	hdc = GetDC(hwnd);	
	GetTextMetrics(hdc, &tm);
	ReleaseDC(hwnd, hdc);
}


void WinFunc::Instantiate (DWORD Flags)
{
	int i;
	bool seleccionat = false;
	bool algun = false;

	for (i = 0; i < d_sel->enumerats; i++) 
	{
		if (d_sel->seleccionats[i]) {
			if (d_sel->dtype[i] ==RATOLI) {				
				interficie[i] = new CDInputMouse(hwnd, hinst);
				seleccionat = true;				
			}
			else {				
				interficie[i] = new CDInputJoystick(hwnd, hinst);
				seleccionat = true;				
			}

			if (seleccionat==true) {
				if(interficie[i]->Create_Device(d_sel->guid_list[i], Flags))
					MessageBox(hwnd, "Ha estat capturat correctament.", "nfo",  MB_OK|MB_ICONINFORMATION);
				seleccionat=false;
			}
			algun=true;
		}
	}
	
	if (algun == false) {
		MessageBox(hwnd, "És necessari tenir escollit algun dispositiu.", "nfo",  MB_OK|MB_ICONINFORMATION);
		return;
	}
/*
	for (i = 0; i < d_sel->enumerats; i++) 
	{
		if (d_sel->seleccionats[i]) {
			if (d_sel->dtype[i] ==RATOLI) {
				if(m_int[i]->Create_Device(d_sel->guid_list[i], Flags)) {
					MessageBox(hwnd, "Adquirit Correctament.", "nfo",  MB_OK|MB_ICONINFORMATION);
				}					
			}
			else {
				if(j_int[i]->Create_Device(d_sel->guid_list[i], Flags)) {
					MessageBox(hwnd, "Adquirit Correctament.", "nfo",  MB_OK|MB_ICONINFORMATION);
				}
			}
		}
	}*/		
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
void WinFunc::printstatus(HDC hdc, int i)
{
	//TextOut(hdc, 20, d_sel->posy, "Valors:", 7);	
	char  * buffer;
	char  tmp[255];
	buffer = (char *) malloc(512*sizeof(char));
	int j;

	sprintf(buffer, "                                                                                                                                                     ");
	TextOut(hdc, 25, d_sel->posy, buffer, strlen(buffer));
	jsmstatus st = interficie[i]->GetStatus();
	
	// pels eixos	
	sprintf(buffer, " X=%d Y=%d", st.x, st.y);
	
	
	if (interficie[i]->GetnEixos() > 2) { // tenim més de 3 eixos
		if (st.hasGUID_ZAxis) {
			sprintf(tmp, " Z=%d", st.z);
			strcat(buffer, tmp);
		}
		// els eixos de rotació
		if (st.hasGUID_RxAxis) {
			sprintf(tmp, " Rx=%d", st.raxis[0]);
			strcat(buffer, tmp);
		}
		if (st.hasGUID_RyAxis) {
			sprintf(tmp, " Ry=%d", st.raxis[1]);
			strcat(buffer, tmp);
		}
		if (st.hasGUID_RzAxis) {
			sprintf(tmp, " Rz=%d", st.raxis[2]);
			strcat(buffer, tmp);
		}
		// els eixos de slider		
		if (st.hasGUID_Slider) {
			sprintf(tmp, " SliderX=%d SliderY=%d", st.raxis[0], st.raxis[1]);
			strcat(buffer, tmp);
		}
		if (st.hasGUID_POV) {			
			sprintf(tmp, " POV1=%d POV2=%d POV3=%d POV4=%d", st.eixpov[0], st.eixpov[1], st.eixpov[2], st.eixpov[3]);
			strcat(buffer, tmp);
		}		
	}
	// pels botons
	for ( j = 0; j < interficie[i]->GetnBotons(); j++)
	{
		sprintf(tmp, " | B%d=%d ", j, st.b[j]);
		strcat(buffer, tmp);
	}
	TextOut(hdc, 25, d_sel->posy, buffer, strlen(buffer));
	delete buffer;
	//return(buffer);
}