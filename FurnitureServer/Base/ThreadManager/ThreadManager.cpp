#include "ThreadManager.h"
#include "MyThread.h"
#include "Task.h"

ThreadManager::ThreadManager()
{
	for (int i = 0; i < THEAD_INIT_NUM; ++i)
	{
		this->createThread();
	}
}
ThreadManager::~ThreadManager()
{
	for (auto iter : _freeThreadVec)
	{
		delete iter;
	}
	for (auto iter : _busyThreadVec)
	{
		delete iter;
	}
	for (auto iter : _taskVec)
	{
		delete iter;
	}

	_freeThreadVec.clear();
	_busyThreadVec.clear();
	_taskVec.clear();
}

static ThreadManager *pThreadManager = NULL;
ThreadManager *ThreadManager::getInstance()
{
	if (pThreadManager == NULL)
		pThreadManager = new ThreadManager();
	return pThreadManager;
}

void ThreadManager::createThread()
{
	MyThread *pThread = new MyThread();
	_freeThreadVec.push_back(pThread);
}

void ThreadManager::addTask(std::function<void(MyThread *)> task)
{
	Task *pTask = new Task(task);
	_taskVec.push_back(pTask);

	//moving thread from freeThreadVec to busyThreadVec
	auto iter = _freeThreadVec.begin();
	if (iter == _freeThreadVec.end())
		return;

	MyThread *pThread = *iter;
	_freeThreadVec.erase(iter);
	pThread->stop();
	pThread->linkTask(pTask);
	_busyThreadVec.push_back(pThread);
}

void ThreadManager::stopThread(int threadId)
{
	for (auto iter = _busyThreadVec.begin(); iter != _busyThreadVec.end(); ++iter)
	{
		if ((*iter)->getId() == threadId)
		{
			MyThread *pThread = *iter;
			Task *pTask = pThread->getTask();
			int taskId = pTask->getId();
			this->stopTask(taskId);
			pTask = this->getTask();

			if (pTask != nullptr)
			{
				pThread->linkTask(pTask);
			}
			else
			{
				pThread->stop();
				_busyThreadVec.erase(iter);
				_freeThreadVec.push_back(pThread);
			}
			break;
		}
	}
}

void ThreadManager::stopTask(int taskId)
{
	for (auto iter = _taskVec.begin(); iter != _taskVec.end(); ++iter)
	{
		if ((*iter)->getId() == taskId)
		{
			Task *pTask = (*iter);
			_taskVec.erase(iter);
			delete pTask;
			break;
		}
	}
}

Task *ThreadManager::getTask()
{
	for (auto iter = _taskVec.begin(); iter != _taskVec.end(); ++iter)
	{
		Task *pTask = *iter;
		_taskVec.erase(iter);
		return pTask;
	}

	return nullptr;
}