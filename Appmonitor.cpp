// Appmonitor.cpp : implementation file
//

#include "stdafx.h"
#include "DirectoryMonitor.h"
#include "Appmonitor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAppmonitor dialog


CAppmonitor::CAppmonitor(CWnd* pParent /*=NULL*/)
	: CDialog(CAppmonitor::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAppmonitor)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CAppmonitor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAppmonitor)
	DDX_Control(pDX, IDC_LIST1, m_list1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAppmonitor, CDialog)
	//{{AFX_MSG_MAP(CAppmonitor)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAppmonitor message handlers
/* 函数名：OnInitDialog

   函数功能：初始化应用程序监控对话框
   创建者：Peter
   创建时间：2015-6-16
   修改时间: 
   修改内容：                                              */
/************************************************************************/
BOOL CAppmonitor::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_list1.ModifyStyle(LVS_TYPEMASK,LVS_REPORT);
	m_list1.SetExtendedStyle(LVS_EX_TWOCLICKACTIVATE|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_FLATSB);
	m_list1.InsertColumn(0,_T("任务"),LVCFMT_LEFT,300,0);
	m_list1.InsertColumn(1,_T("状态"),LVCFMT_LEFT,200,1);
	//getState();
	SetTimer(1,1000,NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CAppmonitor::getState()
{
	int num=m_list1.GetSelectedCount();
	m_list1.DeleteAllItems();
	m_num=0;
	CString str;

   CWnd *pwnd=AfxGetMainWnd()->GetWindow(GW_HWNDFIRST);
   int i=0;
   while(pwnd)
   {
    if(pwnd->IsWindowVisible()&&pwnd->GetWindowTextLength()&&!pwnd->GetOwner())
	{
		pwnd->GetWindowText(str);
		m_programName[m_num++]=str;
		this->m_list1.InsertItem(i,str);
		this->m_list1.SetItemText(i,1,"正在运行");	
		i++;
	}
	pwnd=pwnd->GetWindow(GW_HWNDNEXT);
   }
   m_list1.SetSelectionMark(num);
}

void CAppmonitor::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	int index=m_list1.GetSelectionMark();
	getState();
	m_list1.SetSelectionMark(index);
	m_list1.SetItemState(index,LVIS_SELECTED,LVIS_SELECTED);
	CDialog::OnTimer(nIDEvent);
}
