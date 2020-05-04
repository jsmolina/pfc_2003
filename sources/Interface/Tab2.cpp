// Tab2.cpp : implementation file
//

#include "stdafx.h"
#include "tmpConfigDriver.h"
#include "Tab2.h"
#include "head/DirectInput/dinput_f.h"
#include "head/CBDades.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CBDades dbase;
/////////////////////////////////////////////////////////////////////////////
// CTab2 dialog


CTab2::CTab2(CWnd* pParent /*=NULL*/)
	: CDialog(CTab2::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTab2)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTab2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTab2)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTab2, CDialog)
	//{{AFX_MSG_MAP(CTab2)
	ON_WM_SIZE()
	ON_WM_VSCROLL()
	ON_CBN_SELCHANGE(IDC_T28, OnSelchangeT28TX)
	ON_CBN_SELCHANGE(IDC_T29, OnSelchangeT29TY)
	ON_CBN_SELCHANGE(IDC_T210, OnSelchangeT210TZ)
	ON_CBN_SELCHANGE(IDC_2RX, OnSelchange2rx)
	ON_CBN_SELCHANGE(IDC_T212, OnSelchangeT212RY)
	ON_CBN_SELCHANGE(IDC_T213, OnSelchangeT213RZ)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTab2 message handlers

void CTab2::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
		m_nCurHeight = cy;
	m_nCurWidth  = cx;
	SCROLLINFO si;
	si.cbSize = sizeof(SCROLLINFO);
	si.fMask = SIF_ALL; 
	si.nMin = 0;
	si.nMax = m_rcOriginalRect.Height();
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

BOOL CTab2::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here		
	GetWindowRect(m_rcOriginalRect);
	m_nScrollPos = 0; 
	m_nhScrollPos=0;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
////////////////////////////////////////////////////////////////////
void CTab2::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
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
////////////////////////////////////////////////////////////
void CTab2::SetListDeviceCaps(int current, CComboBox * cc)
{
	int neixos=0;
	register int i=0;
	
	cc->ResetContent();
	
	if (current < 0) return;
	CDirectInput ** d   = dbase.GetDI();
	
	if (d[current]!=NULL)
	{
		neixos = d[current]->GetnEixos();
		jsmstatus * st = d[current]->GetStatus();		
		cc->InsertString(i, "0- TX");
		cc->SetItemData(i, 0);
		i++;
		cc->InsertString(i, "1- TY");
		cc->SetItemData(i, 1);
		i++;
		if (neixos>=2)
		{
			if (st->hasGUID_ZAxis) {				
				cc->InsertString(i, "2- TZ");
				cc->SetItemData(i, 2);
				i++;
			}
			if (st->hasGUID_RxAxis) {				
				cc->InsertString(i, "3- RX");
				cc->SetItemData(i, 3);
				i++;
			}
			if (st->hasGUID_RyAxis) {				
				cc->InsertString(i, "4- RY");
				cc->SetItemData(i, 4);
				i++;
			}
			if (st->hasGUID_RzAxis) {				
				cc->InsertString(i, "5- RZ");
				cc->SetItemData(i, 5);
				i++;
			}
			if (st->hasGUID_POV) {				
				cc->InsertString(i, "6- POV1");				
				cc->SetItemData(i, 6);
				i++;
				cc->InsertString(i, "7- POV2");				
				cc->SetItemData(i, 7);
				i++;
				cc->InsertString(i, "8- POV3");				
				cc->SetItemData(i, 8);
				i++;
				cc->InsertString(i, "9- POV4");				
				cc->SetItemData(i, 9);
				i++;
			}
			if (st->hasGUID_Slider) {								
				cc->InsertString(i, "10- SLIDER1");				
				cc->SetItemData(i, 10);
				i++;
				cc->InsertString(i, "11- SLIDER2");
				cc->SetItemData(i, 11);
				i++;
			}
		}	
		
			
	}
}
////////////////////////////////////////////////////////////////
void CTab2::OnSelchangeT28TX() 
{		
	CComboBox * cc;
	
	int current=-1;
	// obtenim un punter al combo que ha canviat
	cc = (CComboBox *) GetDescendantWindow(IDC_T28, FALSE);	
	current = cc->GetCurSel()-1;
	// obtenim un punter al combo que variarà per aquesta causa
	cc = (CComboBox *) GetDescendantWindow(IDC_T214, FALSE);
	
	SetListDeviceCaps(current, cc);
}

void CTab2::OnSelchangeT29TY() 
{
	// TODO: Add your control notification handler code here
	CComboBox * cc;	
	int current=-1;
	// obtenim un punter al combo que ha canviat
	cc = (CComboBox *) GetDescendantWindow(IDC_T29, FALSE);	
	current = cc->GetCurSel()-1;
	// obtenim un punter al combo que variarà per aquesta causa
	cc = (CComboBox *) GetDescendantWindow(IDC_T215, FALSE);
	
	SetListDeviceCaps(current, cc);

}

void CTab2::OnSelchangeT210TZ() 
{
	// TODO: Add your control notification handler code here
	CComboBox * cc;	
	int current=-1;
	// obtenim un punter al combo que ha canviat
	cc = (CComboBox *) GetDescendantWindow(IDC_T210, FALSE);	
	current = cc->GetCurSel()-1;
	// obtenim un punter al combo que variarà per aquesta causa
	cc = (CComboBox *) GetDescendantWindow(IDC_T216, FALSE);
	
	SetListDeviceCaps(current, cc);

}

void CTab2::OnSelchange2rx() 
{
	// TODO: Add your control notification handler code here
	CComboBox * cc;	
	int current=-1;
	// obtenim un punter al combo que ha canviat
	cc = (CComboBox *) GetDescendantWindow(IDC_2RX, FALSE);	
	current = cc->GetCurSel()-1;
	// obtenim un punter al combo que variarà per aquesta causa
	cc = (CComboBox *) GetDescendantWindow(IDC_T217, FALSE);
	
	SetListDeviceCaps(current, cc);
}

void CTab2::OnSelchangeT212RY() 
{
	// TODO: Add your control notification handler code here
	CComboBox * cc;	
	int current=-1;
	// obtenim un punter al combo que ha canviat
	cc = (CComboBox *) GetDescendantWindow(IDC_T212, FALSE);	
	current = cc->GetCurSel()-1;
	// obtenim un punter al combo que variarà per aquesta causa
	cc = (CComboBox *) GetDescendantWindow(IDC_T218, FALSE);
	
	SetListDeviceCaps(current, cc);
	
}

void CTab2::OnSelchangeT213RZ() 
{
	// TODO: Add your control notification handler code here
	CComboBox * cc;	
	int current=-1;
	// obtenim un punter al combo que ha canviat
	cc = (CComboBox *) GetDescendantWindow(IDC_T213, FALSE);	
	current = cc->GetCurSel()-1;
	// obtenim un punter al combo que variarà per aquesta causa
	cc = (CComboBox *) GetDescendantWindow(IDC_T219, FALSE);
	
	SetListDeviceCaps(current, cc);
	
}
