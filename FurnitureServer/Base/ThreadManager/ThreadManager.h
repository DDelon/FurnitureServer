/*********************************************************************************
   *Copyright(C),2010-2011,Your Company
   *FileName:  //ThreadManager
   *Author:    //吴晓胜
   *Version:   //1.0
   *Date:	   //2015-05-22
   *Description:  //线程的管理
                 //包含FreeThread类和BusyThread类和TaskManager类
                 //将函数封装成CTask类 将线程封装成CMyThread类
				 
   *Others:  //其他内容说明
   *Function List:  //主要函数列表，每条记录应包含函数名及功能简要说明
      1.…………
      2.…………
   *History:  //修改历史记录列表，每条修改记录应包含修改日期、修改者及修改内容简介
      1.Date:	//2017-09-16
        Author:	//吴晓胜
        Modification:	//简化线程管理类
						//
      2.…………
 **********************************************************************************/


#ifndef __THREAD_MANAGER_H__
#define __THREAD_MANAGER_H__

#define THEAD_INIT_NUM 5

#include <functional>
#include <vector>
#include "Task.h"
#include "MyThread.h"

class ThreadManager
{
private:
	ThreadManager(void);
	~ThreadManager(void);
public:
	/**
	*function: 获取线程管理单例
	*
	*return: ThreadManager *
	*/
	static ThreadManager *getInstance();
	/**
	*function: 创建空闲线程放入空闲列表
	*
	*args:
	*/
	void createThread();
	/**
	*function: 添加任务
	*
	*/
	void addTask(std::function<void(MyThread *)> task);
	/**
	*function: 停止线程 将线程加入空闲列表
	*
	*/
	void stopThread(int threadId);
	/**
	*function: 停止任务 删除任务
	*
	*/
	void stopTask(int taskId);
	/**
	*function: 获取空闲线程数 
	*
	*/
	int getFreeThreadSize() { return _freeThreadVec.size(); }
	/**
	*function: 获取忙碌线程数
	*
	*/
	int getBusyThreadSize() { return _busyThreadVec.size(); }
	/**
	*function: 获取任务数量
	*
	*/
	int getTaskSize() { return _taskVec.size(); }

private:
	Task *getTask();
	
private:
	static ThreadManager *_pInstance;
	
	std::vector<MyThread *> _freeThreadVec;
	std::vector<MyThread *> _busyThreadVec;
	std::vector<Task *> _taskVec;
};

#endif