//
//  SettingLayer.h
//  testcocos2d-x
//
//  Created by wangwb on 13-11-13.
//
//

#ifndef __testcocos2d_x__SettingLayer__
#define __testcocos2d_x__SettingLayer__

#include "commonheader.h"
//#include "HelloWorldScene.h"
class SettingLayer : public cocos2d::CCLayer
{
public:
    CREATE_FUNC(SettingLayer);
    bool init();
    
    //设置音乐和音效按钮的状态
    void setSoundAndMusicVolume(float soundVolume, float musicVolume);
protected:
    void resume();
    void sound();
    void music();
    void reset();
    void quit();
    
    
    void createMenu();
    void createBackground();
    
    cocos2d::CCMenuItemToggle* _sound;
    cocos2d::CCMenuItemToggle* _music;
};
#endif /* defined(__testcocos2d_x__SettingLayer__) */
