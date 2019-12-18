
// CircleMeasuringDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CircleMeasuring.h"
#include "CircleMeasuringDlg.h"
#include "afxdialogex.h"

#include "exception\exceptionplus.h"

#include "ConfigDlg.h"

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


// CCircleMeasuringDlg dialog



CCircleMeasuringDlg::CCircleMeasuringDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CIRCLEMEASURING_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCircleMeasuringDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCircleMeasuringDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_COMMAND(ID_FILE_OPEN_IMAGE, &CCircleMeasuringDlg::OnFileOpenImage)
	ON_COMMAND(ID_FILE_SAVE_IMAGE, &CCircleMeasuringDlg::OnFileSaveImage)
	ON_COMMAND(ID_FILE_EXIT, &CCircleMeasuringDlg::OnFileExit)
	ON_COMMAND(ID_CONFIG_CONFIG, &CCircleMeasuringDlg::OnConfigConfig)
	ON_COMMAND(ID_CONTROL_SOFTWARETRIGGER, &CCircleMeasuringDlg::OnControlSoftwaretrigger)
	ON_COMMAND(ID_HELP_ABOUT, &CCircleMeasuringDlg::OnHelpAbout)
END_MESSAGE_MAP()


// CCircleMeasuringDlg message handlers

BOOL CCircleMeasuringDlg::OnInitDialog()
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
	try
	{
		m_config.get_config(_T("config.ini"));
	}
	catch (CExceptionPlus &e)
	{
		for (size_t i = 0; i < e.get_exception().size(); i++)
			MessageBox((e.get_exception()[i].category + _T(" : ") + e.get_exception()[i].name + _T(" : ") + e.get_exception()[i].result).c_str(), _T("example"), MB_OK | MB_ICONERROR);
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCircleMeasuringDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCircleMeasuringDlg::OnPaint()
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
HCURSOR CCircleMeasuringDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



BOOL CCircleMeasuringDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CCircleMeasuringDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default

	CDialogEx::OnClose();
}


void CCircleMeasuringDlg::OnFileOpenImage()
{
	// TODO: Add your command handler code here
}


void CCircleMeasuringDlg::OnFileSaveImage()
{
	// TODO: Add your command handler code here
}


void CCircleMeasuringDlg::OnFileExit()
{
	// TODO: Add your command handler code here
}


void CCircleMeasuringDlg::OnConfigConfig()
{
	// TODO: Add your command handler code here
	CConfigDlg dlg;

	dlg.m_config = m_config;
	if (IDOK == dlg.DoModal())
	{
		m_config = dlg.m_config;
	}
}


void CCircleMeasuringDlg::OnControlSoftwaretrigger()
{
	// TODO: Add your command handler code here
}


void CCircleMeasuringDlg::OnHelpAbout()
{
	// TODO: Add your command handler code here
}
