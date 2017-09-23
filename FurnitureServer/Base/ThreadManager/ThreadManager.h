/*********************************************************************************
   *Copyright(C),2010-2011,Your Company
   *FileName:  //ThreadManager
   *Author:    //����ʤ
   *Version:   //1.0
   *Date:	   //2015-05-22
   *Description:  //�̵߳Ĺ���
                 //����FreeThread���BusyThread���TaskManager��
                 //��������װ��CTask�� ���̷߳�װ��CMyThread��
				 
   *Others:  //��������˵��
   *Function List:  //��Ҫ�����б�ÿ����¼Ӧ���������������ܼ�Ҫ˵��
      1.��������
      2.��������
   *History:  //�޸���ʷ��¼�б�ÿ���޸ļ�¼Ӧ�����޸����ڡ��޸��߼��޸����ݼ��
      1.Date:	//2017-09-16
        Author:	//����ʤ
        Modification:	//���̹߳�����
						//
      2.��������
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
	*function: ��ȡ�̹߳�����
	*
	*return: ThreadManager *
	*/
	static ThreadManager *getInstance();
	/**
	*function: ���������̷߳�������б�
	*
	*args:
	*/
	void createThread();
	/**
	*function: �������
	*
	*/
	void addTask(std::function<void(MyThread *)> task);
	/**
	*function: ֹͣ�߳� ���̼߳�������б�
	*
	*/
	void stopThread(int threadId);
	/**
	*function: ֹͣ���� ɾ������
	*
	*/
	void stopTask(int taskId);
	/**
	*function: ��ȡ�����߳��� 
	*
	*/
	int getFreeThreadSize() { return _freeThreadVec.size(); }
	/**
	*function: ��ȡæµ�߳���
	*
	*/
	int getBusyThreadSize() { return _busyThreadVec.size(); }
	/**
	*function: ��ȡ��������
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