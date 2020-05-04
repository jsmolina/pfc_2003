// tmpConfigDriverDlg.h : header file
//
#include "exports.h"
#if !defined(AFX_TMPCONFIGDRIVERDLG_H__E7432CD6_BCCE_4385_A1A0_A26F3228133A__INCLUDED_)
#define AFX_TMPCONFIGDRIVERDLG_H__E7432CD6_BCCE_4385_A1A0_A26F3228133A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



/////////////////////////////////////////////////////////////////////////////
// CTmpConfigDriverDlg dialog


class CTmpConfigDriverDlg : public CDialog
{
// Construction
public:
	CTmpConfigDriverDlg(CWnd* pParent = NULL);	// standard constructor
	void WinPrintf(char input[255]);
	void WinPrintf(char input[255], int nID, bool clrscr);
	void InitDirectInput();
	void TakeDeviceOnGUIConfig();
protected:
	void GetConfig(int SP_BUTTON, int ID_CDI, int ID_CBU);
	void GetAxisConfig(int SP_AXIS, int ID_CDI, int ID_CAX);
	void GetAsEspecialsConfig(int SP_AXIS, CComboBox * cc_boto, CComboBox * cc_eixfin);

public:
// Dialog Data
	//{{AFX_DATA(CTmpConfigDriverDlg)
	enum { IDD = IDD_TMPCONFIGDRIVER_DIALOG };
	CTabCtrl	m_tabcontrol;
	CString	m_editor;
	BOOL	m_ontop;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTmpConfigDriverDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	void ConfigTabs();

	// Generated message map functions
	//{{AFX_MSG(CTmpConfigDriverDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangingTab1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSetTop();
	afx_msg void OnAboutD();
	virtual void OnOK();
	afx_msg void OnApply();
	virtual void OnCancel();
	afx_msg void OnButton32();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TMPCONFIGDRIVERDLG_H__E7432CD6_BCCE_4385_A1A0_A26F3228133A__INCLUDED_)
