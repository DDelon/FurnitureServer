#ifndef __MY_THREAD_H__
#define __MY_THREAD_H__

#include <functional>
#include <thread>
#include <mutex>

class Task;

class MyThread
{
public:
	enum Status
	{
		FREE,
		BUSY,
	};
public:
	MyThread();
	~MyThread();

public:
	int getId() { return _id; }

	void linkTask(Task *pTask);

	Task *getTask() { return _pTask; }

	void stop();

	bool lock();

	void unlock();

private:
	void loop();

private:
	static int _count;

	int _id;

	int _status;

	Task *_pTask;

	std::thread *_pThread;
};

#endif