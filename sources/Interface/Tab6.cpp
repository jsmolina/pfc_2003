// Tab6.cpp : implementation file
//

#include "stdafx.h"
#include "tmpConfigDriver.h"
#include "Tab6.h"
#include "head/CurrentStatus.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//extern void Capturar_Dispositiu(int didevice);
extern CCurrentStatus			STATUS_current;
/////////////////////////////////////////////////////////////////////////////
// CTab6 dialog


CTab6::CTab6(CWnd* pParent /*=NULL*/)
	: CDialog(CTab6::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTab6)
	//}}AFX_DATA_INIT
}


void CTab6::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTab6)
	DDX_Control(pDX, IDC_TZ63, m_tz63);
	DDX_Control(pDX, IDC_T66, m_t66);
	DDX_Control(pDX, IDC_T65, m_t65);
	DDX_Control(pDX, IDC_T64, m_t64);
	DDX_Control(pDX, IDC_T62, m_t62);
	DDX_Control(pDX, IDC_T61, m_t61);
	DDX_Control(pDX, IDC_69, m_t69);
	DDX_Control(pDX, IDC_68, m_t68);
	DDX_Control(pDX, IDC_67, m_t67);
	DDX_Control(pDX, IDC_612, m_t612);
	DDX_Control(pDX, IDC_611, m_t611);
	DDX_Control(pDX, IDC_610, m_t610);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTab6, CDialog)
	//{{AFX_MSG_MAP(CTab6)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTab6 message handlers

BOOL CTab6::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here
	m_t61.SetCurSel(0);
	m_t610.SetCurSel(0);
	m_t611.SetCurSel(0);
	m_t612.SetCurSel(0);
	m_t62.SetCurSel(0);
	m_t64.SetCurSel(0);
	m_t65.SetCurSel(0);
	m_t66.SetCurSel(0);
	m_t67.SetCurSel(0);
	m_t68.SetCurSel(0);
	m_t69.SetCurSel(0);
	m_tz63.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
