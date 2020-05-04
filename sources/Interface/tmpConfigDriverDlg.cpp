// tmpConfigDriverDlg.cpp : implementation file
//

#include "stdafx.h"
#include "tmpConfigDriver.h"
#include "tmpConfigDriverDlg.h"
//#include "exports.h" // inclou tots els #includes necessaris 
					 // i la comunicació amb la DLL
// INCLUSIÓ DE LES FINESTRES DE TABS
#include "Tab1.h"
#include "Tab2.h"
#include "Tab3.h"
#include "Tab4.h"
#include "Tab5.h"
#include "Tab6.h"
#include "CurrentStatus.h"
#include <Winuser.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TIMER1 100001
#define ZERO_EVERY 10
//#define delay_timer    80
#define delay_consultar 1000/60

// variables globals
extern CTmpConfigDriverApp theApp; // aplicació global
CBDades dbase; // base de dades global
CFilterDI * cf; // filtre DInput
CTmpConfigDriverDlg *	pctmp; // punter al diàleg
// Handles de la aplicació MFC
HWND					hwndj;
HINSTANCE				hinstj;
// Flags
bool					di_init=false;
bool					appreg = false;
bool					log_enabled=true;
int						tmpdev_capt=0;
// estat del dispositiu Emulat
CCurrentStatus			STATUS_last;
CCurrentStatus			STATUS_current;
// handle de la darrera finestra vàlida
HWND					handle_darrera=NULL;
// variable per rebre informació sobre quina finestra està rebent les dades
char buffer_fore[255];
// Id missatge a registrar

// funcions globals
void CALLBACK EXPORT TimerProc(HWND hWnd,UINT nMsg,UINT nIDEvent, DWORD dwTime); // per consultar DirectInput
void CALLBACK EXPORT Consultar_Registres(HWND hWnd,UINT nMsg,UINT nIDEvent, DWORD dwTime); // per consultar entrada externa
void Capturar_Dispositiu(int didevice);
HWND  WinMain2();
void PrintDeviceStatus(CDirectInput ** pDI, register int i, bool clr);



/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About


class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTmpConfigDriverDlg dialog

CTmpConfigDriverDlg::CTmpConfigDriverDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTmpConfigDriverDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTmpConfigDriverDlg)
	m_editor = _T("");
	m_ontop = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTmpConfigDriverDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTmpConfigDriverDlg)
	DDX_Control(pDX, IDC_TAB1, m_tabcontrol);
	DDX_Text(pDX, IDC_EDIT1, m_editor);
	DDX_Check(pDX, IDC_CHECK1, m_ontop);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTmpConfigDriverDlg, CDialog)
	//{{AFX_MSG_MAP(CTmpConfigDriverDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, OnSelchangeTab1)
	ON_NOTIFY(TCN_SELCHANGING, IDC_TAB1, OnSelchangingTab1)
	ON_BN_CLICKED(IDC_CHECK1, OnSetTop)
	ON_BN_CLICKED(IDC_BUTTON2, OnAboutD)
	ON_BN_CLICKED(IDOK2, OnApply)
	ON_BN_CLICKED(IDC_BUTTON32, OnButton32)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTmpConfigDriverDlg message handlers

BOOL CTmpConfigDriverDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
		// obtenim dades internes de la aplicació
		CWnd * cwnd = theApp.GetMainWnd();
		hwndj =  cwnd->GetSafeHwnd();
		hinstj =  theApp.m_hInstance;
	    cf = dbase.GetCFilter();	
		// fer ALWAYS ON TOP:
		m_ontop=TRUE;		
		::SetWindowPos(GetSafeHwnd(), (true) ? HWND_TOPMOST : HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		ConfigTabs();

		m_editor = "Ready.";		
		UpdateData(false);	
		pctmp = this;
		// PER A ACONSEGUIR UNA SOLA INSTÀNCIA!
		SetProp(AfxGetMainWnd()->m_hWnd, AfxGetApp()->m_pszExeName, (HANDLE)1234);
		// Per aconseguir tenir un timer de Consulta de registres
		//::SetTimer(hwndj, TIMER2, delay_timer, TimerProc);
		
		SetTimer(TIMER1, delay_consultar, Consultar_Registres);


		// DLL Initialize
		Initialize();
		// inicialitzem la estructura interna de CSiappmfc
		ExeInit();
		// Initialitzem DirectInput!
		InitDirectInput();
		OnApply();
	/*	lastevent.boto =-1;  lastevent.dispDI=-1;
		lastevent.hwnd =NULL;lastevent.id=-1;
		lastevent.motion=-1; lastevent.rx=-1;
		lastevent.ry=-1;lastevent.rz=-1;
		lastevent.tx=-1;lastevent.ty=-1;
		lastevent.tz=-1;*/

		WinPrintf("[EXE] Initialized - Ready!\r\n");
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTmpConfigDriverDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTmpConfigDriverDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTmpConfigDriverDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
//////////////////////////////////////////////////////////////////
// +és per Debugging i per printar coses lentament
//////////////////////////////////////////////////////////////////
void CTmpConfigDriverDlg::ConfigTabs()
{
	////////////////////////////////////////////////////////////
	////////////////////CREACIO DELS TABS///////////////////////
	////////////////////////////////////////////////////////////
	
	TCITEM tc;
	char szText[100];
	tc.mask = TCIF_TEXT;
	tc.pszText = szText;
	tc.cchTextMax =100;	
	ZeroMemory(&szText, sizeof(char)*100);
	strcat(szText, "Emulated SpaceMouse");
	
	m_tabcontrol.InsertItem(0,&tc);
	ZeroMemory(&szText, sizeof(char)*100);
	strcat(szText, "Axis Map");
	m_tabcontrol.InsertItem(1,&tc);
	
	ZeroMemory(&szText, sizeof(char)*100);
	strcat(szText, "Buttons Map");
	m_tabcontrol.InsertItem(2,&tc);

	ZeroMemory(&szText, sizeof(char)*100);
	strcat(szText, "Axis Variations");
	m_tabcontrol.InsertItem(3,&tc);

	ZeroMemory(&szText, sizeof(char)*100);	
	strcat(szText, "Sensitivity and Filters");
	m_tabcontrol.InsertItem(4,&tc);

	ZeroMemory(&szText, sizeof(char)*100);
	strcat(szText, "Status");
	m_tabcontrol.InsertItem(5,&tc);


	//// PAGE 1
	CTab1 * page1;
	page1 = new CTab1();

	tc.mask=TCIF_PARAM;
	tc.lParam = (LPARAM) page1;
	m_tabcontrol.SetItem(0, &tc);
	page1->Create(IDD_TAB1, &m_tabcontrol);
	page1->SetWindowPos(NULL, 15, 22, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	page1->ShowWindow(SW_SHOW);

	//// PAGE 2
	CTab2 * page2;
	page2 = new CTab2();

	tc.mask=TCIF_PARAM;
	tc.lParam = (LPARAM) page2;
	m_tabcontrol.SetItem(1, &tc);
	page2->Create(IDD_TAB2, &m_tabcontrol);
	page2->SetWindowPos(NULL, 15, 22, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	page2->ShowWindow(SW_HIDE);
	
	//// PAGE 3
	CTab3 * page3;
	page3 = new CTab3();

	tc.mask=TCIF_PARAM;
	tc.lParam = (LPARAM) page3;
	m_tabcontrol.SetItem(2, &tc);
	page3->Create(IDD_TAB3, &m_tabcontrol);
	page3->SetWindowPos(NULL, 15, 22, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	page3->ShowWindow(SW_HIDE);
	
	//// PAGE 4
	CTab6 * page6;
	page6 = new CTab6();

	tc.mask=TCIF_PARAM;
	tc.lParam = (LPARAM) page6;
	m_tabcontrol.SetItem(3, &tc);
	page6->Create(IDD_TAB6, &m_tabcontrol);
	page6->SetWindowPos(NULL, 15, 22, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	page6->ShowWindow(SW_HIDE);

	//// PAGE 5
	CTab4 * page4;
	page4 = new CTab4();

	tc.mask=TCIF_PARAM;
	tc.lParam = (LPARAM) page4;
	m_tabcontrol.SetItem(4, &tc);
	page4->Create(IDD_TAB4, &m_tabcontrol);
	page4->SetWindowPos(NULL, 15, 22, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	page4->ShowWindow(SW_HIDE);
	

	
	//// PAGE 6
	CTab5 * page5;
	page5 = new CTab5();

	tc.mask=TCIF_PARAM;
	tc.lParam = (LPARAM) page5;
	m_tabcontrol.SetItem(5, &tc);
	page5->Create(IDD_TAB5, &m_tabcontrol);
	page5->SetWindowPos(NULL, 15, 22, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	page5->ShowWindow(SW_HIDE);

	//m_tabcontrol
return;
}
////////////////////////////////////////////////////////////////////////

void CTmpConfigDriverDlg::OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult) 
{
    int        iTab = m_tabcontrol.GetCurSel();
    TC_ITEM    tci;
    tci.mask = TCIF_PARAM;
    m_tabcontrol.GetItem(iTab, &tci);
    ASSERT(tci.lParam);
    CWnd* pWnd = (CWnd *)tci.lParam;
    pWnd->ShowWindow(SW_SHOW);	
	
	
	*pResult = 0;
}
//////////////////////////////////////////////////////////////////
void CTmpConfigDriverDlg::OnSelchangingTab1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int        iTab = m_tabcontrol.GetCurSel();
	TC_ITEM    tci;
    tci.mask = TCIF_PARAM;
    m_tabcontrol.GetItem(iTab, &tci);
    ASSERT(tci.lParam);
    CWnd* pWnd = (CWnd *)tci.lParam;
    pWnd->ShowWindow(SW_HIDE);

	*pResult = 0;
}
//////////////////////////////////////////////////////////////////
void CTmpConfigDriverDlg::OnSetTop() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	::SetWindowPos(GetSafeHwnd(), (m_ontop) ? HWND_TOPMOST : HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

}
//////////////////////////////////////////////////////////////////
void CTmpConfigDriverDlg::OnAboutD() 
{
	// TODO: Add your control notification handler code here
	CAboutDlg * ca;
	ca = new CAboutDlg();
	ca->DoModal();
	
}
//////////////////////////////////////////////////////////////////
void CTmpConfigDriverDlg::OnOK() 
{
	// TODO: Add extra validation here
	Terminate();

	CDialog::OnOK();
}
//////////////////////////////////////////////////////////////////
void CTmpConfigDriverDlg::OnApply() 
{
	//CConfiguration * cc = dbase.GetDevConfig();

	TakeDeviceOnGUIConfig();
	Devinfo * d =dbase.GetDevInfo();
	
	STATUS_current.SetNumberButtons(d->botons);
	STATUS_last.SetNumberButtons(d->botons);

}
//////////////////////////////////////////////////////////////////
void CTmpConfigDriverDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	Terminate();
	CDialog::OnCancel();
}
/////////////////////////////////////////////////////////////
void CTmpConfigDriverDlg::WinPrintf(char input[255])
{
	CEdit * ce;
	CString cs;

	ce = static_cast<CEdit *>(GetDescendantWindow(IDC_T56, FALSE));		
	ce->GetWindowText(cs);
	
	cs =  cs+input;
	ce->SetWindowText(cs);
	pctmp->UpdateData(false);
		
	ce->LineScroll(ce->GetLineCount());
}
//////////////////////////////////////////////////////////////////
void CTmpConfigDriverDlg::WinPrintf(char input[255], int nID, bool clrscr)
{
	CEdit * ce;
	CString cs;

	if (nID==IDC_EDIT1) {
		pctmp->m_editor=input;
		pctmp->UpdateData(false);
		return;
	}

	ce = static_cast<CEdit *>(GetDescendantWindow(nID, FALSE));		
	ce->GetWindowText(cs);
	if (clrscr== false)
		cs =  cs+input;
	else 
		cs = input;

	ce->SetWindowText(cs);
	pctmp->UpdateData(false);
		
	ce->LineScroll(ce->GetLineCount());
}

//////////////////////////////////////////////////////////////////
void CTmpConfigDriverDlg::InitDirectInput()
{
	
	CConfiguration * c = dbase.GetDevConfig();
	Devinfo *devinfo  = dbase.GetDevInfo();
	CDirectInput ** d   = dbase.GetDI();
	Device_Selector *d_sel = dbase.GetSelector();
	CComboBox * cc;

	d_sel = new Device_Selector(hwndj, hinstj);
	dbase.SetSelector(d_sel);
	dbase.hinst_exe = hinstj;
	dbase.hwnd_exe  = hwndj;

	if (d_sel==NULL) MessageBox( "Device Selector is NULL.", "ERROR  - InitDirectInput()", MB_OK|MB_ICONEXCLAMATION);
    d_sel->EnumerarDispositius(DI8DEVCLASS_POINTER);
	d_sel->EnumerarDispositius(DI8DEVCLASS_DEVICE);
	d_sel->EnumerarDispositius(DI8DEVCLASS_GAMECTRL);
	// per a cada dispositiu, ficar al TAB6
	//cc = (CComboBox *) GetDescendantWindow(IDC_T61, FALSE);
	register int i;
	for (i = 0; i < d_sel->enumerats; i++)
	{
		Capturar_Dispositiu(i);
	}
//IDC_HDEV10
	cc = (CComboBox *) GetDescendantWindow(IDC_HDEV10, FALSE);	
	for (i = 0; i < d_sel->enumerats; i++)	cc->InsertString(i, d_sel->disp_list[i]);
	cc->SetCurSel(0);

	// per a cada dispositiu, omplir les diferents combo
	//tx
	cc = (CComboBox *) GetDescendantWindow(IDC_T28, FALSE);
	cc->InsertString(0,"(none)");
	for (i = 0; i < d_sel->enumerats; i++)	cc->InsertString(i+1, d_sel->disp_list[i]);
	cc->SetCurSel(0);

	//ty
	cc = (CComboBox *) GetDescendantWindow(IDC_T29, FALSE);
	cc->InsertString(0,"(none)");
	for (i = 0; i < d_sel->enumerats; i++)	cc->InsertString(i+1, d_sel->disp_list[i]);
	cc->SetCurSel(0);

	//tz
	cc = (CComboBox *) GetDescendantWindow(IDC_T210, FALSE);
	cc->InsertString(0,"(none)");
	for (i = 0; i < d_sel->enumerats; i++)	cc->InsertString(i+1, d_sel->disp_list[i]);
	cc->SetCurSel(0);

	//ry
	cc = (CComboBox *) GetDescendantWindow(IDC_T212, FALSE);
	cc->InsertString(0,"(none)");
	for (i = 0; i < d_sel->enumerats; i++)	cc->InsertString(i+1, d_sel->disp_list[i]);
	cc->SetCurSel(0);

	//rx
	//IDC_T211
	cc = (CComboBox *) GetDescendantWindow(IDC_2RX, FALSE);
	cc->InsertString(0,"(none)");
	for (i = 0; i < d_sel->enumerats; i++)	cc->InsertString(i+1, d_sel->disp_list[i]);
	cc->SetCurSel(0);

	//rz
	cc = (CComboBox *) GetDescendantWindow(IDC_T213, FALSE);
	cc->InsertString(0,"(none)");
	for (i = 0; i < d_sel->enumerats; i++)	cc->InsertString(i+1, d_sel->disp_list[i]);
	cc->SetCurSel(0);

	//b1
	cc = (CComboBox *) GetDescendantWindow(IDC_T301, FALSE);
	cc->InsertString(0,"(none)");
	for (i = 0; i < d_sel->enumerats; i++)	cc->InsertString(i+1, d_sel->disp_list[i]);
	cc->SetCurSel(0);

	//b2
	cc = (CComboBox *) GetDescendantWindow(IDC_T302, FALSE);
	cc->InsertString(0,"(none)");
	for (i = 0; i < d_sel->enumerats; i++)	cc->InsertString(i+1, d_sel->disp_list[i]);
	cc->SetCurSel(0);
	
	//b3
	cc = (CComboBox *) GetDescendantWindow(IDC_T303, FALSE);
	cc->InsertString(0,"(none)");
	for (i = 0; i < d_sel->enumerats; i++)	cc->InsertString(i+1, d_sel->disp_list[i]);
	cc->SetCurSel(0);
	
	//b4
	cc = (CComboBox *) GetDescendantWindow(IDC_T304, FALSE);
	cc->InsertString(0,"(none)");
	for (i = 0; i < d_sel->enumerats; i++)	cc->InsertString(i+1, d_sel->disp_list[i]);
	cc->SetCurSel(0);
	
	//b5
	cc = (CComboBox *) GetDescendantWindow(IDC_T305, FALSE);
	cc->InsertString(0,"(none)");
	for (i = 0; i < d_sel->enumerats; i++)	cc->InsertString(i+1, d_sel->disp_list[i]);
	cc->SetCurSel(0);
	
	//b6
	cc = (CComboBox *) GetDescendantWindow(IDC_T306, FALSE);
	cc->InsertString(0,"(none)");
	for (i = 0; i < d_sel->enumerats; i++)	cc->InsertString(i+1, d_sel->disp_list[i]);
	cc->SetCurSel(0);


}

//////////////////////////////////////////////////////////////////
void CTmpConfigDriverDlg::OnButton32() 
{
	// TODO: Add your control notification handler code here
	WinPrintf("", IDC_T54, true);
	WinPrintf("", IDC_T55, true);
	WinPrintf("", IDC_T56, true);
}
//////////////////////////////////////////////////////////////////
void CTmpConfigDriverDlg::TakeDeviceOnGUIConfig()
{
	// obté informació sobre tots els dispositius
	Devinfo		* pDevinfo;
	CEdit		* ce;	
	CButton		* cb;
	CComboBox	* cc;
	CSliderCtrl * cs;
	CString		c;
	int			n=0;
//	int			cursel=-1;
		
	// Reconfigure Device Information	
	pDevinfo = dbase.GetDevInfo();	
		// Get BIOS Data
		ce = static_cast<CEdit *>(GetDescendantWindow(IDC_T11, FALSE));				
		ce->GetWindowText(c);		
		sprintf(pDevinfo->bios, "%s", c);
		// Get Number of buttons selected	
		ce = static_cast<CEdit *>(GetDescendantWindow(IDC_T16, FALSE));
		ce->GetWindowText(c);		
		pDevinfo->botons=atoi(c);
		// User Accepted that may beep?	
		cb = static_cast<CButton *>(GetDescendantWindow(IDC_T17, FALSE));
		if (cb->GetCheck()>=1) pDevinfo->can_beep=true;
		else				   pDevinfo->can_beep=false;	
		// Get Number of axis
		ce = static_cast<CEdit *>(GetDescendantWindow(IDC_T15, FALSE));
		ce->GetWindowText(c);
		pDevinfo->eixos=atoi(c);
		// Get Major version of device
		ce = static_cast<CEdit *>(GetDescendantWindow(IDC_T13, FALSE));
		ce->GetWindowText(c);
		pDevinfo->major=atoi(c);
		// Get Minor version of device
		ce = static_cast<CEdit *>(GetDescendantWindow(IDC_T14, FALSE));
		ce->GetWindowText(c);
		pDevinfo->minor=atoi(c);
		// Get Major version of LIBRARY
		ce = static_cast<CEdit *>(GetDescendantWindow(IDC_T19, FALSE));
		ce->GetWindowText(c);
		pDevinfo->major=atoi(c);
		// Get Minor version of LIBRARY
		ce = static_cast<CEdit *>(GetDescendantWindow(IDC_T20, FALSE));
		ce->GetWindowText(c);
		pDevinfo->major=atoi(c);
		// Put Device String
		ce = static_cast<CEdit *>(GetDescendantWindow(IDC_T20, FALSE));
		ce->GetWindowText(c);
		strcpy(pDevinfo->model_str, c);
		// Get Model VERSION
		cc = static_cast<CComboBox *>(GetDescendantWindow(IDC_T12, FALSE));
		n=cc->GetCount();
		if (n >= 1) 
		{
			n=cc->GetCurSel();
			switch(n)
			{
			case 0:
				pDevinfo->model=SI_SPACEBALL_2003;
				break;
			case 1:
				pDevinfo->model=SI_SPACEBALL_3003;
				break;
			case 2:
				pDevinfo->model=SI_SPACE_CONTROLLER;
				break;
			case 3:
				pDevinfo->model=SI_AVENGER;
				break;
			case 4:
				pDevinfo->model=SI_SPACEORB_360;
				break;
			case 5:
				pDevinfo->model=SI_NAVIGATOR;
				break;
			case 6:
				pDevinfo->model=SI_SPACEBALL_2003A;
				break;
			case 7:
				pDevinfo->model=SI_SPACEBALL_2003B;
				break;
			case 8:
				pDevinfo->model=SI_SPACEBALL_2003C;
				break;
			case 9:
				pDevinfo->model=SI_SPACEBALL_3003A;
				break;
			case 10:
				pDevinfo->model=SI_SPACEBALL_3003B;
				break;
			case 11:
				pDevinfo->model=SI_SPACEBALL_3003C;
				break;
			case 12:
				pDevinfo->model=SI_SPACEBALL_4000;
				break;
			case 13:
				pDevinfo->model=SI_SPACEMOUSE_CLASSIC;
				break;
			case 14:
				pDevinfo->model=SI_SPACEMOUSE_PLUS;
				break;
			case 15:
				pDevinfo->model=SI_SPACEMOUSE_XT;
				break;
			case 16:
				pDevinfo->model=SI_PUCKMAN;
				break;
			case 17:
				pDevinfo->model=SI_CADMAN;
				break;
			case 18:
				pDevinfo->model=0;
				break;
			} // fi switch
		} // fi del if n>0	
	///////////////////////////////////////////////////////
	// CONFIGURACIO DEL DISPOSITIU VIRTUAL (MAPEJOS, ...)//
	///////////////////////////////////////////////////////
	CConfiguration * pConfig = dbase.GetDevConfig();
		//         Selecció de configuració i mapeig        //
	//IDC_T415	
	// actuació del beep
	cb = static_cast<CButton *>(GetDescendantWindow(IDC_T415, FALSE));
		if(cb->GetCheck()>=1) pConfig->beep_act = true;
		else				pConfig->beep_act = false;
	// filtre del eix dominant
	cb = static_cast<CButton *>(GetDescendantWindow(IDC_T45, FALSE));
		if(cb->GetCheck()>=1) pConfig->hFilt_eixdominant = true;
		else				pConfig->hFilt_eixdominant = false;
	// habilitades rotacions
	cb = static_cast<CButton *>(GetDescendantWindow(IDC_T411, FALSE));
		if(cb->GetCheck()>=1) pConfig->hRotacions = true;
		else				pConfig->hRotacions = false;
	cb = static_cast<CButton *>(GetDescendantWindow(IDC_T47, FALSE));
		if(cb->GetCheck()>=1) pConfig->hTraslacions = true;
		else				pConfig->hTraslacions = false;		
	// panoramitzar (panning)
	cs = static_cast<CSliderCtrl *>(GetDescendantWindow(IDC_T42, FALSE));	
		pConfig->panoramitzar=cs->GetPos(); 
	// rotacions
	cs = static_cast<CSliderCtrl *>(GetDescendantWindow(IDC_T43, FALSE));	
		pConfig->rotacions=cs->GetPos(); 
	// zooming
	cs = static_cast<CSliderCtrl *>(GetDescendantWindow(IDC_T44, FALSE));	
		pConfig->zooming=cs->GetPos(); 
	// sensibilitat
	cs = static_cast<CSliderCtrl *>(GetDescendantWindow(IDC_T41, FALSE));	
		pConfig->sensibilitat=cs->GetPos(); 		
	// rx activat
	cb = static_cast<CButton *>(GetDescendantWindow(IDC_T412, FALSE));
		if(cb->GetCheck()>=1) pConfig->rx = true;
		else				pConfig->rx = false;		
	// ry activat
	cb = static_cast<CButton *>(GetDescendantWindow(IDC_T413, FALSE));
		if(cb->GetCheck()>=1) pConfig->ry = true;
		else				pConfig->ry = false;		
	// rz activat
	cb = static_cast<CButton *>(GetDescendantWindow(IDC_T414, FALSE));
		if(cb->GetCheck()>=1) pConfig->rz = true;
		else				pConfig->rz = false;
	// tx activat
	cb = static_cast<CButton *>(GetDescendantWindow(IDC_T48, FALSE));
		if(cb->GetCheck()>=1) pConfig->tx = true;
		else				pConfig->tx = false;		
	// ty activat
	cb = static_cast<CButton *>(GetDescendantWindow(IDC_T49, FALSE));
		if(cb->GetCheck()>=1) pConfig->ty = true;
		else				pConfig->ty = false;		
	// tz activat
	cb = static_cast<CButton *>(GetDescendantWindow(IDC_T410, FALSE));
		if(cb->GetCheck()>=1) pConfig->tz = true;
		else				pConfig->tz = false;		
	// intercanvi y-z activat
	cb = static_cast<CButton *>(GetDescendantWindow(IDC_T46, FALSE));
		if(cb->GetCheck()>=1) pConfig->y_z_int = true;
		else				pConfig->y_z_int = false;		
		
	/* ARA ES MANUAL - caldrà rebre de cada combo la informació*/
	/////////////////////////////////////////////////
		//        Selecció de mapejos        //
	/////////////////////////////////////////////////		
///////
	/*************************************************/
	////////////////////////////////////////////////////////
	AsignBotons * ab = &(pConfig->theAsignBotons);
	ab->Reset();
	GetConfig(0, IDC_T301,  IDC_T313);
	GetConfig(1, IDC_T302,  IDC_T314);
	GetConfig(2, IDC_T303,  IDC_T315);
	GetConfig(3, IDC_T304,  IDC_T316);
	GetConfig(4, IDC_T305,  IDC_T317);
	GetConfig(5, IDC_T306,  IDC_T318);
	/*************************************************/
	////////////////////////////////////////////////////////
	AsignEixos * e = &(pConfig->theAsignEixos);
	e->Reset();
	GetAxisConfig(SI_TX, IDC_T28, IDC_T214);
	GetAxisConfig(SI_TY, IDC_T29, IDC_T215);
	GetAxisConfig(SI_TZ, IDC_T210, IDC_T216);
	GetAxisConfig(SI_RX, IDC_2RX, IDC_T217);
	GetAxisConfig(SI_RY, IDC_T212, IDC_T218);
	GetAxisConfig(SI_RZ, IDC_T213, IDC_T219);
	/*************************************************/
	////////////////////////////////////////////////////////
	/*char buf[50];*/
	
	/*sprintf(buf, "CCB=%d", ccb->GetCurSel());
	MessageBox(buf);*/

	AsignEspecials * es = &(pConfig->theAsignEspecials);
	es->Reset();	

	CComboBox * ccb = (CComboBox *) GetDescendantWindow(IDC_T61);
	CComboBox * ccb2 = (CComboBox *) GetDescendantWindow(IDC_67);
	if (ccb==NULL || ccb2==NULL) MessageBox("Failed while trying to have access to combobox");
	
	GetAsEspecialsConfig(SI_TX, ccb, ccb2);
	//////////////
	ccb = (CComboBox *) GetDescendantWindow(IDC_T62);
	ccb2 = (CComboBox *) GetDescendantWindow(IDC_68);
	if (ccb==NULL || ccb2==NULL) MessageBox("Failed while trying to have access to combobox");
	
	GetAsEspecialsConfig(SI_TY, ccb, ccb2);	
	//////////////
	ccb = (CComboBox *) GetDescendantWindow(IDC_TZ63);
	ccb2 = (CComboBox *) GetDescendantWindow(IDC_69);
	if (ccb==NULL || ccb2==NULL) MessageBox("Failed while trying to have access to combobox");
	
	GetAsEspecialsConfig(SI_TZ, ccb, ccb2);	
	//////////////
	ccb = (CComboBox *) GetDescendantWindow(IDC_T64);
	ccb2 = (CComboBox *) GetDescendantWindow(IDC_610);
	if (ccb==NULL || ccb2==NULL) MessageBox("Failed while trying to have access to combobox");
	
	GetAsEspecialsConfig(SI_RX, ccb, ccb2);	
	//////////////
	ccb = (CComboBox *) GetDescendantWindow(IDC_T65);
	ccb2 = (CComboBox *) GetDescendantWindow(IDC_611);
	if (ccb==NULL || ccb2==NULL) MessageBox("Failed while trying to have access to combobox");
	
	GetAsEspecialsConfig(SI_RY, ccb, ccb2);	
	//////////////
	ccb = (CComboBox *) GetDescendantWindow(IDC_T66);
	ccb2 = (CComboBox *) GetDescendantWindow(IDC_612);
	if (ccb==NULL || ccb2==NULL) MessageBox("Failed while trying to have access to combobox");
	
	GetAsEspecialsConfig(SI_RZ, ccb, ccb2);	

	///////////////////////////////////////////////////////
	/*AsignEspecials	*aes = &(pConfig->theAsignEspecials);
			Asignacio * a = new Asignacio();
				a->boto_modificador=1;
				a->eixSP_inicial=SI_TX;
				a->eixSP_final=SI_TY;								
			aes->Add(a);*/
			//aes->
	// cridem a la DLL wrapper per avisar sobre el canvi
	ChangeConfig(pDevinfo);
	// fem feedback cap a l'usuari
	WinPrintf("Device Information and Configuration succesfully changed", IDC_EDIT1, true);
}
//////////////////////////////////////////////////////////////////
void CTmpConfigDriverDlg::GetConfig(int SP_BUTTON, int ID_CDI, int ID_CBU)
{
	CComboBox	* cc;
	int n;
	int cursel;
	char buff[50];
	CConfiguration * pConfig = dbase.GetDevConfig();
	AsignBotons		*ab = &(pConfig->theAsignBotons);
	if ((SP_BUTTON==-1) || (ID_CDI==-1) || (ID_CBU==-1)) return;

	cc=static_cast<CComboBox *>(GetDescendantWindow(ID_CBU, FALSE));
	n		= cc->GetCount();
	cursel	= cc->GetCurSel();
	if (cursel <0) return;
	cc=static_cast<CComboBox *>(GetDescendantWindow(ID_CDI, FALSE));
	if ((n >0) && (cc->GetCurSel()>0))
	{
		Boto * b = new Boto();
		b->botoDI=cursel;
		b->botoSP=SP_BUTTON;
		b->dispDI=cc->GetCurSel() - 1;
		if (b->botoDI==-1 || b->botoSP==-1 || b->dispDI==-1)
		{
			delete b;
			return;
		}
		ab->Add(b);				
		
		sprintf(buff, "botoDI=%d botoSP=%d dispDI=%d\r\n", b->botoDI, b->botoSP, b->dispDI);
		WinPrintf(buff);
	}

}
//////////////////////////////////////////////////////////////////
void CTmpConfigDriverDlg::GetAxisConfig(int SP_AXIS, int ID_CDI, int ID_CAX)
{
	int		n;
	int		cursel;
	CComboBox		* cc;
	CConfiguration	* pConfig = dbase.GetDevConfig();
	AsignEixos		* ae = &(pConfig->theAsignEixos);

	if (SP_AXIS< 0 || ID_CDI < 0 || ID_CAX < 0) return;
	cc=static_cast<CComboBox *>(GetDescendantWindow(ID_CAX, FALSE));
	n		= cc->GetCount();
	cursel	= cc->GetItemData(cc->GetCurSel());
	if (cursel <0) return;
/*char buf[50];
sprintf(buf, "Cursel=%d", cursel);
MessageBox(buf);*/
	cc=static_cast<CComboBox *>(GetDescendantWindow(ID_CDI, FALSE));
	if ((n >0) && (cc->GetCurSel()>0))
	{
		Eix * e = new Eix();
			e->dispDI=cc->GetCurSel()-1;
			e->eixDI=cursel;
			e->eixSP=SP_AXIS;	
			if (e->dispDI < 0) return;
		ae->Add(e);
	}
}
//////////////////////////////////////////////////////////////////
void CTmpConfigDriverDlg::GetAsEspecialsConfig(int SP_AXIS, CComboBox * cc_boto, CComboBox * cc_eixfin)
{
	if (cc_boto==NULL || cc_eixfin==NULL) {
		MessageBox("Refused by NULL on input");
		return;
	}
	int		curboto=cc_boto->GetCurSel();
	int		cureix=cc_eixfin->GetCurSel();

	if (curboto<=0) { return;}
	if (cureix<=0) { return;}
	Asignacio * a = new Asignacio();
	a->boto_modificador= cc_boto->GetCurSel()-1;
	a->eixSP_inicial   = SP_AXIS;
	a->eixSP_final     = cureix-1;

	CConfiguration	* pConfig = dbase.GetDevConfig();
	AsignEspecials	* ae = &(pConfig->theAsignEspecials);

	ae->Add(a);
	
/*	char buffer[50];
	sprintf(buffer, "modific=%d inicial=%d  final=%d", a->boto_modificador, a->eixSP_inicial, a->eixSP_final);
	MessageBox(buffer);*/
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
void PrintDeviceStatus(CDirectInput ** pDI, register int i, bool clr)
{
	if (log_enabled==false) return;
	if (i != tmpdev_capt) return;
	if (di_init==false) return;
	//TextOut(hdc, 20, d_sel->posy, "Valors:", 7);	
	char  * buffer;
	char  tmp[255];
	register int j;
	jsmstatus *st;
 
	buffer = new char[512];		
		if (pDI[i]==NULL) pctmp->WinPrintf("pDI NULL in PrintDeviceStatus\r\n");
	
	st=pDI[i]->GetStatus();


	// pels eixos	
	sprintf(buffer, " X=%d Y=%d\r\n", st->x, st->y);
	// si té més d'un eix
	if (pDI[i]->GetnEixos() > 2) { // tenim més de 3 eixos
		if (st->hasGUID_ZAxis) {
			sprintf(tmp, " Z=%d\r\n", st->z);
			strcat(buffer, tmp);
		}
		// els eixos de rotació
		if (st->hasGUID_RxAxis) {
			sprintf(tmp, " Rx=%d", st->raxis[0]);
			strcat(buffer, tmp);
		}
		if (st->hasGUID_RyAxis) {
			sprintf(tmp, " Ry=%d", st->raxis[1]);
			strcat(buffer, tmp);
		}
		if (st->hasGUID_RzAxis) {
			sprintf(tmp, " Rz=%d\r\n", st->raxis[2]);
			strcat(buffer, tmp);
		}
		// els eixos de slider		
		if (st->hasGUID_Slider) {
			sprintf(tmp, " SliderX=%d SliderY=%d\r\n", st->raxis[0], st->raxis[1]);
			strcat(buffer, tmp);
		}
		if (st->hasGUID_POV) {			
			sprintf(tmp, " POV1=%d POV2=%d POV3=%d POV4=%d\r\n", st->eixpov[0], st->eixpov[1], st->eixpov[2], st->eixpov[3]);
			strcat(buffer, tmp);
		}		
	}
	// pels botons
	
	for ( j = 0; j < pDI[i]->GetnBotons(); j++)
	{
		sprintf(tmp, " B%d=%d \r\n", j, st->b[j]);
		strcat(buffer, tmp);
	}
	pctmp->WinPrintf(buffer, IDC_T55, clr);
	//TextOut(hdc, 25, d_sel->posy, buffer, strlen(buffer));
	delete buffer;
	//return(buffer);
	
}



void CALLBACK EXPORT TimerProc(HWND hWnd,UINT nMsg,UINT nIDEvent, DWORD dwTime)
{	
	int num=0;
	char buffer[40];

	

	CDirectInput ** cd =dbase.GetDI(); // recupera punter a DirectInput
	Device_Selector * ds = dbase.GetSelector();	
	register int i;
if (log_enabled==true)
{
	pctmp->WinPrintf(" ", IDC_T55, true);
}
	for (i = 0; i < ds->enumerats; i++)
	{
		if (ds->seleccionats[i])
		{
			cd[i]->Main();
			if (log_enabled==true)
			{
				// nom
				sprintf(buffer, "%s\r\n", ds->disp_list[i]);
				pctmp->WinPrintf(buffer, IDC_T55, false);
				// eixos i botons
				PrintDeviceStatus(cd, i, false);// 0-1º, 1-2º, ...
			}
		}
	}
}
//////////////////////////////////////////////////////////////////
// TIMER per recuperar paràmetres de funcions ràpidament
void CALLBACK EXPORT Consultar_Registres(HWND hWnd,UINT nMsg,UINT nIDEvent, DWORD dwTime)
{
/*	if (IsNewLog()) {
	//	MessageBox(NULL, "New LOG", "OK", MB_OK);
		pctmp->WinPrintf(GetLogBuffer());
	}	*/
	char buf[1024];
	if (IsNewRegister()) 
	{	
		Window_Handles * wh = dbase.GetWindowHandles();
		HWND hwnd_registrat;
		hwnd_registrat = GetApp();

		wh->Add(hwnd_registrat);
			char buf[1024];
			sprintf(buf, "[%x] New Window Registered\r\n", hwnd_registrat);
			pctmp->WinPrintf(buf);		
		appreg=true;
	}

	if(IsNewUnRegister())
	{
		Window_Handles * wh = dbase.GetWindowHandles();
		HWND hwnd_desregistrat;
		hwnd_desregistrat = GetUnApp();
		if (hwnd_desregistrat == handle_darrera) handle_darrera=NULL;
		if (wh->Remove(hwnd_desregistrat))
			sprintf(buf, "--[%x] Window UNRegistered\r\n", hwnd_desregistrat);
		else 
			sprintf(buf, "**ERROR** Window Can't be UNRegistered\r\n");
		pctmp->WinPrintf(buf);		
		if(wh->count<=0) 
		{
			pctmp->WinPrintf("-0 windows registered\r\n");
			appreg=false;
		}
	}

	TimerProc(NULL,0,0,0);

	if (appreg==true) 
	{
		HWND hwnd = WinMain2(); // crida al MAIN
	}

}

//////////////////////////////////////////////////////////////////
HWND  WinMain2()
{
	/* a) executar Main DirectInput
	   b) filtrar  només missatges 'interessants'
	   c) veure quina finestra té el focus
	   d) Insertar event a la cua (si el hwnd de la finestra estava registrat)
	   e) retornar el HWND
	*/
	//pCDirectInput
	
	register int i;
	Device_Selector * devsel = dbase.GetSelector();
	CDirectInput    ** direct = dbase.GetDI();
	HWND    hw_tosend;
	char buf[1024];
	char tmp[20];
	jsmstatus *st;
	bool mo=false;;
	STATUS_current.changed=true;
	
	for (i =0; i < STATUS_current.GetNumberButtons(); i++)
	{
		STATUS_current.bpr_array[i]=0;
	}
	
	for (i = 0; i < devsel->enumerats; i++)
	{
		if ((direct[i] != NULL)) 
		{			
			if (devsel->seleccionats[i]) 
			{
				st = NULL;
				st = direct[i]->GetStatus();
				if (st==NULL) PostQuitMessage(1);
				// if IsEnqueueable
				if (cf->IsEnqueueable(i, direct[i]->GetnBotons(), st, hw_tosend))			
					cf->JsmstatusToStatus(st, direct[i]->GetnEixos(), direct[i]->GetnBotons(), i);
			
				
			} // if seleccionats[i]
		} // if direct[i]!=NULL		
	} // for all enumerats


	// ara ja tinc el estat del dispositiu emulat, ara serà quan
	// tregui zones mortes, comparar amb l'anterior, etc, etc
		cf->FilterDeadZone();
		cf->MapToConfiguration();
		//comparar amb l'anterior, si és igual, no dir res, i no 
		//generar CAP event
	
		switch(cf->CompareGenerateAndSend())
		{	
		case 1:			
			if (log_enabled==true) pctmp->WinPrintf("-Move event.\r\n");

			break;
		case 2:
			if (log_enabled==true) pctmp->WinPrintf("-Zero (stop move) event.\r\n");
			break;
		case 3:
			if (log_enabled==true) pctmp->WinPrintf("-Button PUSH event.\r\n");
			break;
		case 4:
			if (log_enabled==true) pctmp->WinPrintf("-Button RELEASE event.\r\n");
			break;
		}
		
		if (log_enabled==false) return(hw_tosend);
		////////// VIRTUAL DEVICE LOG STATUS //////////////
		pctmp->WinPrintf(buffer_fore, IDC_T54, true);
		CComboBox * ccom;
		ccom = static_cast<CComboBox *>(pctmp->GetDescendantWindow(IDC_T12, FALSE));				
		i=ccom->GetCurSel();
		ccom->GetLBText(i, buf);
		pctmp->WinPrintf(buf, IDC_T54, false);
		// AXIS STATUS
		sprintf(buf, "\r\n-STATUS\r\nTX=%d\r\nTY=%d\r\nTZ=%d\r\n", STATUS_current.tx, STATUS_current.ty, STATUS_current.tz);
		// BUTTONS STATUS
		for (i = 0; i < STATUS_current.GetNumberButtons(); i++)
		{
			if (STATUS_current.bpr_array[i]==1)
			{
				sprintf(tmp, "B%d:%d\r\n", i+1, STATUS_current.bpr_array[i]);
				strcat(buf, tmp);
			}
		}
		pctmp->WinPrintf(buf, IDC_T54, false);

	return (hw_tosend);	
}

//////////////////////////////////////////////////////////////////
void Capturar_Dispositiu(int didevice)
{
//	tmpdev_capt=didevice;
	//////////////////////////////////////////////////
	//			Inicialització del DirectInput      //
	//////////////////////////////////////////////////
	Device_Selector * d_sel = dbase.GetSelector();
	CDirectInput    ** di;
	
	d_sel->seleccionats[didevice]=true;
	if (log_enabled==true) 
	{
		char buffer[50];
		sprintf(buffer, "-Captured: %s\r\n", d_sel->disp_list[didevice]);
		pctmp->WinPrintf(buffer);
	}
	
	di = dbase.GetDI();
	if (d_sel->dtype[didevice] ==JOYSTICK) {	
		di[didevice] = new CDInputJoystick(dbase.hwnd_exe, dbase.hinst_exe);
		di[didevice]->Create_Device(d_sel->guid_list[didevice], DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);
	}
	if (d_sel->dtype[didevice] ==RATOLI) {
		di[didevice] = new CDInputMouse(dbase.hwnd_exe, dbase.hinst_exe);
		di[didevice]->Create_Device(d_sel->guid_list[didevice],DISCL_BACKGROUND| DISCL_NONEXCLUSIVE);
	}
	d_sel->seleccionats[didevice]=true;
	
di_init=true;

}
