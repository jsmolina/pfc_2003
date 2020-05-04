#if !defined(AFX_TAB6_H__01F5F95E_BA74_432B_BE0E_6A500DBB4A7E__INCLUDED_)
#define AFX_TAB6_H__01F5F95E_BA74_432B_BE0E_6A500DBB4A7E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Tab6.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTab6 dialog

class CTab6 : public CDialog
{
// Construction
public:
	CTab6(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTab6)
	enum { IDD = IDD_TAB6 };
	CComboBox	m_tz63;
	CComboBox	m_t66;
	CComboBox	m_t65;
	CComboBox	m_t64;
	CComboBox	m_t62;
	CComboBox	m_t61;
	CComboBox	m_t69;
	CComboBox	m_t68;
	CComboBox	m_t67;
	CComboBox	m_t612;
	CComboBox	m_t611;
	CComboBox	m_t610;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTab6)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTab6)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TAB6_H__01F5F95E_BA74_432B_BE0E_6A500DBB4A7E__INCLUDED_)
