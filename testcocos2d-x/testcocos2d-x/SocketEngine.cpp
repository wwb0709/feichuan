//
//  SocketEngine.cpp
//  testcocos2d-x
//
//  Created by wangwb on 13-11-15.
//
//

#include "SocketEngine.h"

#define MAX_RECV_SIZE 1024
#define SERVER_IP "192.168.0.60"
#define SERVER_PORT 8000

#define SOKETTIMEOUT 10

static SocketEngine* _sharedSocketEngine = NULL;

SocketEngine::SocketEngine():m_socket(NULL),socketDelegate(NULL)
{


}
void SocketEngine::init()
{
    //创建socket
    CreateSocket();

}
SocketEngine::~SocketEngine()
{
    if (m_socket!=NULL) {
        delete m_socket;
        m_socket = NULL;
    }
}
SocketEngine* SocketEngine::sharedSocketEngine(SoketEngineDelegate* delegate)
{
    if (_sharedSocketEngine==NULL) {
        _sharedSocketEngine = new SocketEngine();
        _sharedSocketEngine->init();
        _sharedSocketEngine->setSoketDelegate(delegate);
    }
    
    return _sharedSocketEngine;
}

void SocketEngine::CreateSocket()
{
    const char* serverIp=SERVER_IP;
    
    //定义客户端的ip，写客户端的ip
    
    int serverPort=SERVER_PORT;
    
    //定义客户端的端口
    
    //处理异常
    
    try {
        
        address.SetHostName(serverIp, false);
        
        //false的意思是是否用这个ip与网络连接
        
        m_socket=new TCPClientSocket(address,serverPort);
        
        // 设置超时
        
        struct timeval timeout;
        
        socklen_t len = sizeof(timeout);
        
        timeout.tv_sec = SOKETTIMEOUT;
        
        m_socket -> SetSockOpt(SOL_SOCKET, SO_RCVTIMEO, &timeout, len);
        
    } catch (SocketException &excep) {
        
        cout<<"Socket Exception:"<<(const  char *)excep<<endl;
        
    }
    
    catch(...){
        
        //这是c++里面的例外处理，catch(...)的意思是其他例外的出现
        
        cout<<"other error"<<endl;
        
    }
    
//    if(pthread_create(&pthead_rec, NULL, recivePublicData, this)!=0){
//        
//        //pthead_recx线程标示，reciveData回调函数， m_socket传入的参数
//        
//        cout<<"创建reciveData失败"<<endl;
//        
//    }
    
    
}
void SocketEngine::sendData(const char* data)
{
    if (m_socket==NULL) {
        CreateSocket();
    }
    
    if (m_socket==NULL) {
        cout<<"Socket创建失败"<<endl;
        return;
    }
    
    try {
    cocos2d::CCLog("send() datas : %s \n\n",data);
    m_socket->SendData(data, strlen(data)+1);
    }catch (SocketException &excep) {

        cout<<"收到参数意外"<<endl;

        cocos2d::CCLog("sendData recvDatas Error: %s \n\n",(const char*)excep);

        return;
    }
    
//    strcpy(outData, data);
    cout<<"开始线程接受Socket数据"<<endl;
    if(pthread_create(&pthead_rec, NULL, reciveData, this)!=0){
        
        //pthead_recx线程标示，reciveData回调函数， m_socket传入的参数
        

        cout<<"创建reciveData失败"<<endl;
        
    }
    
}
void* SocketEngine::reciveData(void* object){
    SocketEngine *scoketClient =( SocketEngine *) object;
    TCPClientSocket *mysocket=scoketClient->m_socket;
    
    bool tag = true;
    //while (1)
    {
        
        cout<<"reciveData"<<endl;
        
        unsigned char pcRecvBuf[MAX_RECV_SIZE];
        
        //在栈中建立的数组，用于盛放接收来的数据
        
        try {
            
//            cocos2d::CCLog("send() datas : %s \n\n",scoketClient->outData);
            
//            mysocket->SendData(scoketClient->outData, strlen(scoketClient->outData)+1);
            
            int iBytesRec=mysocket->RecvData(pcRecvBuf, MAX_RECV_SIZE);
            
            cout<<"收到服务端传来"<<iBytesRec<<endl;
            
            pcRecvBuf[iBytesRec]=0;
            cout<<pcRecvBuf<<endl;
            char* p = (char*)pcRecvBuf;
//            scoketClient->callBack(p);
            if (scoketClient->socketDelegate!=NULL) {
                scoketClient->socketDelegate->recvData(p);
            }
            cocos2d::CCLog("reciveData()===recvDatas : %s \n\n",p);
            // 处理收到的数据，如果他的最后一位是0，则表示接收数据完成
            
            
        } catch (SocketException &excep) {
            
          
            
            tag = false;
            cout<<"收到参数意外"<<endl;
            
            cocos2d::CCLog("recvDatas Error: %s \n\n",(const char*)excep);
           
     
            
            //            scoketClient->callBack("收到参数意外");
            
        }catch (...){
            tag = false;
            cout<<"其他例外"<<endl;
            
            cocos2d::CCLog("recvDatas Error\n\n");
            //            scoketClient->callBack("收到参数意外");
            
  
        }
        
        cocos2d::CCLog("net disconnect \n\n");
        
    }
    
    cocos2d::CCLog("end reciveData \n\n");
    
}


void SocketEngine::setSoketDelegate( SoketEngineDelegate* delegate)
{
    socketDelegate = delegate;
}