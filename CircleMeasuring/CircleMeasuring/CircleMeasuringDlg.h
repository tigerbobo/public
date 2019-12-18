
// CircleMeasuringDlg.h : header file
//

#pragma once

#include "config\config.h"


// CCircleMeasuringDlg dialog
class CCircleMeasuringDlg : public CDialogEx
{
// Construction
public:
	CCircleMeasuringDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CIRCLEMEASURING_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnClose();
public:
	afx_msg void OnFileOpenImage();
	afx_msg void OnFileSaveImage();
	afx_msg void OnFileExit();

	afx_msg void OnConfigConfig();

	afx_msg void OnControlSoftwaretrigger();

	afx_msg void OnHelpAbout();
public:
	CConfig m_config;
};
