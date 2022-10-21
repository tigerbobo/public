#pragma once

#include <vector>
#include <tchar.h>
#include <process.h>
#include <Windows.h>

typedef struct _thread_param
{
	void *wParam;
	void *lParam;
}thread_param;

class threadlistener
{
public:
	threadlistener() {};
	~threadlistener() {};
public:
	virtual void onstart(WPARAM wParam, LPARAM lParam) = 0;
	virtual void onstop(WPARAM wParam, LPARAM lParam) = 0;
};

class CBaseThread
{
public:
	CBaseThread()
	{
		m_handle = NULL;

		m_listeners.clear();
	};

	~CBaseThread()
	{
		stop();
	};
protected:
	// thread handle
	void *m_handle;

	// thread control
	volatile bool m_interrupt;

	// thread listeners
	std::vector<threadlistener*> m_listeners;
protected:
	virtual unsigned int procedure(void *param)
	{
		onstart(0, 0);
		OutputDebugString(_T("thread start\n"));

		while (false == m_interrupt)
		{
			OutputDebugString(_T("thread running\n"));
			Sleep(1000);
		}

		onstop(0, 0);
		OutputDebugString(_T("thread stop\n"));
		
		CloseHandle(m_handle);
		m_handle = NULL;

		_endthreadex(0);

		return 0;
	};
protected:
	void onstart(WPARAM wParam, LPARAM lParam)
	{
		for (size_t i = 0; i < m_listeners.size(); i++)
			m_listeners[i]->onstart(wParam, lParam);
	};

	void onstop(WPARAM wParam, LPARAM lParam)
	{
		for (size_t i = 0; i < m_listeners.size(); i++)
			m_listeners[i]->onstop(wParam, lParam);
	};

	static unsigned int __stdcall iteration(void *param)
	{
		thread_param *threadParam = (thread_param*)param;
		CBaseThread *pthread = (CBaseThread*)(threadParam->lParam);

		CoInitialize(NULL);
		pthread->procedure(threadParam->wParam);
		CoUninitialize();

		delete threadParam;

		return 0;
	};
public:
	virtual void start(void *param)
	{
		unsigned int threadid;
		thread_param *threadParam = new thread_param;

		if (m_handle)
			return;

		m_interrupt = false;

		threadParam->wParam = param;
		threadParam->lParam = this;

		m_handle = (void*)_beginthreadex(NULL, 0, &iteration, threadParam, 0, &threadid);
	};

	virtual void stop(unsigned long milliseconds = INFINITE)
	{
		if (NULL == m_handle)
			return;

		m_interrupt = true;

		WaitForSingleObject(m_handle, INFINITE);

		CloseHandle(m_handle);
		m_handle = NULL;
	};

	virtual void suspend(void)
	{
		if (m_handle)
			SuspendThread(m_handle);
	};

	virtual void resume(void)
	{
		if (m_handle)
			ResumeThread(m_handle);
	};
public:
	void add_listener(threadlistener* listener)
	{
		m_listeners.push_back(listener);
	};
};
