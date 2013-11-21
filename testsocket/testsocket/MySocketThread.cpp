//
//  MySocketThread.cpp
//  testsocket
//
//  Created by wangwb on 13-11-19.
//
//
#define MAX_RECV_SIZE 1024
#define SERVER_IP "192.168.0.60"
#define SERVER_PORT 8000

#define SOKETTIMEOUT 10

#include "MySocketThread.h"
#include "cocos2d.h"
#include "ResPonseThread.h"

USING_NS_CC;
using namespace std;
int MySocketThread::start(){
	int errCode = 0;
	do{
		pthread_attr_t tAttr;
		errCode = pthread_attr_init(&tAttr);
		CC_BREAK_IF(errCode!=0);
		//但是上面这个函数其他内容则主要为你创建的线程设定为分离式
		errCode = pthread_attr_setdetachstate(&tAttr, PTHREAD_CREATE_DETACHED);
		if (errCode!=0) {
			pthread_attr_destroy(&tAttr);
			break;
		}
		errCode = pthread_create(&pid,&tAttr,start_thread,this);
	}while (0);
	return errCode;
}


void* MySocketThread::start_thread(void *arg)   {
    
    MySocketThread* thred=(MySocketThread*)arg;
    const char* serverIp=SERVER_IP;
    
    //定义客户端的ip，写客户端的ip
    
    int serverPort=SERVER_PORT;
    
    //定义客户端的端口
    
    //处理异常
    IPAddress address;
    try {
        
        address.SetHostName(serverIp, false);
        
        //false的意思是是否用这个ip与网络连接
        
       TCPClientSocket *socket=new TCPClientSocket(address,serverPort);
        
        // 设置超时
        
        struct timeval timeout;
        
        socklen_t len = sizeof(timeout);
        
        timeout.tv_sec = SOKETTIMEOUT;
        
        socket->SetSockOpt(SOL_SOCKET, SO_RCVTIMEO, &timeout, len);
        thred->csocket = socket;
//        thred->csocket->SetSockOpt(SOL_SOCKET, SO_RCVTIMEO, &timeout, len);
        
		 thred->state=0;
//		 ResPonseThread::GetInstance()->start();//// 启动响应参数
        
    } catch (SocketException &excep) {
        
        cout<<"Socket Exception:"<<(const  char *)excep<<endl;
        thred->state=1;
    }
    
    catch(...){
        thred->state=1;
        //这是c++里面的例外处理，catch(...)的意思是其他例外的出现
        
        cout<<"other error"<<endl;
        
    }
    
    
    

//	ODSocket cdSocket;
//	cdSocket.Init();
//	bool isok=cdSocket.Create(AF_INET,SOCK_STREAM,0);
//	bool iscon=cdSocket.Connect("127.0.0.1",8000);
//	if(iscon){
//		thred->state=0;
//		ResPonseThread::GetInstance()->start();//// 启动响应参数
//		CCLOG("conection");
//	}else{
//		thred->state=1;
//	}
//	thred->csocket=cdSocket;
	return NULL;
}
TCPClientSocket* MySocketThread::getSocket(){
	return this->csocket;
}

MySocketThread* MySocketThread::m_pInstance=new MySocketThread;
MySocketThread* MySocketThread::GetInstance(){
	return m_pInstance;
}

void MySocketThread::stop(){
	pthread_cancel(pid);
	pthread_detach(pid);
}

MySocketThread::MySocketThread(void)
{
    
}


MySocketThread::~MySocketThread(void)
{
	if(m_pInstance!=NULL){
		delete m_pInstance;
	}
}
