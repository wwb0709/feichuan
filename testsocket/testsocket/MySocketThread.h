//
//  MySocketThread.h
//  testsocket
//
//  Created by wangwb on 13-11-19.
//
//

#ifndef __testsocket__MySocketThread__
#define __testsocket__MySocketThread__

#include <iostream>
#include "socketcc.h"
class MySocketThread
{
public:
	~MySocketThread(void);
	static MySocketThread*   GetInstance();
	int start();
	TCPClientSocket* getSocket();
	int state;// 0 表示连接成功 1 表示连接失败
	TCPClientSocket* csocket;
	void stop();//函数中止当前线程
private:
	pthread_t pid;
	static void* start_thread(void *);//静态成员函数 相当于c中的全局函数
	MySocketThread(void);
private:
	static MySocketThread* m_pInstance;
};
#endif /* defined(__testsocket__MySocketThread__) */
