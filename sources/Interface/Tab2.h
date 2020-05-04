#if !defined(AFX_TAB2_H__83BF385E_B300_41DE_B6E2_72AAD26AC53A__INCLUDED_)
#define AFX_TAB2_H__83BF385E_B300_41DE_B6E2_72AAD26AC53A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Tab2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTab2 dialog

class CTab2 : public CDialog
{
public:
	// dialog size as you see in the resource view (original size)
	CRect	m_rcOriginalRect;

	// actual scroll position
	int		m_nScrollPos;
	int		m_nhScrollPos;

	// actual dialog height
	int		m_nCurHeight;
	int		m_nCurWidth;
protected:
	void	SetListDeviceCaps(int current, CComboBox * cc);

// Construction
public:
	CTab2(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTab2)
	enum { IDD = IDD_TAB2 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTab2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTab2)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnSelchangeT28TX();
	afx_msg void OnSelchangeT29TY();
	afx_msg void OnSelchangeT210TZ();
	afx_msg void OnSelchange2rx();
	afx_msg void OnSelchangeT212RY();
	afx_msg void OnSelchangeT213RZ();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TAB2_H__83BF385E_B300_41DE_B6E2_72AAD26AC53A__INCLUDED_)
