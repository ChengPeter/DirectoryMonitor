#if !defined(AFX_OPTIONS_H__5A6F25CF_ACCD_44FE_87BF_B8229A7965F3__INCLUDED_)
#define AFX_OPTIONS_H__5A6F25CF_ACCD_44FE_87BF_B8229A7965F3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OPTIONS.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COPTIONS dialog

class COPTIONS : public CDialog
{
// Construction
public:
	COPTIONS(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COPTIONS)
	enum { IDD = IDD_DOPTIONS };
	BOOL	m_del;
	BOOL	m_modify;
	BOOL	m_rename;
	BOOL	m_mdfatr;
	BOOL	m_other;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COPTIONS)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COPTIONS)
	afx_msg void OnBtnSelectall();
	afx_msg void OnBtnSelectno();
	afx_msg void OnBtnOk();
	afx_msg void OnBtnNo();
	afx_msg void OnCheck1Del();
	afx_msg void OnCheck2Modify();
	afx_msg void OnCheck3Rename();
	afx_msg void OnCheck4Mdfatr();
	afx_msg void OnCheck5Other();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONS_H__5A6F25CF_ACCD_44FE_87BF_B8229A7965F3__INCLUDED_)


