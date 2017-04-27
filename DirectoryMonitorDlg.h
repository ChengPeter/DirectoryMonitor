// DirectoryMonitorDlg.h : header file
//
#include<windows.h>
#if !defined(AFX_DIRECTORYMONITORDLG_H__40B1C80F_5126_4BBC_8BA4_0BBF7503E9FD__INCLUDED_)
#define AFX_DIRECTORYMONITORDLG_H__40B1C80F_5126_4BBC_8BA4_0BBF7503E9FD__INCLUDED_
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WM_TRAY WM_USER+100
/////////////////////////////////////////////////////////////////////////////
// CDirectoryMonitorDlg dialog

class CDirectoryMonitorDlg : public CDialog
{
// Construction
public:
	void InitTray();
	void NoAutoRun();
	void AutoRun();
	void InitProfile(BOOL b,CString strName,int type);
	void InitListView();
	CDirectoryMonitorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDirectoryMonitorDlg)
	enum { IDD = IDD_DIRECTORYMONITOR_DIALOG };
	CListCtrl	m_list;
	CString	m_strDirectoryPath;
	HANDLE m_thread;
	int index;
	CString strPathCommon;
	BOOL	m_autoMin;
	BOOL	m_autoMonitor;
	BOOL	m_autoRun;
	BOOL	m_windows;
	NOTIFYICONDATA nid;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDirectoryMonitorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDirectoryMonitorDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnOptions();
	afx_msg void OnBtnApp();
	afx_msg void OnBtnSelectdir();
	afx_msg void OnBtnStart();
	afx_msg void OnBtnStop();
	afx_msg void OnBtnClear();
	afx_msg void OnAutomonitor();
	afx_msg void OnAutomin();
	afx_msg void OnAutorun();
	afx_msg void OnWindows();
	afx_msg LRESULT OnTrayNotify(WPARAM wParam,LPARAM lParam);
	afx_msg void OnClose();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIRECTORYMONITORDLG_H__40B1C80F_5126_4BBC_8BA4_0BBF7503E9FD__INCLUDED_)

