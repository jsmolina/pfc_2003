#if !defined(AFX_TAB5_H__4AA50413_0C77_4523_85D4_6D119F4F5A83__INCLUDED_)
#define AFX_TAB5_H__4AA50413_0C77_4523_85D4_6D119F4F5A83__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Tab5.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTab5 dialog

class CTab5 : public CDialog
{
// Construction
public:
	CTab5(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTab5)
	enum { IDD = IDD_TAB5 };
	CButton	m_loging;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTab5)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTab5)
	virtual BOOL OnInitDialog();
	afx_msg void OnLoging();
	afx_msg void OnSelchangeHdev10();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TAB5_H__4AA50413_0C77_4523_85D4_6D119F4F5A83__INCLUDED_)
