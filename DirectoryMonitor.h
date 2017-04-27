// DirectoryMonitor.h : main header file for the DIRECTORYMONITOR application
//

#if !defined(AFX_DIRECTORYMONITOR_H__5BF6A08F_3D6C_4ABC_8445_1AF29ECE3682__INCLUDED_)
#define AFX_DIRECTORYMONITOR_H__5BF6A08F_3D6C_4ABC_8445_1AF29ECE3682__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDirectoryMonitorApp:
// See DirectoryMonitor.cpp for the implementation of this class
//

class CDirectoryMonitorApp : public CWinApp
{
public:
	CDirectoryMonitorApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDirectoryMonitorApp)
	public:
	virtual BOOL InitInstance();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDirectoryMonitorApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIRECTORYMONITOR_H__5BF6A08F_3D6C_4ABC_8445_1AF29ECE3682__INCLUDED_)

