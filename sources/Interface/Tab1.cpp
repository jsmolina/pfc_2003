// Tab1.cpp : implementation file
//

#include "stdafx.h"
#include "tmpConfigDriver.h"
#include "Tab1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MAX_AXIS	6
#define MAX_BUTTONS 14
/////////////////////////////////////////////////////////////////////////////
// CTab1 dialog


CTab1::CTab1(CWnd* pParent /*=NULL*/)
	: CDialog(CTab1::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTab1)
	//}}AFX_DATA_INIT
}


void CTab1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTab1)
	DDX_Control(pDX, IDC_T20, m_t22);
	DDX_Control(pDX, IDC_T19, m_t21);
	DDX_Control(pDX, IDC_T18, m_t20);
	DDX_Control(pDX, IDC_SPIN2, m_t19);
	DDX_Control(pDX, IDC_SPIN1, m_t18);
	DDX_Control(pDX, IDC_T16, m_t16);
	DDX_Control(pDX, IDC_T17, m_t17);
	DDX_Control(pDX, IDC_T15, m_t15);
	DDX_Control(pDX, IDC_T14, m_t14);
	DDX_Control(pDX, IDC_T13, m_t13);
	DDX_Control(pDX, IDC_T12, m_t12);
	DDX_Control(pDX, IDC_T11, m_t11);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTab1, CDialog)
	//{{AFX_MSG_MAP(CTab1)
	ON_BN_CLICKED(IDC_BDEFAULTS, OnBdefaults)
	ON_CBN_SELCHANGE(IDC_T12, OnSelchangeT12)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, OnDeltaposSpin1)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN2, OnDeltaposSpin2)
	ON_EN_CHANGE(IDC_T15, OnChangeT15)
	ON_EN_CHANGE(IDC_T16, OnChangeT16)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTab1 message handlers

void CTab1::OnBdefaults() 
{
	// TODO: Add your control notification handler code here
	
	if(AfxMessageBox("Are you sure to set defaults for this tab?",  MB_YESNO|MB_ICONQUESTION)==IDYES )
	{
		ModeDefecte();
	}
}
//////////////////////////////////////
void CTab1::ModeNormal()
{	
		// DEFAULT TEXT VALUES
		// buddy text spin 1		
		m_t15.SetWindowText("6");
		// buddy text spin 2		
		m_t16.SetWindowText("12");
		// info BIOS		
		m_t11.SetWindowText("Firm: \"1 Spaceball 4000 FLX\n\"2 B:13 L PnP:0 Az:1 Sns:C 2710 14\n\"3 V0.24 created on Feb 1 1999\n\"4 Copyright(C) 1999 Spacetec IMC Corpo");
		// major version		
		m_t13.SetWindowText("2012504036");
		// minor version
		m_t14.SetWindowText("3");
	// CAN BEEP?
	m_t17.SetCheck(1);
	// SPIN1 INITIALITZATION
	m_t18.SetBase(10);
	m_t18.SetRange32(1,MAX_AXIS);
	m_t18.SetPos(6);
	// SPIN2 INITIALITZATION
	m_t19.SetBase(10);
	m_t19.SetRange32(1,MAX_BUTTONS);
	m_t19.SetPos(12);

/*	m_t11.EnableWindow(FALSE);
	//m_t12.EnableWindow(FALSE); no es toca, és la combo
	m_t13.EnableWindow(FALSE);
	m_t14.EnableWindow(FALSE);
	m_t15.EnableWindow(FALSE);
	m_t16.EnableWindow(FALSE);
	m_t17.EnableWindow(FALSE);
	m_t18.EnableWindow(FALSE);
	m_t19.EnableWindow(FALSE);
	m_t20.EnableWindow(FALSE);*/
}
/////////////////////////////////////////
void CTab1::ModePersonalitzat()
{
	m_t11.EnableWindow(TRUE);
	//m_t12.EnableWindow(FALSE); no es toca, és la combo
	m_t13.EnableWindow(TRUE);
	m_t14.EnableWindow(TRUE);
	m_t15.EnableWindow(TRUE);
	m_t16.EnableWindow(TRUE);
	m_t17.EnableWindow(TRUE);
	m_t18.EnableWindow(TRUE);
	m_t19.EnableWindow(TRUE);
	m_t20.EnableWindow(TRUE);
}
/////////////////////////////////////////////
void CTab1::ModeDefecte()
{
	// COMBO DEFAULTS
	m_t12.SetCurSel(12);
	
	m_t18.SetBuddy((CWnd*) &m_t15);	
	m_t19.SetBuddy((CWnd*) &m_t16);
	m_t21.SetWindowText("9");
	m_t22.SetWindowText("5");
	ModeNormal();
	OnSelchangeT12();

}
///////////////////////////////////////

BOOL CTab1::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// COMBO DEFAULTS
	m_t12.SetCurSel(12);
	
	m_t18.SetBuddy((CWnd*) &m_t15);	
	m_t19.SetBuddy((CWnd*) &m_t16);
	m_t20.SetWindowText("SPACEBALL 4000");
	m_t21.SetWindowText("9");
	m_t22.SetWindowText("5");
	ModeNormal();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTab1::OnSelchangeT12() 
{
	// TODO: Add your control notification handler code here
	register int n;
	register int total;
	CComboBox * pCombo = (CComboBox *) GetDlgItem(IDC_T12);
	total=pCombo->GetCount();
	if (total <=0) return;
	n=pCombo->GetCurSel();

   switch(n)
   {
   case 0:
	   m_t20.SetWindowText("SPACEBALL 2003\0");	   
	   ModeNormal();
	   break;
   case 1:
	   m_t20.SetWindowText("SPACEBALL 3003\0");
   	   ModeNormal();
	   break;
   case 2:		
		m_t20.SetWindowText("SPACE CONTROLLER\0");
	   ModeNormal();
	break;
   case 3:
	   m_t20.SetWindowText("AVENGER\0");
	   ModeNormal();
	break;
   case 4:		
  		m_t20.SetWindowText("SPACEORB 360\0");
	   ModeNormal();
	break;
   case 5:		
	   	m_t20.SetWindowText("NAVIGATOR\0");	
		ModeNormal();
	break;
   case 6:		
		m_t20.SetWindowText("SPACEBALL 2003A\0");
		ModeNormal();
	break;
   case 7:		
		m_t20.SetWindowText("SPACEBALL 2003B\0");
		ModeNormal();
	break;
   case 8:		
		m_t20.SetWindowText("SPACEBALL 2003C\0");
		ModeNormal();
	break;
   case 9:		
		m_t20.SetWindowText("SPACEBALL 3003A\0");
		ModeNormal();
	break;
   case 10:		
		m_t20.SetWindowText("SPACEBALL 3003B\0");
		ModeNormal();
	break;  
   case 11:		
		m_t20.SetWindowText("SPACEBALL 3003C\0");
		ModeNormal();
	break;
   case 12:		
		m_t20.SetWindowText("SPACEBALL 4000\0");
		ModeNormal();
	break;
   case 13:
		m_t20.SetWindowText("SPACEMOUSE CLASSIC\0");
		ModeNormal();
	break;
   case 14:
		m_t20.SetWindowText("SPACEMOUSE PLUS\0");
		ModeNormal();
	break;
   case 15:
		m_t20.SetWindowText("SPACEMOUSE XT\0");
		ModeNormal();
	break;
   case 16:
		m_t20.SetWindowText("PUCKMAN\0");
		ModeNormal();
	break;
   case 17:
		m_t20.SetWindowText("CADMAN\0");
		ModeNormal();
	break;
   case 18:
		m_t20.SetWindowText("SPECIAL DEVICE");
		ModePersonalitzat();
	break;
	
   }   
	// n va de 0 a 18, y el 18 es el personalizado
}

void CTab1::OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	char * result=new char[4];
	sprintf(result, "%d", m_t18.GetPos()-65536);	
	m_t15.SetWindowText(result);
	delete result;
	*pResult = 0;
}

void CTab1::OnDeltaposSpin2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	char * result=new char[4];
	sprintf(result, "%d", m_t19.GetPos()-65536);	
	m_t16.SetWindowText(result);
	delete result;
	*pResult = 0;
}
void CTab1::OnChangeT15() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	CEdit c;
	CString cs;
	
	m_t15.GetWindowText(cs);
	// TODO: Add your control notification handler code here
	if (atoi(cs)>MAX_AXIS) {
		cs.Format("%d", MAX_AXIS);
		m_t15.SetWindowText(cs);
	}
	if (atoi(cs)<= 0) {
		cs.Format("1");
		m_t15.SetWindowText(cs);
	}
	//MessageBox("Changed t15");
}

void CTab1::OnChangeT16() 
{
	CEdit c;
	CString cs;
	
	m_t16.GetWindowText(cs);
	// TODO: Add your control notification handler code here
	if (atoi(cs)>MAX_BUTTONS) {
		cs.Format("%d", MAX_BUTTONS);
		m_t16.SetWindowText(cs);
	}
	if (atoi(cs)<= 0) {
		cs.Format("1");
		m_t16.SetWindowText(cs);
	}
}
