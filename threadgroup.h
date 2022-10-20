#pragma once

#include <vector>
#include "base_thread.h"

class CThreadGroup
{
public:
	CThreadGroup()
	{
		m_threads.clear();
	}

	~CThreadGroup()
	{
		std::vector<CBaseThread*>::iterator it;

		for (it = m_threads.begin(); it != m_threads.end();)
		{
			delete (*it);
			it = m_threads.erase(it);
		}
	}
private:
	std::vector<CBaseThread*> m_threads;
public:
	void start_thread(CBaseThread* thread, void *param)
	{
		thread->start(param);
		m_threads.push_back(thread);
	}

	void start_threads(void)
	{
		std::vector<CBaseThread*>::iterator it;

		for (it = m_threads.begin(); it != m_threads.end(); it++)
			(*it)->start(NULL);
	}

	void stop_threads(unsigned long milliseconds = INFINITE)
	{
		std::vector<CBaseThread*>::iterator it;

		for (it = m_threads.begin(); it != m_threads.end(); it++)
			(*it)->stop(milliseconds);
	}

	void suspend_threads(void)
	{
		std::vector<CBaseThread*>::iterator it;

		for (it = m_threads.begin(); it != m_threads.end(); it++)
			(*it)->suspend();
	}

	void resume_threads(void)
	{
		std::vector<CBaseThread*>::iterator it;

		for (it = m_threads.begin(); it != m_threads.end(); it++)
			(*it)->resume();
	}
public:
	void add_thread(CBaseThread* thread)
	{
		m_threads.push_back(thread);
	}
};
