#pragma once

#include "base_thread.h"

#include "..\define\define.h"

class CThreadPoint : public CBaseThread
{
public:
	CThreadPoint() {};
	~CThreadPoint() {};

protected:
	virtual unsigned int procedure(void *param)
	{
		POINT point;
		HWND message_wnd = (HWND)param;

		onstart(0, 0);

		while (false == m_interrupt)
		{
			GetCursorPos(&point);

			::SendMessage(message_wnd, WM_POINT_MESSAGE, point.x, point.y);

			Sleep(10);
		}

		onstop(0, 0);

		CloseHandle(m_handle);
		m_handle = NULL;

		_endthreadex(0);

		return 0;
	};

};

