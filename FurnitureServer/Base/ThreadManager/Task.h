#ifndef __TASK_H__
#define __TASK_H__

#include <functional>
#include <list>
#include <thread>
#include <iostream>

class MyThread;

class Task
{
public:
	Task(std::function<void(MyThread *)> func);
	~Task(void);

public:
	int getId() { return _id; }

	void runTask(MyThread *pExcuteThread);

private:
	static int _count;

	int _id;

	std::function<void (MyThread *)> _func;
};

#endif