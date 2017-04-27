#if !defined(AFX_APPMONITOR_H__7CF2D5BB_74BD_4476_957A_53A9BD6DFE7C__INCLUDED_)
#define AFX_APPMONITOR_H__7CF2D5BB_74BD_4476_957A_53A9BD6DFE7C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Appmonitor.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAppmonitor dialog

class CAppmonitor : public CDialog
{
// Construction
public:
	
	CAppmonitor(CWnd* pParent = NULL); // standard constructor 
	int m_num;
    CString m_programName[400];
	void getState();

// Dialog Data
	//{{AFX_DATA(CAppmonitor)
	enum { IDD = IDD_DMONITOR };
	CListCtrl	m_list1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAppmonitor)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAppmonitor)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_APPMONITOR_H__7CF2D5BB_74BD_4476_957A_53A9BD6DFE7C__INCLUDED_)


