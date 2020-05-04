// tmpConfigDriver.h : main header file for the TMPCONFIGDRIVER application
//

#if !defined(AFX_TMPCONFIGDRIVER_H__807D5E5A_D3FF_4C02_823C_D6DF4AF175BA__INCLUDED_)
#define AFX_TMPCONFIGDRIVER_H__807D5E5A_D3FF_4C02_823C_D6DF4AF175BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTmpConfigDriverApp:
// See tmpConfigDriver.cpp for the implementation of this class
//

class CTmpConfigDriverApp : public CWinApp
{
public:
	CTmpConfigDriverApp();	


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTmpConfigDriverApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTmpConfigDriverApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	private:
		bool FindLastInstance();
	public:
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////



//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TMPCONFIGDRIVER_H__807D5E5A_D3FF_4C02_823C_D6DF4AF175BA__INCLUDED_)
