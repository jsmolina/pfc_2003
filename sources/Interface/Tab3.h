#if !defined(AFX_TAB3_H__76129A80_CCD4_4D7D_9E53_4E33C830B837__INCLUDED_)
#define AFX_TAB3_H__76129A80_CCD4_4D7D_9E53_4E33C830B837__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Tab3.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTab3 dialog

class CTab3 : public CDialog
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
	void SetListDeviceCaps(int current, CComboBox * cc);

// Construction
public:
	CTab3(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTab3)
	enum { IDD = IDD_TAB3 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTab3)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTab3)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnSelchangeT301();
	afx_msg void OnSelchangeT302();
	afx_msg void OnSelchangeT303();
	afx_msg void OnSelchangeT304();
	afx_msg void OnSelchangeT305();
	afx_msg void OnSelchangeT306();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TAB3_H__76129A80_CCD4_4D7D_9E53_4E33C830B837__INCLUDED_)
