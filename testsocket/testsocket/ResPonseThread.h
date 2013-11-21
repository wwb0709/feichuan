#pragma once
// ¥À¿‡÷˜“™ ¥¶¿Ì∑˛ŒÒ∆˜Õ∆ÀÕπ˝¿¥µƒœ˚œ¢
#include "pthread.h"
#include "cocos2d.h"
#include "BaseResponseMsg.h"
typedef void (cocos2d::CCObject::*ResPonseThreadEvent)(BaseResponseMsg*);
#define callFunc_selectormsg(_SELECTOR) (ResPonseThreadEvent)(&_SELECTOR)

#define M_ADDCALLBACKEVENT(varName)\
protected: cocos2d::CCObject* m_##varName##listener;ResPonseThreadEvent varName##selector;\
public: void add##varName##ListenerEvent(ResPonseThreadEvent m_event,cocos2d::CCObject* listener)  { m_##varName##listener=listener;varName##selector=m_event; }

class ResPonseThread
{
public:	
	~ResPonseThread(void);
	static ResPonseThread*   GetInstance(); //获取该类的单例
	int start (void * =NULL); //函数是启动函数，其输入参数无类型指针
	void stop();     //函数中止当前线程
	void sleep (int tesec); //函数让当前线程休眠给定时间，单位是微妙
	void detach();   //
	void * wait();
    	
private:
	ResPonseThread(void);
	pthread_t handle; 
	bool started;
	bool detached;
	static void * threadFunc(void *);
	static ResPonseThread* m_pInstance;	
	M_ADDCALLBACKEVENT(msg);// 聊天回调函数
	M_ADDCALLBACKEVENT(notcon);//断网回调函数
	
};
