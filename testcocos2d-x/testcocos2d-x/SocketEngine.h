//
//  SocketEngine.h
//  testcocos2d-x
//
//  Created by wangwb on 13-11-15.
//
//

#ifndef __testcocos2d_x__SocketEngine__
#define __testcocos2d_x__SocketEngine__

#include <iostream>
#include "socketcc.h"
#include "commonheader.h"

using namespace std;


class SoketEngineDelegate
{

public:
    virtual ~SoketEngineDelegate() {};
    
    /**
     * This method is called when an edit box gains focus after keyboard is shown.
     * @param editBox The edit box object that generated the event.
     */
    virtual void recvData(char *content) {};
};



class SocketEngine:public CCObject
{
private:
    SocketEngine();
    void init();
    ~SocketEngine();
public:
    void CreateSocket();

    static SocketEngine* sharedSocketEngine(SoketEngineDelegate* delegate);
    
    void sendData(const char* data);
    
    static void* reciveData(void* object);
    
    void setSoketDelegate( SoketEngineDelegate* delegate);
private:
    TCPClientSocket *m_socket;
    
    IPAddress address;
    
    pthread_t pthead_rec;
    

    
    char outData[20];
    
protected:
    SoketEngineDelegate* socketDelegate;
};

#endif /* defined(__testcocos2d_x__SocketEngine__) */
