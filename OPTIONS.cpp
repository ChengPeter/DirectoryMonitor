// OPTIONS.cpp : implementation file
//

#include "stdafx.h"
#include "DirectoryMonitor.h"
#include "OPTIONS.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COPTIONS dialog


COPTIONS::COPTIONS(CWnd* pParent /*=NULL*/)
	: CDialog(COPTIONS::IDD, pParent)
{
	//{{AFX_DATA_INIT(COPTIONS)
	m_del = FALSE;
	m_modify = FALSE;
	m_rename = FALSE;
	m_mdfatr = FALSE;
	m_other = FALSE;
	//}}AFX_DATA_INIT
}


void COPTIONS::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COPTIONS)
	DDX_Check(pDX, IDC_CHECK1_DEL, m_del);
	DDX_Check(pDX, IDC_CHECK2_MODIFY, m_modify);
	DDX_Check(pDX, IDC_CHECK3_RENAME, m_rename);
	DDX_Check(pDX, IDC_CHECK4_MDFATR, m_mdfatr);
	DDX_Check(pDX, IDC_CHECK5_OTHER, m_other);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COPTIONS, CDialog)
	//{{AFX_MSG_MAP(COPTIONS)
	ON_BN_CLICKED(IDC_BTN_SELECTALL, OnBtnSelectall)
	ON_BN_CLICKED(IDC_BTN_SELECTNO, OnBtnSelectno)
	ON_BN_CLICKED(IDC_BTN_OK, OnBtnOk)
	ON_BN_CLICKED(IDC_BTN_NO, OnBtnNo)
	ON_BN_CLICKED(IDC_CHECK1_DEL, OnCheck1Del)
	ON_BN_CLICKED(IDC_CHECK2_MODIFY, OnCheck2Modify)
	ON_BN_CLICKED(IDC_CHECK3_RENAME, OnCheck3Rename)
	ON_BN_CLICKED(IDC_CHECK4_MDFATR, OnCheck4Mdfatr)
	ON_BN_CLICKED(IDC_CHECK5_OTHER, OnCheck5Other)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COPTIONS message handlers
/************************************************************************/
/* 函数名：OnBtnSelectall

   函数功能：全选监控选项
   创建者：Peter
   创建时间：2015-6-16
   修改时间: 
   修改内容：                                              */
/************************************************************************/
void COPTIONS::OnBtnSelectall() 
{
	// TODO: Add your control notification handler code here
	m_del = true;
	m_modify = true;
	m_rename = true;
	m_mdfatr = true;
	m_other = true;
	WritePrivateProfileString("Selections","Check1Del",m_del? "1":"0",".\\Selections.ini");
    WritePrivateProfileString("Selections","Check2Modify",m_modify? "1":"0",".\\Selections.ini");
	WritePrivateProfileString("Selections","Check3Rename",m_rename? "1":"0",".\\Selections.ini");
    WritePrivateProfileString("Selections","Check4Mdfatr",m_mdfatr? "1":"0",".\\Selections.ini");
	WritePrivateProfileString("Selections","Check5Other",m_other? "1":"0",".\\Selections.ini");
	UpdateData(false);
}
/************************************************************************/
/* 函数名：OnBtnSelectno

   函数功能：全否监控选项
   创建者：Peter
   创建时间：2015-6-16
   修改时间: 
   修改内容：                                              */
/************************************************************************/
void COPTIONS::OnBtnSelectno() 
{
	// TODO: Add your control notification handler code here
	m_del = FALSE;
	m_modify = FALSE;
	m_rename = FALSE;
	m_mdfatr = FALSE;
	m_other = FALSE;
	WritePrivateProfileString("Selections","Check1Del",m_del? "1":"0",".\\Selections.ini");
    WritePrivateProfileString("Selections","Check2Modify",m_modify? "1":"0",".\\Selections.ini");
	WritePrivateProfileString("Selections","Check3Rename",m_rename? "1":"0",".\\Selections.ini");
    WritePrivateProfileString("Selections","Check4Mdfatr",m_mdfatr? "1":"0",".\\Selections.ini");
	WritePrivateProfileString("Selections","Check5Other",m_other? "1":"0",".\\Selections.ini");
	UpdateData(false);
}

void COPTIONS::OnBtnOk() 
{
	// TODO: Add your control notification handler code here

	CDialog::OnOK();
	
}

void COPTIONS::OnBtnNo() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}
/************************************************************************/
/* 函数名：OnCheck1Del

   函数功能：更新删除复选框的状态并且在文件中记住它的状态
   创建者：Peter
   创建时间：2015-7-4
   修改时间: 
   修改内容：                                              */
/************************************************************************/
void COPTIONS::OnCheck1Del() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	WritePrivateProfileString("Selections","Check1Del",m_del? "1":"0",".\\Selections.ini");
}
/************************************************************************/
/* 函数名：OnInitDialog

   函数功能：更新修改复选框的状态并且在文件中记住它的状态
   创建者：Peter
   创建时间：2015-7-4
   修改时间: 
   修改内容：                                              */
/************************************************************************/
void COPTIONS::OnCheck2Modify() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	WritePrivateProfileString("Selections","Check2Modify",m_modify? "1":"0",".\\Selections.ini");
}
/************************************************************************/
/* 函数名：OnInitDialog

   函数功能：更新重命名复选框的状态并且在文件中记住它的状态
   创建者：Peter
   创建时间：2015-7-4
   修改时间: 
   修改内容：                                              */
/************************************************************************/
void COPTIONS::OnCheck3Rename() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	WritePrivateProfileString("Selections","Check3Rename",m_rename? "1":"0",".\\Selections.ini");
}
/************************************************************************/
/* 函数名：OnInitDialog

   函数功能：更新修改属性复选框的状态并且在文件中记住它的状态
   创建者：Peter
   创建时间：2015-7-4
   修改时间: 
   修改内容：                                              */
/************************************************************************/
void COPTIONS::OnCheck4Mdfatr() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    WritePrivateProfileString("Selections","Check4Mdfatr",m_mdfatr? "1":"0",".\\Selections.ini");
}
/************************************************************************/
/* 函数名：OnInitDialog

   函数功能：更新其他复选框的状态并且在文件中记住它的状态
   创建者：Peter
   创建时间：2015-7-4
   修改时间: 
   修改内容：                                              */
/************************************************************************/
void COPTIONS::OnCheck5Other() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	WritePrivateProfileString("Selections","Check5Other",m_other? "1":"0",".\\Selections.ini");
}
/************************************************************************/
/* 函数名：OnInitDialog

   函数功能：获取选项的选取复选框状态
   创建者：Peter
   创建时间：2015-7-4
   修改时间: 
   修改内容：                                              */
/************************************************************************/
BOOL COPTIONS::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_del=(GetPrivateProfileInt("Selections","Check1Del",0,".\\Selections.ini")==0 ?false:true);
	m_modify=(GetPrivateProfileInt("Selections","Check2Modify",0,".\\Selections.ini")==0 ?false:true);
	m_rename=(GetPrivateProfileInt("Selections","Check3Rename",0,".\\Selections.ini")==0 ?false:true);
	m_mdfatr=(GetPrivateProfileInt("Selections","Check4Mdfatr",0,".\\Selections.ini")==0 ?false:true);
	m_other=(GetPrivateProfileInt("Selections","Check5Other",0,".\\Selections.ini")==0 ?false:true);
    UpdateData(false);
	return TRUE;  // return TRUE unless you set the focus to a control	              // EXCEPTION: OCX Property Pages should return FALSE
}
