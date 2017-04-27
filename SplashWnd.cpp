// SplashWnd.cpp: implementation of the CSplashWnd class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DirectoryMonitor.h"
#include "SplashWnd.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSplashWnd* CSplashWnd::c_pSplashWnd;
BOOL CSplashWnd::c_bShowSplashWnd;
IMPLEMENT_DYNAMIC(CSplashWnd, CWnd)

CSplashWnd::CSplashWnd()
{

}

CSplashWnd::~CSplashWnd()
{
	ASSERT(c_pSplashWnd == this);
	c_pSplashWnd = NULL;
}


BEGIN_MESSAGE_MAP(CSplashWnd, CWnd)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CSplashWnd 消息处理程序

void CSplashWnd::EnableSplashScreen(BOOL bEnable)
{
	c_bShowSplashWnd = bEnable;
}

void CSplashWnd::ShowSplashScreen(CWnd* pParentWnd)
{
	if ( !c_bShowSplashWnd || c_pSplashWnd != NULL )
	{
		return;
	}

	c_pSplashWnd = new CSplashWnd;
	if ( !c_pSplashWnd->Create(pParentWnd) )
	{
		delete c_pSplashWnd;
	}
	else
	{
		c_pSplashWnd->UpdateWindow();
	}
}

BOOL CSplashWnd::PreTranslateAppMessage(MSG* pMsg)
{
	if ( c_pSplashWnd == NULL )
	{
		return FALSE;
	}
	
	if ( pMsg->message == WM_KEYDOWN
		|| pMsg->message == WM_SYSKEYDOWN
		|| pMsg->message == WM_LBUTTONDOWN
		|| pMsg->message == WM_RBUTTONDOWN
		|| pMsg->message == WM_MBUTTONDOWN
		|| pMsg->message == WM_NCLBUTTONDOWN
		|| pMsg->message == WM_NCRBUTTONDOWN
		|| pMsg->message == WM_NCMBUTTONDOWN)
	{
		c_pSplashWnd->HideSplashScreen();
		return TRUE;
	}

	return FALSE;
}

void CSplashWnd::PostNcDestroy()
{
	delete this;
}

int CSplashWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if ( CWnd::OnCreate(lpCreateStruct) == -1 )
	{
		return -1;
	}

	CenterWindow();

	SetTimer(1, 3000, NULL);

	return 0;
}

void CSplashWnd::OnTimer(UINT_PTR nIDEvent)
{
	if ( nIDEvent == 1 )
	{
		HideSplashScreen();
	}
}

void CSplashWnd::OnPaint()
{
	CPaintDC dc(this);
	CDC dcImg;
	if ( !dcImg.CreateCompatibleDC(&dc) )
	{
		return;
	}

	BITMAP bm;
	m_bitmap.GetBitmap(&bm);

	CBitmap* pOldBit = dcImg.SelectObject(&m_bitmap);
	dc.BitBlt(0, 0, bm.bmWidth, bm.bmHeight, &dcImg, 0, 0, SRCCOPY);
	dcImg.SelectObject(pOldBit);
}

BOOL CSplashWnd::Create(CWnd* pParentWnd)
{
	if ( !m_bitmap.LoadBitmap(IDB_SPLASH))
	{
		return FALSE;
	}

	BITMAP bm;
	m_bitmap.GetBitmap(&bm);
	return CreateEx(0,
		AfxRegisterWndClass(0, AfxGetApp()->LoadStandardCursor(IDC_ARROW)),
		NULL,
		WS_POPUP | WS_VISIBLE,
		0, 0,
		bm.bmWidth,
		bm.bmHeight,
		pParentWnd->GetSafeHwnd(),
		NULL);
}

void CSplashWnd::HideSplashScreen()
{
	DestroyWindow();
	AfxGetMainWnd()->UpdateWindow();
}