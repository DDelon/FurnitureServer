
#include "Task.h"
int Task::_count = 0;
Task::Task(std::function<void(MyThread *)> func) :
_id(_count++),
_func(func)
{
}

Task::~Task()
{
}

void Task::runTask(MyThread *pExcuteThread)
{
	_func(pExcuteThread);
}
