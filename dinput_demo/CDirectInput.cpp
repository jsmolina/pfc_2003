// ==============================================================
// File Name: CDirectInput.cpp
// 
// Model Name: Treball de fi de Carrera
// 
// 
// 
// ==============================================================

#include "CDirectInput.h" // class header file
// Class: CDirectInput
// 
// Operations (Member Functions):

void CDirectInput::ControlPanel() 
{
	lpdidev->RunControlPanel(hwnd,  0);

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CDirectInput::Create_Device(GUID id_disp, DWORD Flags) 
{
	// crear dispositiu, lpdiM queda assignat
	if(!lpdi) 
	{
		MessageBox(NULL, "DirectInput no inicialitzat, és NULL [CDirectInput::CreateDevice]", "nfo", MB_OK|MB_ICONSTOP);
		return false;
	}

	if (FAILED(lpdi->CreateDevice(id_disp, &lpdidev,  NULL))) {
		MessageBox(NULL, "No puc crear el Dispositiu [CDirectInput::CreateDevice]", "nfo", MB_OK|MB_ICONEXCLAMATION);
		return (false);
	}
	// CONCRETE CREATE, PER MOUSE O JOYSTICK
	if (ConcreteCreate(id_disp, Flags)==false) {
		return (false);
	}
	
	if (lpdidev == NULL) {
		MessageBox(NULL, "LPDIDEV ES NULL  [CDirectInput::CreateDevice]", "nfo", MB_OK|MB_ICONEXCLAMATION);
	}
	// adquirint el dispositiu (quan ja ha estat creat!)
	if (FAILED(lpdidev->Acquire())) {
		MessageBox(NULL, "No puc adquirir el dispositiu [CDirectInput::CreateDevice]", "nfo", MB_OK|MB_ICONINFORMATION);
		return (false);
	}
	//MessageBox(NULL, "DISPOSITIVO DINPUT CREADO [CDirectInput::CreateDevice]", "nfo", MB_OK|MB_ICONINFORMATION);
	disp_capt = true;	
	return(true);
}


///////////////////////////////////////////////////////////////////////////////////////////////////

TCHAR* CDirectInput::GetDIError(HRESULT error)
{
	switch(error)
	{
	case E_PENDING : return ("E_PENDING : Data Not Available.\n");
		break;
	case E_HANDLE :  return ("E_HANDLE : The HWND parameter is not a valid top-level window that belongs to the process.\n");
		break;
	case DIERR_UNSUPPORTED : return ("DIERR_UNSUPPORTED : The function called is not supported at this time. This value is equal to the E_NOTIMPL standard COM return value.\n");
		break;
	case DIERR_UNPLUGGED : return ("DIERR_UNPLUGGED : The operation could not be completed because the device is not plugged in.\n");
		break;
	case DIERR_REPORTFULL : return ("DIERR_REPORTFULL : More information was requested to be sent than can be sent to the device.\n");
		break;
	case DIERR_READONLY : return ("DIERR_READONLY : The specified property cannot be changed. This value is equal to the E_ACCESSDENIED standard COM return value.\n");
		break;
	case DIERR_OUTOFMEMORY : return ("DIERR_OUTOFMEMORY : The DirectInput subsystem could not allocate sufficient memory to complete the call. This value is equal to the E_OUTOFMEMORY standard COM return value.\n");
		break;
		//	case DIERR_OTHERAPPHASPRIO : return ("DIERR_OTHERAPPHASPRIO : Another application has a higher priority level, preventing this call from succeeding. This value is equal to the E_ACCESSDENIED standard COM return value. This error can be returned when an application has only foreground access to a device but is attempting to acquire the device while in the background. ");
		//		break;
	case DIERR_OLDDIRECTINPUTVERSION : return ("DIERR_OLDDIRECTINPUTVERSION : The application requires a newer version of DirectInput.\n");
		break;
	case DIERR_OBJECTNOTFOUND : return ("DIERR_OBJECTNOTFOUND : The requested object does not exist.\n");
		break;
	case DIERR_NOTINITIALIZED : return ("DIERR_NOTINITIALIZED : This object has not been initialized.\n");
		break;
		//	case DIERR_NOTFOUND : return ("DIERR_NOTFOUND : The requested object does not exist.\n");
		//		break;
	case DIERR_NOTEXCLUSIVEACQUIRED : return ("DIERR_NOTEXCLUSIVEACQUIRED : The operation cannot be performed unless the device is acquired in DISCL_EXCLUSIVE mode.\n");
		break;
	case DIERR_NOTDOWNLOADED : return ("DIERR_NOTDOWNLOADED : The effect is not downloaded.\n");
		break;
	case DIERR_NOTBUFFERED : return ("DIERR_NOTBUFFERED : The device is not buffered. Set the DIPROP_BUFFERSIZE property to enable buffering.\n");
		break;
	case DIERR_NOTACQUIRED : return ("DIERR_NOTACQUIRED : The operation cannot be performed unless the device is acquired.\n");
		break;
	case DIERR_NOINTERFACE : return ("DIERR_NOINTERFACE : The specified interface is not supported by the object. This value is equal to the E_NOINTERFACE standard COM return value.\n");
		break;
	case DIERR_NOAGGREGATION : return ("DIERR_NOAGGREGATION : This object does not support aggregation.\n");
		break;
	case DIERR_MOREDATA : return ("DIERR_MOREDATA : Not all the requested information fit into the buffer.\n");
		break;
	case DIERR_INVALIDPARAM : return ("DIERR_INVALIDPARAM : An invalid parameter was passed to the returning function, or the object was not in a state that permitted the function to be called. This value is equal to the E_INVALIDARG standard COM return value.\n");
		break;
	case DIERR_INPUTLOST : return ("DIERR_INPUTLOST : Access to the input device has been lost. It must be reacquired.\n");
		break;
	case DIERR_INCOMPLETEEFFECT : return ("DIERR_INCOMPLETEEFFECT : The effect could not be downloaded because essential information is missing. For example, no axes have been associated with the effect, or no type-specific information has been supplied.\n");
		break;
		//	case DIERR_HANDLEEXISTS : return ("DIERR_HANDLEEXISTS : The device already has an event notification associated with it. This value is equal to the E_ACCESSDENIED standard COM return value.\n");
		//		break;
	case DIERR_GENERIC : return ("DIERR_GENERIC : An undetermined error occurred inside the DirectInput subsystem. This value is equal to the E_FAIL standard COM return value.\n");
		break;
	case DIERR_HASEFFECTS : return ("DIERR_HASEFFECTS : The device cannot be reinitialized because there are still effects attached to it.\n");
		break;
	case DIERR_EFFECTPLAYING : return ("DIERR_EFFECTPLAYING : The parameters were updated in memory but were not downloaded to the device because the device does not support updating an effect while it is still playing.\n");
		break;
	case DIERR_DEVICENOTREG : return ("DIERR_DEVICENOTREG : The device or device instance is not registered with DirectInput. This value is equal to the REGDB_E_CLASSNOTREG standard COM return value.\n");
		break;
	case DIERR_DEVICEFULL : return ("DIERR_DEVICEFULL : The device is full.\n");
		break;
	case DIERR_BETADIRECTINPUTVERSION : return ("DIERR_BETADIRECTINPUTVERSION : The application was written for an unsupported prerelease version of DirectInput.\n");
		break;
	case DIERR_BADDRIVERVER : return ("DIERR_BADDRIVERVER : The object could not be created due to an incompatible driver version or mismatched or incomplete driver components.\n");
		break;
	case DIERR_ALREADYINITIALIZED : return ("DIERR_ALREADYINITIALIZED : This object is already initialized\n");
		break;
	case DIERR_ACQUIRED : return ("DIERR_ACQUIRED : The operation cannot be performed while the device is acquired.\n");
		break;
	case DI_TRUNCATEDANDRESTARTED : return ("DI_TRUNCATEDANDRESTARTED : Equal to DI_EFFECTRESTARTED | DI_TRUNCATED\n");
		break;
	case DI_TRUNCATED : return ("DI_TRUNCATED : The parameters of the effect were successfully updated, but some of them were beyond the capabilities of the device and were truncated to the nearest supported value.\n");
		break;
	case DI_PROPNOEFFECT : return ("DI_PROPNOEFFECT : The change in device properties had no effect. This value is equal to the S_FALSE standard COM return value.\n");
		break;
	case DI_POLLEDDEVICE : return ("DI_POLLEDDEVICE : The device is a polled device. As a result, device buffering does not collect any data and event notifications is not signaled until the IDirectInputDevice7::Poll method is called.\n");
		break;
	case DI_OK : return ("DI_OK : The operation completed successfully. This value is equal to the S_OK standard COM return value.\n");
		break;
		//	case DI_NOTATTACHED : return ("DI_NOTATTACHED : The device exists but is not currently attached. This value is equal to the S_FALSE standard COM return value.\n");
		//		break;
		//	case DI_NOEFFECT : return ("DI_NOEFFECT : The operation had no effect. This value is equal to the S_FALSE standard COM return value.\n");
		//		break;
	case DI_EFFECTRESTARTED : return ("DI_EFFECTRESTARTED : The effect was stopped, the parameters were updated, and the effect was restarted.\n");
		break;
	case DI_DOWNLOADSKIPPED : return ("The parameters of the effect were successfully updated, but the effect could not be downloaded because the associated device was not acquired in exclusive mode.\n");
		break;
		//	case DI_BUFFEROVERFLOW : return ("DI_BUFFEROVERFLOW : The device buffer overflowed and some input was lost. This value is equal to the S_FALSE standard COM return value.\n");
		//		break;
	default: return ("Unknown Error Code.\n");
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////
bool CDirectInput::Init() 
{
		hr = DirectInput8Create(hinstance, DIRECTINPUT_VERSION, IID_IDirectInput8,(void**)&lpdi, NULL);
		if (FAILED(hr)) {	
			switch(hr)
			{
				case DIERR_BETADIRECTINPUTVERSION:
					MessageBox(NULL, "Versio de DirectX BETA,\nadquireixi una nova versió.", "nfo", MB_OK|MB_ICONEXCLAMATION);
					return(false);
				break;
				case DIERR_OLDDIRECTINPUTVERSION:
					MessageBox(NULL, "Versio de DirectX Incorrecta, es recomanar actualitzar", "nfo", MB_OK|MB_ICONEXCLAMATION);
					return(false);
				break;
				case DIERR_INVALIDPARAM:
					MessageBox(NULL, "Parametre incorrecte.", "nfo", MB_OK|MB_ICONSTOP);
					return(false);
				break;
				case DIERR_OUTOFMEMORY:
					MessageBox(NULL, "Sense Memòria.", "nfo", MB_OK|MB_ICONSTOP);
					return(false);
				break;
				default:
					MessageBox(NULL, "No contemplat a la documentació.", "nfo", MB_OK|MB_ICONEXCLAMATION);
					return(false);
				break;
			}	
		}
		return(true);
}
///////////////////////////////////////////////////////////////////////////////////////////////////
void CDirectInput::Main() 
{
	ConcreteMain();
	SendMessage(hwnd, WM_PAINT, 0, 0); // repintem
	return;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
void CDirectInput::ShutDown() 
{
	if (lpdidev)
	{
		lpdidev->Unacquire();
	}
	if (lpdidev)
	{
		lpdidev->Release();
	}
	if (lpdi)
	{
		lpdi->Release();
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void CDirectInput::MoreAxis(GUID type)
{
	neixos++;
	if (type==GUID_ZAxis) 
		estat.hasGUID_ZAxis		= true;			
	if (type==GUID_RxAxis)
		estat.hasGUID_RxAxis	= true;
	if (type==GUID_RyAxis)
		estat.hasGUID_RyAxis	= true;				
	if (type==GUID_RzAxis)
		estat.hasGUID_RzAxis	= true;
	if (type==GUID_Slider) 
		estat.hasGUID_Slider	= true;
	if (type==GUID_POV)
		estat.hasGUID_POV		= true;		
	// Concrete és per si cal afegir alguna funcionalitat a la subclasse
	//ConcreteMoreAxis();
}

void CDirectInput::MoreButtons() 
{
	nbotons++;
	// Concrete és per si cal afegir alguna funcionalitat a la subclasse
	//ConcreteMoreButtons();
}
///////////////////////////////////////////////////////////////////////////////////////////////////
int CDirectInput::GetnBotons() 
{
	return(nbotons);
}
///////////////////////////////////////////////////////////////////////////////////////////////////
int CDirectInput::GetnEixos() 
{

	return(neixos);
}
///////////////////////////////////////////////////////////////////////////////////////////////////
jsmstatus CDirectInput::GetStatus() 
{
	return(estat);
}
///////////////////////////////////////////////////////////////////////////////////////////////////
CDirectInput::CDirectInput(HWND hwnd2, HINSTANCE hinst2)
{
	hwnd		= hwnd2;
	hinstance	= hinst2;
	exclusiu	= false;
	background	= false;
	disp_capt	= false;

	lpdi			= NULL;
	hr				= NULL;	
	nbotons			= 0;
	neixos			= 0;
	estat.b			= NULL;
	/*estat.x			= 0;
	estat.y			= 0;
	estat.z			= 0;*/
	ZeroMemory(&estat,sizeof(estat));
	/*estat.eixpov	= NULL;
	estat.eixslider	= NULL;
	estat.raxis		= NULL;*/
	lpdidev			= NULL;
	Init();
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CDirectInput::~CDirectInput() 
{
	ShutDown(); 
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
