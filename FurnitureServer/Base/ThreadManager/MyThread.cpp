#include "MyThread.h"
#include <windows.h>
#include "Task.h"

static std::mutex mux;

int MyThread::_count = 0;

MyThread::MyThread() :
_id(_count++),
_status(Status::FREE)
{
	_pTask = nullptr;
	_pThread = new std::thread([&]() {this->loop(); });
	_pThread->detach();
}

MyThread::~MyThread()
{
}

void MyThread::linkTask(Task *pTask)
{
	_pTask = pTask;
	_status = Status::BUSY;
}

bool MyThread::lock()
{
	return mux.try_lock();
}

void MyThread::unlock()
{
	mux.unlock();
}

void MyThread::loop()
{
	while (true)
	{
		if (_status == Status::BUSY)
		{
			_pTask->runTask(this);
		}
		else if (_status == Status::FREE)
		{
			//std::cout << "free" << std::endl;
			Sleep(50);
		}
	}
}

void MyThread::stop()
{
	_pTask = nullptr;
	_status = Status::FREE;
}
