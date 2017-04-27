; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CAboutDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "DirectoryMonitor.h"

ClassCount=5
Class1=CDirectoryMonitorApp
Class2=CDirectoryMonitorDlg
Class3=CAboutDlg

ResourceCount=5
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_DIRECTORYMONITOR_DIALOG
Class4=COPTIONS
Resource4=IDD_DOPTIONS
Class5=CAppmonitor
Resource5=IDD_DMONITOR

[CLS:CDirectoryMonitorApp]
Type=0
HeaderFile=DirectoryMonitor.h
ImplementationFile=DirectoryMonitor.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC

[CLS:CDirectoryMonitorDlg]
Type=0
HeaderFile=DirectoryMonitorDlg.h
ImplementationFile=DirectoryMonitorDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_AUTORUN

[CLS:CAboutDlg]
Type=0
HeaderFile=DirectoryMonitorDlg.h
ImplementationFile=DirectoryMonitorDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=7
Control1=IDC_STATIC,static,1342177283
Control2=IDC_PRODUCTNAME,static,1342308480
Control3=IDC_COPYRIGHT,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_AUTHER,static,1342308352
Control6=IDC_VERSION,static,1342308352
Control7=IDC_COMPANY,static,1342308352

[DLG:IDD_DIRECTORYMONITOR_DIALOG]
Type=1
Class=CDirectoryMonitorDlg
ControlCount=13
Control1=IDC_LIST1,SysListView32,1350631425
Control2=IDC_EDIT1,edit,1484849280
Control3=IDC_STATIC,button,1342177287
Control4=IDC_AUTOMONITOR,button,1342242819
Control5=IDC_AUTOMIN,button,1342242819
Control6=IDC_AUTORUN,button,1342242819
Control7=IDC_WINDOWS,button,1342242819
Control8=IDC_BTN_START,button,1342242817
Control9=IDC_BTN_SELECTDIR,button,1342242816
Control10=IDC_BTN_CLEAR,button,1342242816
Control11=IDC_BTN_STOP,button,1342242816
Control12=IDC_BTN_APP,button,1342242816
Control13=IDC_BTN_OPTIONS,button,1342242816

[DLG:IDD_DOPTIONS]
Type=1
Class=COPTIONS
ControlCount=16
Control1=IDC_CHECK1_DEL,button,1342242819
Control2=IDC_CHECK2_MODIFY,button,1342242819
Control3=IDC_CHECK3_RENAME,button,1342242819
Control4=IDC_CHECK4_MDFATR,button,1342242819
Control5=IDC_CHECK5_OTHER,button,1342242819
Control6=IDC_BTN_SELECTALL,button,1342242816
Control7=IDC_BTN_SELECTNO,button,1342242816
Control8=IDC_BTN_OK,button,1342242816
Control9=IDC_BTN_NO,button,1342242816
Control10=IDC_STATIC,button,1342177287
Control11=IDC_STATIC,static,1342177283
Control12=IDC_STATIC,static,1342177287
Control13=IDC_STATIC,static,1342177283
Control14=IDC_STATIC,static,1342177283
Control15=IDC_STATIC,static,1342177283
Control16=IDC_STATIC,static,1342177283

[CLS:COPTIONS]
Type=0
HeaderFile=OPTIONS.h
ImplementationFile=OPTIONS.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_CHECK1_DEL

[DLG:IDD_DMONITOR]
Type=1
Class=CAppmonitor
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDC_LIST1,SysListView32,1350631425

[CLS:CAppmonitor]
Type=0
HeaderFile=Appmonitor.h
ImplementationFile=Appmonitor.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC

