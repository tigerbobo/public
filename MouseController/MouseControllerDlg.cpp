
// MouseControllerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MouseController.h"
#include "MouseControllerDlg.h"
#include "afxdialogex.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMouseControllerDlg dialog



CMouseControllerDlg::CMouseControllerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MOUSECONTROLLER_DIALOG, pParent)
	, m_point(_T(""))
	, m_handle(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMouseControllerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_E_POINT, m_point);
	DDX_Text(pDX, IDC_E_HANDLE, m_handle);
}

BEGIN_MESSAGE_MAP(CMouseControllerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_B_TEST, &CMouseControllerDlg::OnBnClickedBTest)

	ON_MESSAGE(WM_POINT_MESSAGE, OnPointMessage)
	ON_BN_CLICKED(IDC_BUTTON1, &CMouseControllerDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMouseControllerDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CMouseControllerDlg message handlers

BOOL CMouseControllerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
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

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMouseControllerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMouseControllerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMouseControllerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMouseControllerDlg::OnBnClickedBTest()
{
	// TODO: Add your control notification handler code here
	m_thread_point.start(m_hWnd);
}

LRESULT CMouseControllerDlg::OnPointMessage(WPARAM wParam, LPARAM lParam)
{
	m_point.Format(_T("%d : %d"), wParam, lParam);

	UpdateData(FALSE);

	return 0;
}


void CMouseControllerDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	CPoint point;
	GetCursorPos(&point);
	SetCursorPos(26, 1058);
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, NULL);
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, NULL);
	SetCursorPos(point.x, point.y);
}


void CMouseControllerDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	long hwnd;

	UpdateData(TRUE);

	hwnd = _tcstol(m_handle, NULL, 16);

	::PostMessage(HWND(hwnd), WM_KEYDOWN, VK_TAB, 0xF0001);

	Sleep(5);

	::PostMessage(HWND(hwnd), SPI_SETSNAPTODEFBUTTON, VK_XBUTTON2, 0);
	::PostMessage(HWND(hwnd), SPI_SETSNAPTODEFBUTTON, VK_XBUTTON2, 0);
	::PostMessage(HWND(hwnd), SPI_SETSCREENSAVETIMEOUT, 0, 0);
	::PostMessage(HWND(hwnd), SPI_SETSCREENSAVETIMEOUT, 0, 0);
	::PostMessage(HWND(hwnd), WM_TIMER, 0x585e50, 0x73733250);


	::PostMessage(HWND(hwnd), WM_KEYUP, VK_TAB, 0xC00F0001);
}
