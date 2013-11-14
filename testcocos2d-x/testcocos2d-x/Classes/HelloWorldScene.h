#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "commonheader.h"
#include "GameLayer.h"
#include "SettingLayer.h"



class HelloWorld : public CCLayer
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();

    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static CCScene* scene();
    
 
    
    void menuSettingCallback(CCObject* pSender);

    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(HelloWorld);
    

    
    void onExit();
//    void onEnter();
    
    //退出
    void quitGame();
    //暂停
    void pause();
    //继续
    void resume();
    //重新开始
    void restart();
    
    void operateAllSchedulerAndActions(CCNode* node, OperateFlag flag);
    
   
public:
    
    GameLayer* gameLayer;
    SettingLayer* settingLayer;
    
    
    CCMenu* pSettingMenu;
    
    
//    void onEnterTransitionDidFinish();
};

#endif // __HELLOWORLD_SCENE_H__
