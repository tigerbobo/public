
// MouseControllerDlg.h : header file
//

#pragma once

#include "thread\thread_point.h"


// CMouseControllerDlg dialog
class CMouseControllerDlg : public CDialogEx
{
// Construction
public:
	CMouseControllerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MOUSECONTROLLER_DIALOG };
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
	afx_msg void OnBnClickedBTest();
	CString m_point;
public:
	CThreadPoint m_thread_point;
public:
	afx_msg LRESULT OnPointMessage(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedButton1();
	CString m_handle;
	afx_msg void OnBnClickedButton2();
};
