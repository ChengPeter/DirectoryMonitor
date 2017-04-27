// DirectoryMonitorDlg.cpp : implementation file
//

#include <windows.h> 
#include "stdafx.h"
#include "DirectoryMonitor.h"
#include "DirectoryMonitorDlg.h"
#include "OPTIONS.h"
#include "Appmonitor.h"
#include "SplashWnd.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#include "FileVersion.h"
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDirectoryMonitorDlg dialog

/************************************************************************/
/* 函数名：CDirectoryMonitorDlg

   函数功能：初始化系统图标
   创建者：Peter
   创建时间：2015-6-16
   修改时间: 2015-6-16
   修改内容：修改系统图标                                               */
/************************************************************************/
CDirectoryMonitorDlg::CDirectoryMonitorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDirectoryMonitorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDirectoryMonitorDlg)
	m_strDirectoryPath = _T("");
	m_thread=NULL;
	index=0;
	strPathCommon="";
	m_autoMin = FALSE;
	m_autoMonitor = FALSE;
	m_autoRun = FALSE;
	m_windows = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void CDirectoryMonitorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDirectoryMonitorDlg)
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Text(pDX, IDC_EDIT1, m_strDirectoryPath);
	DDX_Check(pDX, IDC_AUTOMIN, m_autoMin);
	DDX_Check(pDX, IDC_AUTOMONITOR, m_autoMonitor);
	DDX_Check(pDX, IDC_AUTORUN, m_autoRun);
	DDX_Check(pDX, IDC_WINDOWS, m_windows);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDirectoryMonitorDlg, CDialog)
	//{{AFX_MSG_MAP(CDirectoryMonitorDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_OPTIONS, OnBtnOptions)
	ON_BN_CLICKED(IDC_BTN_APP, OnBtnApp)
	ON_BN_CLICKED(IDC_BTN_SELECTDIR, OnBtnSelectdir)
	ON_BN_CLICKED(IDC_BTN_START, OnBtnStart)
	ON_BN_CLICKED(IDC_BTN_STOP, OnBtnStop)
	ON_BN_CLICKED(IDC_BTN_CLEAR, OnBtnClear)
	ON_BN_CLICKED(IDC_AUTOMONITOR, OnAutomonitor)
	ON_BN_CLICKED(IDC_AUTOMIN, OnAutomin)
	ON_BN_CLICKED(IDC_AUTORUN, OnAutorun)
	ON_BN_CLICKED(IDC_WINDOWS, OnWindows)
	ON_MESSAGE(WM_TRAY,OnTrayNotify)
	ON_WM_CLOSE()
	ON_WM_SIZE()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDirectoryMonitorDlg message handlers
/* 函数名：CDirectoryMonitorDlg

   函数功能：初始化对话框
   创建者：Peter
   创建时间：2015-6-16
   修改时间: 2015-6-16
   修改内容：修改系统的初始化成员数据                                              */
/************************************************************************/
BOOL CDirectoryMonitorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	InitTray();
    InitListView();
	//开始禁用停止按钮
    GetDlgItem(IDC_BTN_STOP)->EnableWindow(FALSE);

   //InitProfile(m_autoMin,"Minimized",1);
  // InitProfile(m_autoMin,"AutoMonitor",2);
    CString str,str1,str2,str3;
	GetPrivateProfileString("Settings","Minimized","",str.GetBuffer(MAX_PATH),MAX_PATH,".\\Settings.ini");

	GetPrivateProfileString("Settings","AutoMonitor","",str1.GetBuffer(MAX_PATH),MAX_PATH,".\\Settings.ini");

	GetPrivateProfileString("Settings","AlwaysOnTop","",str2.GetBuffer(MAX_PATH),MAX_PATH,".\\Settings.ini");

	GetPrivateProfileString("Settings","AutoRun","",str3.GetBuffer(MAX_PATH),MAX_PATH,".\\Settings.ini");

	if(str=="1")
	{
       m_autoMin=true;
	   UpdateData(FALSE);
	   PostMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0);
	}
	else
	{
	   m_autoMin=false;
	   UpdateData(FALSE);
	}
	if(str1=="1")
	{
		m_autoMonitor=true;
		m_strDirectoryPath="C:\\";
		UpdateData(FALSE);
		GetDlgItem(IDC_EDIT1)->SetWindowText("正在监控"+m_strDirectoryPath);
	    OnBtnStart();
	}
	else
	{
		m_autoMonitor=false;
		UpdateData(FALSE);
	}
	if(str2=="1")
	{
		m_windows=true;
		UpdateData(FALSE);
		OnWindows();
	}
	else
	{
		m_windows=false;
		UpdateData(FALSE);
	}
	if (str3=="1")
	{
        m_autoRun=true;
		UpdateData(FALSE);
	}
	else
	{
		m_autoRun=false;
		UpdateData(FALSE);
	}
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDirectoryMonitorDlg::InitProfile(BOOL b,CString strName,int type)
{
    CString str;
	GetPrivateProfileString("Settings",strName,"",str.GetBuffer(MAX_PATH),MAX_PATH,".\\Settings.ini");
	if(str=="1")
	{	
		b = true;
		UpdateData(FALSE);

	    if(type==1)
		   PostMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0);
		else if(type==2)
		{
		 m_strDirectoryPath="C:\\";
	 	 UpdateData(FALSE);
		 GetDlgItem(IDC_EDIT1)->SetWindowText("正在监控"+m_strDirectoryPath);
	     OnBtnStart();
		}
	}
	else if(str=="0")
	{
		b=false;
		UpdateData(FALSE);
	}
}

void CDirectoryMonitorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDirectoryMonitorDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDirectoryMonitorDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
/* 函数名：OnBtnOptions

   函数功能：单击打开选项监控对话框
   创建者：Peter
   创建时间：2015-6-16
   修改时间: 
   修改内容：                                              */
/************************************************************************/
void CDirectoryMonitorDlg::OnBtnOptions() 
{
	// TODO: Add your control notification handler code here
	COPTIONS dlg;
	dlg.DoModal();
}
/* 函数名：OnBtnApp

   函数功能：单击打开应用程序监控对话框
   创建者：Peter
   创建时间：2015-6-16
   修改时间: 
   修改内容：                                              */
/************************************************************************/
void CDirectoryMonitorDlg::OnBtnApp() 
{
	// TODO: Add your control notification handler code here
	CAppmonitor dlg;
	dlg.DoModal();
}
/* 函数名：OnBtnSelectdir

   函数功能：选择监控目录
   创建者：Peter
   创建时间：2015-6-25
   修改时间: 
   修改内容：                                              */
/************************************************************************/
void CDirectoryMonitorDlg::OnBtnSelectdir() 
{
	// TODO: Add your control notification handler code here
/*	CFileDialog dlg(true);
	CString path;
	if(dlg.DoModal()!=IDOK)
	{
       return;
	}
	else
		 path=dlg.GetPathName();
    AfxMessageBox(path);*/
	static TCHAR strDirName[MAX_PATH];
	BROWSEINFO bi;
	CString szString = TEXT("选择一个源文件子文件夹");
	bi.hwndOwner = this->GetSafeHwnd();
	bi.pidlRoot = NULL;
    bi.pszDisplayName = strDirName;
	bi.lpszTitle = szString;
    bi.ulFlags = BIF_BROWSEFORCOMPUTER | BIF_DONTGOBELOWDOMAIN | BIF_RETURNONLYFSDIRS;
    bi.lpfn = NULL;
	bi.lParam = 0;
	bi.iImage = 0;

	LPITEMIDLIST pItemIDList = SHBrowseForFolder(&bi);	
	if(pItemIDList == NULL)		
	{		
		return ;		
	}		
	SHGetPathFromIDList(pItemIDList, strDirName);
	strPathCommon=strDirName;
	if(strPathCommon != "" && strPathCommon.Right(1) != "\\")
		strPathCommon += "\\";
	GetDlgItem(IDC_EDIT1)->SetWindowText(strPathCommon);
	
	//SetDlgItemText(IDC_EDIT1,str);
}
/* 函数名：InitListView

   函数功能：初始化列表视图控件
   创建者：Peter
   创建时间：2015-6-25
   修改时间: 
   修改内容：                                              */
/************************************************************************/
void CDirectoryMonitorDlg::InitListView()
{
   // CRect rect;
   // m_list.GetClientRect(&rect);
	m_list.ModifyStyle(LVS_TYPEMASK,LVS_REPORT);
	m_list.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FLATSB|LVS_EX_FULLROWSELECT|LVS_EX_TWOCLICKACTIVATE);
	m_list.InsertColumn(0,"数  量",LVCFMT_LEFT,50);
    m_list.InsertColumn(1,"时  间",LVCFMT_LEFT,150);
    m_list.InsertColumn(2,"类  型",LVCFMT_LEFT,70);
    m_list.InsertColumn(3,"变化内容",LVCFMT_LEFT,600);

/*m_list.InsertItem(3,"111");
				m_list.SetItemText(0,1,"111");
				m_list.SetItemText(0,2,"111");
				m_list.SetItemText(0,3,"111");
				m_list.InsertItem(5,"111");*/
}
/* 函数名：ThreadProc

函数功能：线程处理函数
创建者：Peter
创建时间：2015-6-25
修改时间: 2015-7-4
修改内容：增加选项控制功能，根据选项的选取来进行不同类型的文件监控                                             */
/************************************************************************/
DWORD WINAPI ThreadProc(LPVOID lpParam)
{

//	AfxMessageBox(strTime);
	BOOL b1,b2,b3,b4,b5;
    b1=(GetPrivateProfileInt("Selections","Check1Del",0,".\\Selections.ini")==0 ?false:true);
	b2=(GetPrivateProfileInt("Selections","Check2Modify",0,".\\Selections.ini")==0 ?false:true);
	b3=(GetPrivateProfileInt("Selections","Check3Rename",0,".\\Selections.ini")==0 ?false:true);
	b4=(GetPrivateProfileInt("Selections","Check4Mdfatr",0,".\\Selections.ini")==0 ?false:true);
	b5=(GetPrivateProfileInt("Selections","Check5Other",0,".\\Selections.ini")==0 ?false:true);

    BOOL bRet = FALSE; 
    BYTE Buffer[1024] = { 0 }; 

    CDirectoryMonitorDlg *pdlg = (CDirectoryMonitorDlg*)lpParam;

    FILE_NOTIFY_INFORMATION *pBuffer = (FILE_NOTIFY_INFORMATION *)Buffer; 

    DWORD BytesReturned = 0; 

    //AfxMessageBox(pdlg->m_strDirectoryPath);

     HANDLE hFile = CreateFile(pdlg->m_strDirectoryPath.GetBuffer(0),
                FILE_LIST_DIRECTORY,  
                FILE_SHARE_READ|FILE_SHARE_DELETE|FILE_SHARE_WRITE, 
                NULL, 
                OPEN_EXISTING, 
                FILE_FLAG_BACKUP_SEMANTICS, 
                NULL); 
    if ( INVALID_HANDLE_VALUE == hFile ) 
    { 
		CString str;
		str.Format("Error is %d",GetLastError());
		AfxMessageBox(str);
        return 1; 
    } 

  CString strInfo;
  CString strType;
  CString strIndex;
  COPTIONS dlg;
  while ( TRUE ) 
    { 
        ZeroMemory(Buffer, 1024); 

        bRet = ReadDirectoryChangesW(hFile, 
                        &Buffer, 
                        sizeof(Buffer), 
                        TRUE, 
                        FILE_NOTIFY_CHANGE_FILE_NAME | 
                        FILE_NOTIFY_CHANGE_ATTRIBUTES | 
                        FILE_NOTIFY_CHANGE_LAST_WRITE , 
                        &BytesReturned, 
                        NULL, NULL); 
         
        if ( bRet == TRUE ) 
		{
			//获取当前的系统时间
			CTime tm;
			CString strTime;
			tm=CTime::GetCurrentTime();
	strTime = tm.Format(_T("%Y-%m-%d %H:%M:%S"));
 
            switch(pBuffer->Action)  
            {  
               
            case FILE_ACTION_ADDED:  
                { 
					strType = "添加";
					strInfo = "添加文件：";
                    strInfo += pBuffer->FileName;
                    break; 	
                } 
                
            case FILE_ACTION_REMOVED:  
                { 
					if(b1)
					{
                    strType = "删除";
					strInfo = "删除文件：";
					strInfo += pBuffer->FileName;
                    break; 
					}
                } 
                
            case FILE_ACTION_MODIFIED:  
                { 
					if(b2&&b4)
					{
                    strType = "修改";
					strInfo = "修改文件：";
					strInfo += pBuffer->FileName;
                    break;
					}
                } 
                
            case FILE_ACTION_RENAMED_OLD_NAME:  
                { 
					if(b3)
					{
						strType = "重命名";
						strInfo = "将文件：";
						strInfo += pBuffer->FileName;
				
						if ( pBuffer->NextEntryOffset != 0 ) 
						{ 
							FILE_NOTIFY_INFORMATION *tmpBuffer = (FILE_NOTIFY_INFORMATION *)((DWORD)pBuffer + pBuffer->NextEntryOffset); 
							switch ( tmpBuffer->Action ) 
							{ 
							case FILE_ACTION_RENAMED_NEW_NAME: 
								{         
									strInfo += "重命名为：";
									strInfo += tmpBuffer->FileName;
									break; 
								} 
							}			
						} 
						break; 
                    } 
                     
                } 
            case FILE_ACTION_RENAMED_NEW_NAME:  
                { 
					strType = "重命名";
					strInfo = "重命名：";
					strInfo += pBuffer->FileName;
					break;
                } 
			default:
				if(b5)
				{
					strType = "其他";
					break;
				}
		
			}
			if(pdlg != NULL)
			{
				strIndex.Format("%d",pdlg->index);
				pdlg->m_list.InsertItem(pdlg->index,strIndex);
				pdlg->m_list.SetItemText(pdlg->index,1,strTime);
				pdlg->m_list.SetItemText(pdlg->index,2,strType);
				pdlg->m_list.SetItemText(pdlg->index++,3,strInfo);
			}
        } 
    } 
 	
   CloseHandle(hFile); 
   return 0; 	
}
/* 函数名：OnBtnStart

函数功能：开始监控
创建者：Peter
创建时间：2015-6-25
修改时间: 
修改内容：                                              */
/************************************************************************/
void CDirectoryMonitorDlg::OnBtnStart() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_strDirectoryPath=="")
	{
	 AfxMessageBox("请先选择要监控的文件夹路径");
	 return;
	}
	if(strPathCommon != "")
	   GetDlgItem(IDC_EDIT1)->SetWindowText("正在监控:"+strPathCommon);

	 GetDlgItem(IDC_BTN_STOP)->EnableWindow(true);
	 GetDlgItem(IDC_BTN_START)->EnableWindow(FALSE);
	 GetDlgItem(IDC_BTN_SELECTDIR)->EnableWindow(FALSE);
	 m_thread=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)&ThreadProc,(LPVOID)this,0,NULL);
	 
	 if(m_thread == NULL)
	 {
		 AfxMessageBox("监控失败");
	 }
	 else
	 {
		 AfxMessageBox("监控成功");
		 //WaitForSingleObject(m_thread, INFINITE); 
         //CloseHandle(m_thread); 
	 }
}
/* 函数名：OnBtnStop

函数功能：结束监控
创建者：Peter
创建时间：2015-6-25
修改时间: 
修改内容：                                              */
/************************************************************************/
void CDirectoryMonitorDlg::OnBtnStop() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_BTN_SELECTDIR)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_START)->EnableWindow(TRUE);
	 GetDlgItem(IDC_BTN_STOP)->EnableWindow(FALSE);
	 if(m_thread)
	 {
		 TerminateThread(m_thread,0);
		 CloseHandle(m_thread);
		 m_thread=NULL;
	 }

	 GetDlgItem(IDC_EDIT1)->SetWindowText("停止监控:"+strPathCommon);
}

void CDirectoryMonitorDlg::OnBtnClear() 
{
	// TODO: Add your control notification handler code here
	m_list.DeleteAllItems();

}
/* 函数名：OnAutomonitor

  函数功能：自动开始监控
  创建者：Peter
  创建时间：2015-6-27
  修改时间: 
修改内容：                                              */
/************************************************************************/
void CDirectoryMonitorDlg::OnAutomonitor() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    WritePrivateProfileString("Settings","AutoMonitor",m_autoMonitor? "1":"0",".\\Settings.ini");
}
/* 函数名：OnAutomin

  函数功能：自动最小化
  创建者：Peter
  创建时间：2015-6-27
  修改时间: 
修改内容：                                              */
/************************************************************************/
void CDirectoryMonitorDlg::OnAutomin() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    WritePrivateProfileString("Settings","Minimized",m_autoMin? "1":"0",".\\Settings.ini");

	//UpdateData(FALSE);
}
/* 函数名：OnAutorun

  函数功能：自动运行
  创建者：Peter
  创建时间：2015-6-27
  修改时间: 
修改内容：                                              */
/************************************************************************/
void CDirectoryMonitorDlg::OnAutorun() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    WritePrivateProfileString("Settings","AutoRun",m_autoRun? "1":"0",".\\Settings.ini");
	if (m_autoRun==TRUE)
	{
		AutoRun();
	}
	else
		NoAutoRun();
}
/* 函数名：OnWindows

  函数功能：自动实现窗口最前面
  创建者：Peter
  创建时间：2015-6-27
  修改时间: 
修改内容：                                              */
/************************************************************************/
void CDirectoryMonitorDlg::OnWindows() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);	
	if (m_windows)
	{
		SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | WS_EX_TOPMOST);
		WritePrivateProfileString("Settings","AlwaysOnTop","1",".\\Settings.ini");
	}
	
	else
	{
		::SetWindowPos(GetSafeHwnd(), HWND_NOTOPMOST, 0, 0, 0, 0,SWP_NOMOVE | SWP_NOSIZE);
		WritePrivateProfileString("Settings","AlwaysOnTop","0",".\\Settings.ini");
	}

}
/* 函数名：AutoRun

  函数功能：开机自启动
  创建者：Peter
  创建时间：2015-8-24
  修改时间: 
  修改内容：                                              */
/************************************************************************/
void CDirectoryMonitorDlg::AutoRun()
{
	CString keyStr;
	LONG lgtResult;
	CString fileName;
	HKEY hRegKey;
	
	keyStr =_T("Software\\Microsoft\\Windows\\CurrentVersion\\Run");
	if(RegOpenKey(HKEY_CURRENT_USER,keyStr,&hRegKey) !=  ERROR_SUCCESS)
		return ;
	else
	{
		TCHAR path[MAX_PATH];
		GetModuleFileName(NULL,path,sizeof(path));	
		CString strPath = path;
		//获得fileName
		_splitpath(strPath.GetBuffer(0),NULL,NULL,fileName.GetBufferSetLength(MAX_PATH+1),NULL);
	//	AfxMessageBox(fileName);
		lgtResult=RegSetValueEx(hRegKey,fileName,0,REG_SZ,(CONST BYTE *)strPath.GetBuffer(0),strPath.GetLength());
		if(lgtResult!=ERROR_SUCCESS)
		{
			AfxMessageBox("设置失败");
			return ;
		}
		strPath.ReleaseBuffer();
		AfxMessageBox("设置成功");
		RegCloseKey(hRegKey);
	}
}
/* 函数名：NoAutoRun

  函数功能：开机不自启动
  创建者：Peter
  创建时间：2015-8-24
  修改时间: 
  修改内容：                                              */
/************************************************************************/
void CDirectoryMonitorDlg::NoAutoRun()
{
	CString keyStr;
	LONG lgtResult;
	CString fileName;
	HKEY hRegKey;
	
	keyStr =_T("Software\\Microsoft\\Windows\\CurrentVersion\\Run");
	if(RegOpenKey(HKEY_CURRENT_USER,keyStr,&hRegKey) !=  ERROR_SUCCESS)
		return ;
	else
	{
		TCHAR path[MAX_PATH];
		GetModuleFileName(NULL,path,sizeof(path));	
		CString strPath = path;
		//获得fileName
		_splitpath(strPath.GetBuffer(0),NULL,NULL,fileName.GetBufferSetLength(MAX_PATH+1),NULL);
		//AfxMessageBox(fileName);
		lgtResult=RegDeleteValue(hRegKey,fileName);
		if(lgtResult!=ERROR_SUCCESS)
		{
			AfxMessageBox("设置失败");
			return ;
		}
		strPath.ReleaseBuffer();
		AfxMessageBox("设置成功");
		RegCloseKey(hRegKey);
	}
}
/* 函数名：InitTray

  函数功能：初始化托盘
  创建者：Peter
  创建时间：2015-8-24
  修改时间: 
  修改内容：                                              */
/************************************************************************/
void CDirectoryMonitorDlg::InitTray()
{
	nid.cbSize=(DWORD)sizeof(NOTIFYICONDATA);  
     nid.hWnd=this->m_hWnd;   
     nid.uID=IDR_MAINFRAME;   
    nid.uFlags=NIF_ICON|NIF_MESSAGE|NIF_TIP ;   
	nid.uCallbackMessage=WM_TRAY;//自定义的消息名称   
	nid.hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));   
    strcpy(nid.szTip,_T("文件监控系统")); //信息提示条   
    Shell_NotifyIcon(NIM_ADD,&nid); //在托盘区添加图标 
}
/* 函数名：OnTrayNotify

  函数功能：托盘消息处理函数
  创建者：Peter
  创建时间：2015-8-24
  修改时间: 
  修改内容：                                              */
/************************************************************************/
LRESULT CDirectoryMonitorDlg::OnTrayNotify(WPARAM wParam, LPARAM lParam)
{
	if(wParam!=IDR_MAINFRAME)   
        return 1;   
	
    switch(lParam)   
    {  
    case WM_RBUTTONUP://右键起来时弹出快捷菜单，这里只有一个“关闭”   
        {  
            LPPOINT lpoint=new tagPOINT;   
            GetCursorPos(lpoint);//得到鼠标位置   
            CMenu menu;   
            menu.CreatePopupMenu();//声明一个弹出式菜单   
            //增加菜单项“关闭”，点击则发送消息WM_DESTROY给主窗口（已隐藏），将程序结束。   
            menu.AppendMenu(MF_STRING,WM_DESTROY,"关闭"); //确定弹出式菜单的位置   
            SetForegroundWindow(); // 防止未选菜单不消失  
            menu.TrackPopupMenu(TPM_LEFTALIGN,lpoint->x,lpoint->y,this); //资源回收   
            HMENU hmenu=menu.Detach();   
            menu.DestroyMenu();   
            delete lpoint;   
        }   
        break;   
    case WM_LBUTTONDBLCLK://双击左键的处理   
        {  
            //窗口前端显示  
            SetForegroundWindow();  
            ShowWindow(SW_SHOWNORMAL);  
        }   
        break;   
    default: break;   
    }   
    return 0;  
}
/* 函数名：OnClose

  函数功能：关闭应用程序
  创建者：Peter
  创建时间：2015-8-24
  修改时间: 
  修改内容：                                              */
/************************************************************************/
void CDirectoryMonitorDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	
	CString strTitle,strText;
	strText=_T("你确定要退出程序吗？");
	strTitle=_T("托盘程序");
	int result;
	result=MessageBox(strText,strTitle,MB_ICONQUESTION|MB_OKCANCEL);
	if(IDOK==result)
	{
		Shell_NotifyIcon(NIM_DELETE,&nid); 
	}
	CDialog::OnClose();
}
/* 函数名：OnSize

  函数功能：最小化到托盘
  创建者：Peter
  创建时间：2015-8-24
  修改时间: 
  修改内容：                                              */
/************************************************************************/
void CDirectoryMonitorDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if (nType==SIZE_MINIMIZED)
	{
		ShowWindow(SW_HIDE);
	}
}

int CDirectoryMonitorDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	CSplashWnd::ShowSplashScreen(this);
    Sleep(3000);

	return 0;
}

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CFileVersion cf;
	cf.Open("DirectoryMonitor.exe");
	CString str;
	str=cf.GetProductName();
	SetDlgItemText(IDC_PRODUCTNAME,str);
	str=cf.GetLegalCopyright();
	SetDlgItemText(IDC_COPYRIGHT,str);
	str=cf.GetProductVersion();
	SetDlgItemText(IDC_VERSION,str);
	str=cf.GetCompanyName();
	SetDlgItemText(IDC_COMPANY,str);
	str=cf.GetComments();
	SetDlgItemText(IDC_AUTHER,str);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
