// tmpConfigDriver.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "tmpConfigDriver.h"
#include "tmpConfigDriverDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CBDades dbase;
extern HWND hwndj;
extern HINSTANCE hinstj;

/////////////////////////////////////////////////////////////////////////////
// CTmpConfigDriverApp

BEGIN_MESSAGE_MAP(CTmpConfigDriverApp, CWinApp)
	//{{AFX_MSG_MAP(CTmpConfigDriverApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTmpConfigDriverApp construction

CTmpConfigDriverApp::CTmpConfigDriverApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CTmpConfigDriverApp object

CTmpConfigDriverApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CTmpConfigDriverApp initialization

BOOL CTmpConfigDriverApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	if (FindLastInstance()) return FALSE;

	CTmpConfigDriverDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

bool CTmpConfigDriverApp::FindLastInstance()
{
	HANDLE hSem = CreateSemaphore(NULL, 1, 1, m_pszExeName);

	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		CloseHandle(hSem);
		HWND hWndPrevious = GetWindow(GetDesktopWindow(), GW_CHILD);

		while (IsWindow(hWndPrevious))
		{
			// The following line should be added to OnInitDialog()
			// for GetProp() to work:
			//      SetProp(AfxGetApp()->m_pMainWnd->m_hWnd, AfxGetApp()->m_pszExeName, (HANDLE)1234);

			if (GetProp(hWndPrevious, m_pszExeName))
			{
				if (IsIconic(hWndPrevious))
					ShowWindow(hWndPrevious, SW_RESTORE);

				SetForegroundWindow(hWndPrevious);
				SetForegroundWindow(GetLastActivePopup(hWndPrevious));

				return true;
			}
			
			hWndPrevious = GetWindow(hWndPrevious, GW_HWNDNEXT);
		}

		return true;
	}

	return false;
}

int CTmpConfigDriverApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CWinApp::ExitInstance();
}

