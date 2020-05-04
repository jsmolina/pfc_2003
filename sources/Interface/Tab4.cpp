// Tab4.cpp : implementation file
//

#include "stdafx.h"
#include "tmpConfigDriver.h"
#include "Tab4.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTab4 dialog


CTab4::CTab4(CWnd* pParent /*=NULL*/)
	: CDialog(CTab4::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTab4)
	//}}AFX_DATA_INIT
}


void CTab4::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTab4)
	DDX_Control(pDX, IDC_T45, m_t45);
	DDX_Control(pDX, IDC_T414, m_t414);
	DDX_Control(pDX, IDC_T49, m_t49);
	DDX_Control(pDX, IDC_T48, m_t48);
	DDX_Control(pDX, IDC_T47, m_t47);
	DDX_Control(pDX, IDC_T46, m_t46);
	DDX_Control(pDX, IDC_T44, m_t44);
	DDX_Control(pDX, IDC_T43, m_t43);
	DDX_Control(pDX, IDC_T413, m_t413);
	DDX_Control(pDX, IDC_T42, m_t42);
	DDX_Control(pDX, IDC_T412, m_t412);
	DDX_Control(pDX, IDC_T415, m_t415);
	DDX_Control(pDX, IDC_T411, m_t411);
	DDX_Control(pDX, IDC_T410, m_t410);
	DDX_Control(pDX, IDC_T41, m_t41);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTab4, CDialog)
	//{{AFX_MSG_MAP(CTab4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTab4 message handlers

BOOL CTab4::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	// PER ELS CONTROLS DE SENSIBILITAT GLOBAL
	m_t41.SetRange(0,100,FALSE);
	m_t41.SetTicFreq( 10 );
	m_t41.SetLineSize(10);
	m_t41.SetPageSize(25);
	m_t41.SetPos(50);
	
	// PANORAMITZAR; ZOOM, ...
	m_t42.SetRange(0,100,FALSE);
	m_t42.SetTicFreq( 10 );
	m_t42.SetLineSize(10);
	m_t42.SetPageSize(25);
	m_t42.SetPos(50);
	m_t43.SetRange(0,100,FALSE);
	m_t43.SetLineSize(10);
	m_t43.SetTicFreq( 10 );
	m_t43.SetPageSize(25);
	m_t43.SetPos(50);
	m_t44.SetRange(0,100,FALSE);
	m_t44.SetLineSize(10);
	m_t44.SetTicFreq( 10 );
	m_t44.SetPageSize(25);
	m_t44.SetPos(50);
	//checkboxes
	m_t45.SetCheck(0);
	m_t46.SetCheck(0);
	m_t47.SetCheck(1);
	m_t48.SetCheck(1);
	m_t49.SetCheck(1);
	m_t410.SetCheck(1);
	m_t411.SetCheck(1);
	m_t412.SetCheck(1);
	m_t413.SetCheck(1);
	m_t414.SetCheck(1);	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
