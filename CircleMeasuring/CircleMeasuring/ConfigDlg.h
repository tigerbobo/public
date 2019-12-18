#pragma once

#include "config\config.h"

// CConfigDlg dialog

class CConfigDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CConfigDlg)

public:
	CConfigDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CConfigDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONFIG_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
public:
	afx_msg void OnBnClickedCheckBackgroundAi();
	afx_msg void OnLvnItemchangedListPixels(NMHDR *pNMHDR, LRESULT *pResult);
public:
	CConfig m_config;
public:
	int m_auto_identification;
	int m_black_background;

	double m_color_threshold;

	double m_target_length;
	double m_length_per_pixel;
	double m_compensation;
public:
	afx_msg void OnBnClickedBOk();
	afx_msg void OnBnClickedBCancel();
	
	afx_msg void OnBnClickedBSet();
	afx_msg void OnBnClickedBDelete();

	double m_standard_length;
};
