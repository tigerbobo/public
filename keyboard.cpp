#define WM_POINT_MESSAGE			WM_USER + 101

afx_msg LRESULT OnPointMessage(WPARAM wParam, LPARAM lParam);

ON_MESSAGE(WM_POINT_MESSAGE, OnPointMessage)


m_thread_point.start(m_hWnd);


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

