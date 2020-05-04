// Tab5.cpp : implementation file
//

#include "stdafx.h"
#include "tmpConfigDriver.h"
#include "tmpConfigDriverDlg.h"

#include "Tab5.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTab5 dialog
extern int tmpdev_capt;
extern bool	log_enabled;
extern CTmpConfigDriverDlg *	pctmp; // punter al diàleg


CTab5::CTab5(CWnd* pParent /*=NULL*/)
	: CDialog(CTab5::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTab5)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTab5::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTab5)
	DDX_Control(pDX, IDC_LOGING, m_loging);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTab5, CDialog)
	//{{AFX_MSG_MAP(CTab5)
	ON_BN_CLICKED(IDC_LOGING, OnLoging)
	ON_CBN_SELCHANGE(IDC_HDEV10, OnSelchangeHdev10)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTab5 message handlers

BOOL CTab5::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CComboBox * ccombo = (CComboBox *) GetDlgItem(IDC_HDEV10);
	
	log_enabled = false;
	m_loging.SetCheck(0);


	ccombo->EnableWindow(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTab5::OnLoging() 
{
	// TODO: Add your control notification handler code here
	int v = m_loging.GetCheck();

	CComboBox * ccombo = (CComboBox *) GetDlgItem(IDC_HDEV10);

	if (v==1)
	{
		log_enabled = true;
		ccombo->EnableWindow(TRUE);
	}
	else if (v==0)
	{
		log_enabled = false;
		pctmp->WinPrintf("", IDC_T54, true);
		pctmp->WinPrintf("", IDC_T55, true);
		pctmp->WinPrintf("", IDC_T56, true);
		ccombo->EnableWindow(FALSE);
	}
	//IDC_HDEV10
}

void CTab5::OnSelchangeHdev10() 
{
	// TODO: Add your control notification handler code here
	//IDC_HDEV10

	CComboBox * cc;
	cc = (CComboBox *) GetDescendantWindow(IDC_HDEV10, FALSE);
	tmpdev_capt=cc->GetCurSel();

}
