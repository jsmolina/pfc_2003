#if !defined(AFX_TAB4_H__85C3449D_1008_4C96_AD16_E6FC0CC1361C__INCLUDED_)
#define AFX_TAB4_H__85C3449D_1008_4C96_AD16_E6FC0CC1361C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Tab4.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTab4 dialog

class CTab4 : public CDialog
{
// Construction
public:
	CTab4(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTab4)
	enum { IDD = IDD_TAB4 };
	CButton	m_t45;
	CButton	m_t414;
	CButton	m_t49;
	CButton	m_t48;
	CButton	m_t47;
	CButton	m_t46;
	CSliderCtrl	m_t44;
	CSliderCtrl	m_t43;
	CButton	m_t413;
	CSliderCtrl	m_t42;
	CButton	m_t412;
	CButton	m_t415;
	CButton	m_t411;
	CButton	m_t410;
	CSliderCtrl	m_t41;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTab4)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTab4)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TAB4_H__85C3449D_1008_4C96_AD16_E6FC0CC1361C__INCLUDED_)
