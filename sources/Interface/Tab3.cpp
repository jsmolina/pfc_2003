// Tab3.cpp : implementation file
//

#include "stdafx.h"
#include "tmpConfigDriver.h"
#include "Tab3.h"
#include "head/DirectInput/dinput_f.h"
#include "head/CBDades.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern CBDades dbase;


/////////////////////////////////////////////////////////////////////////////
// CTab3 dialog


CTab3::CTab3(CWnd* pParent /*=NULL*/)
	: CDialog(CTab3::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTab3)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTab3::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTab3)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTab3, CDialog)
	//{{AFX_MSG_MAP(CTab3)
	ON_WM_SIZE()
	ON_WM_VSCROLL()
	ON_CBN_SELCHANGE(IDC_T301, OnSelchangeT301)
	ON_CBN_SELCHANGE(IDC_T302, OnSelchangeT302)
	ON_CBN_SELCHANGE(IDC_T303, OnSelchangeT303)
	ON_CBN_SELCHANGE(IDC_T304, OnSelchangeT304)
	ON_CBN_SELCHANGE(IDC_T305, OnSelchangeT305)
	ON_CBN_SELCHANGE(IDC_T306, OnSelchangeT306)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTab3 message handlers

BOOL CTab3::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	// TODO: Añadir tantos controles como los botones seleccionados en el primer TAB

	GetWindowRect(m_rcOriginalRect);
	m_nScrollPos = 0; 
	m_nhScrollPos=0;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTab3::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	m_nCurHeight = cy;
	m_nCurWidth  = cx;
	SCROLLINFO si;
	si.cbSize = sizeof(SCROLLINFO);
	si.fMask = SIF_ALL; 
	si.nMin = 0;
	si.nMax = m_rcOriginalRect.Height()+1000;
	si.nPage = cy;
	si.nPos = 0;
    SetScrollInfo(SB_VERT, &si, TRUE); 	
	si.cbSize = sizeof(SCROLLINFO);
	si.fMask = SIF_ALL; 
	si.nMin = 0;
	si.nMax = m_rcOriginalRect.Width();
	si.nPage = cx;
	si.nPos = 0;	
	SetScrollInfo(SB_HORZ, &si, TRUE);
	
}

void CTab3::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
		int nDelta;
	int nMaxPos = m_rcOriginalRect.Height() - m_nCurHeight;

	switch (nSBCode)
	{
	case SB_LINEDOWN:
		if (m_nScrollPos >= nMaxPos)
			return;

		nDelta = min(max(nMaxPos/20,5),nMaxPos-m_nScrollPos);
		break;

	case SB_LINEUP:
		if (m_nScrollPos <= 0)
			return;
		nDelta = -min(max(nMaxPos/20,5),m_nScrollPos);
		break;
	case SB_PAGEDOWN:
		if (m_nScrollPos >= nMaxPos)
			return;
		nDelta = min(max(nMaxPos/10,5),nMaxPos-m_nScrollPos);
		break;
	case SB_THUMBTRACK:
	case SB_THUMBPOSITION:
		nDelta = (int)nPos - m_nScrollPos;
		break;

	case SB_PAGEUP:
		if (m_nScrollPos <= 0)
			return;
		nDelta = -min(max(nMaxPos/10,5),m_nScrollPos);
		break;
	
         default:
		return;
	}
	m_nScrollPos += nDelta;
	SetScrollPos(SB_VERT,m_nScrollPos,TRUE);
	ScrollWindow(0,-nDelta);
	
	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}
//////////////////////////////////////////////////////////////////////
void CTab3::SetListDeviceCaps(int current, CComboBox * cc)
{
	int nbotons=0;
	char buffer[10];
	register int i=0;

	cc->ResetContent();
	if (current <0) return;
	CDirectInput ** d   = dbase.GetDI();
	if (d[current]!=NULL)
	{
		nbotons = d[current]->GetnBotons();
		
		for (i = 0; i < nbotons; i++)
		{
			sprintf(buffer, "B:%d", i);
			cc->InsertString(i, buffer);			
		}			
	}
}
////////////////////////////////////////////////////////////////

void CTab3::OnSelchangeT301() 
{
	// TODO: Add your control notification handler code here
	CComboBox * cc;	
	int current=-1;
	// obtenim un punter al combo que ha canviat
	cc = (CComboBox *) GetDescendantWindow(IDC_T301, FALSE);	
	current = cc->GetCurSel()-1;
	// obtenim un punter al combo que variarà per aquesta causa
	cc = (CComboBox *) GetDescendantWindow(IDC_T313, FALSE);
	
	SetListDeviceCaps(current, cc);
}

void CTab3::OnSelchangeT302() 
{
	// TODO: Add your control notification handler code here
	CComboBox * cc;	
	int current=-1;
	// obtenim un punter al combo que ha canviat
	cc = (CComboBox *) GetDescendantWindow(IDC_T302, FALSE);	
	current = cc->GetCurSel()-1;
	// obtenim un punter al combo que variarà per aquesta causa
	cc = (CComboBox *) GetDescendantWindow(IDC_T314, FALSE);
	
	SetListDeviceCaps(current, cc);
}

void CTab3::OnSelchangeT303() 
{
	// TODO: Add your control notification handler code here
	CComboBox * cc;	
	int current=-1;
	// obtenim un punter al combo que ha canviat
	cc = (CComboBox *) GetDescendantWindow(IDC_T303, FALSE);	
	current = cc->GetCurSel()-1;
	// obtenim un punter al combo que variarà per aquesta causa
	cc = (CComboBox *) GetDescendantWindow(IDC_T315, FALSE);
	
	SetListDeviceCaps(current, cc);	
}

void CTab3::OnSelchangeT304() 
{
	// TODO: Add your control notification handler code here
	CComboBox * cc;	
	int current=-1;
	// obtenim un punter al combo que ha canviat
	cc = (CComboBox *) GetDescendantWindow(IDC_T304, FALSE);	
	current = cc->GetCurSel()-1;
	// obtenim un punter al combo que variarà per aquesta causa
	cc = (CComboBox *) GetDescendantWindow(IDC_T316, FALSE);
	
	SetListDeviceCaps(current, cc);
}

void CTab3::OnSelchangeT305() 
{
	// TODO: Add your control notification handler code here
	CComboBox * cc;	
	int current=-1;
	// obtenim un punter al combo que ha canviat
	cc = (CComboBox *) GetDescendantWindow(IDC_T305, FALSE);	
	current = cc->GetCurSel()-1;
	// obtenim un punter al combo que variarà per aquesta causa
	cc = (CComboBox *) GetDescendantWindow(IDC_T317, FALSE);
	
	SetListDeviceCaps(current, cc);
}

void CTab3::OnSelchangeT306() 
{
	// TODO: Add your control notification handler code here
	CComboBox * cc;	
	int current=-1;
	// obtenim un punter al combo que ha canviat
	cc = (CComboBox *) GetDescendantWindow(IDC_T306, FALSE);	
	current = cc->GetCurSel()-1;
	// obtenim un punter al combo que variarà per aquesta causa
	cc = (CComboBox *) GetDescendantWindow(IDC_T318, FALSE);
	
	SetListDeviceCaps(current, cc);
}
