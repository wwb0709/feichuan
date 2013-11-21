#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "BaseResponseMsg.h"



class HelloWorld : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuSendCallback(CCObject* pSender);
	void msgCallBack(BaseResponseMsg* baseResponseMsg);
    void notContCallBack(BaseResponseMsg* baseResponseMsg);
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
	int i;
	void createConte(float time);
    BaseResponseMsg* baseResponseMsg;
};

#endif // __HELLOWORLD_SCENE_H__
