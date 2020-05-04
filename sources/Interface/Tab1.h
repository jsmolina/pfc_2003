#if !defined(AFX_TAB1_H__2AB8B17F_13A2_4586_B450_A9710A0F513E__INCLUDED_)
#define AFX_TAB1_H__2AB8B17F_13A2_4586_B450_A9710A0F513E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Tab1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTab1 dialog

class CTab1 : public CDialog
{
public:
	void ModeNormal();
	void ModePersonalitzat();
	void ModeDefecte();
// Construction
public:
	CTab1(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTab1)
	enum { IDD = IDD_TAB1 };
	CEdit	m_t22;
	CEdit	m_t21;
	CEdit	m_t20;
	CSpinButtonCtrl	m_t19;
	CSpinButtonCtrl	m_t18;
	CEdit	m_t16;
	CButton	m_t17;
	CEdit	m_t15;
	CEdit	m_t14;
	CEdit	m_t13;
	CComboBox	m_t12;
	CEdit	m_t11;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTab1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTab1)
	afx_msg void OnBdefaults();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeT12();
	afx_msg void OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpin2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeT15();
	afx_msg void OnChangeT16();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TAB1_H__2AB8B17F_13A2_4586_B450_A9710A0F513E__INCLUDED_)
