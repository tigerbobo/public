// ConfigDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CircleMeasuring.h"
#include "ConfigDlg.h"
#include "afxdialogex.h"


// CConfigDlg dialog

IMPLEMENT_DYNAMIC(CConfigDlg, CDialogEx)

CConfigDlg::CConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CONFIG_DIALOG, pParent)
	, m_auto_identification(0)
	, m_black_background(0)
	, m_color_threshold(0)
	, m_target_length(0)
	, m_length_per_pixel(0)
	, m_compensation(0)
	, m_standard_length(0)
{

}

CConfigDlg::~CConfigDlg()
{
}

void CConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_BACKGROUND_AI, m_auto_identification);
	DDX_Check(pDX, IDC_CHECK_BLACK_BACKGROUND, m_black_background);
	DDX_Text(pDX, IDC_E_COLOR_THRESHOLD, m_color_threshold);
	DDX_Text(pDX, IDC_E_TARGET_LENGTH, m_target_length);
	DDX_Text(pDX, IDC_E_MM_PER_PIXEL, m_length_per_pixel);
	DDX_Text(pDX, IDC_E_COMPENSATION, m_compensation);
//	DDX_Text(pDX, IDC_E_STANDARD_LENGTH, m_standard_length);
}


BEGIN_MESSAGE_MAP(CConfigDlg, CDialogEx)
	ON_BN_CLICKED(IDC_B_OK, &CConfigDlg::OnBnClickedBOk)
	ON_BN_CLICKED(IDC_B_CANCEL, &CConfigDlg::OnBnClickedBCancel)
	ON_BN_CLICKED(IDC_CHECK_BACKGROUND_AI, &CConfigDlg::OnBnClickedCheckBackgroundAi)
	ON_BN_CLICKED(IDC_B_SET, &CConfigDlg::OnBnClickedBSet)
	ON_BN_CLICKED(IDC_B_DELETE, &CConfigDlg::OnBnClickedBDelete)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_PIXELS, &CConfigDlg::OnLvnItemchangedListPixels)
END_MESSAGE_MAP()


// CConfigDlg message handlers


BOOL CConfigDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	m_target_length = m_config.m_target_length;
	m_length_per_pixel = m_config.m_length_per_pixel;
	m_compensation = m_config.m_compensation;

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CConfigDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if (WM_KEYDOWN == pMsg->message)
	{
		if (VK_RETURN == pMsg->wParam)
			return TRUE;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CConfigDlg::OnLvnItemchangedListPixels(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	// TODO: Add your control notification handler code here


	*pResult = 0;
}

void CConfigDlg::OnBnClickedCheckBackgroundAi()
{
	// TODO: Add your control notification handler code here
}


void CConfigDlg::OnBnClickedBOk()
{
	// TODO: Add your control notification handler code here
	CString str;

	str.Format(_T("%f"), m_compensation);
	AfxMessageBox(str);

	UpdateData(TRUE);

	str.Format(_T("%f"), m_compensation);
	AfxMessageBox(str);

	m_config.m_auto_identification = m_auto_identification;
	m_config.m_black_background = m_black_background;

	m_config.m_color_threshold = m_color_threshold;

	m_config.m_target_length = m_target_length;
	m_config.m_length_per_pixel = m_length_per_pixel;
	m_config.m_compensation = m_compensation;

	m_config.set_config(_T("config.ini"));

	OnOK();
}


void CConfigDlg::OnBnClickedBCancel()
{
	// TODO: Add your control notification handler code here
}





void CConfigDlg::OnBnClickedBSet()
{
	// TODO: Add your control notification handler code here
}


void CConfigDlg::OnBnClickedBDelete()
{
	// TODO: Add your control notification handler code here
}



