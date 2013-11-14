//
//  SettingLayer.cpp
//  testcocos2d-x
//
//  Created by wangwb on 13-11-13.
//
//

#include "SettingLayer.h"
#include "HelloWorldScene.h"
#include "PersonalAudioEngine.h"
USING_NS_CC;
bool SettingLayer::init()
{
    if(CCLayer::init()){
        this->createBackground();
        this->createMenu();
        return true;
    }
    return false;
}
void SettingLayer::createBackground()
{
    CCLayerColor* colorBackground = CCLayerColor::create(ccc4(0, 0, 0, 128));
    this->addChild(colorBackground);
}
void SettingLayer::createMenu()
{

    int fontSize = 32;
    CCString* fontName = CCString::create("MarkerFelt-Thin");
    
    CCMenuItemLabel* resume = CCMenuItemLabel::create(CCLabelTTF::create("继续", fontName->getCString(), fontSize), this, menu_selector(SettingLayer::resume));
    
    CCMenuItemLabel* quit = CCMenuItemLabel::create(CCLabelTTF::create("退出", fontName->getCString(), fontSize), this, menu_selector(SettingLayer::quit));
    
    CCMenuItemLabel* soundOn = CCMenuItemLabel::create(CCLabelTTF::create("特效 开", fontName->getCString(), fontSize));
    CCMenuItemLabel* soundOff = CCMenuItemLabel::create(CCLabelTTF::create("特效 关", fontName->getCString(), fontSize));
    _sound = CCMenuItemToggle::createWithTarget(this, menu_selector(SettingLayer::sound), soundOff, soundOn, NULL);
    
    CCMenuItemLabel* musicOn = CCMenuItemLabel::create(CCLabelTTF::create("背景音乐 开", fontName->getCString(), fontSize));
    CCMenuItemLabel* musicOff = CCMenuItemLabel::create(CCLabelTTF::create("背景音乐 关", fontName->getCString(), fontSize));
    _music = CCMenuItemToggle::createWithTarget(this, menu_selector(SettingLayer::music), musicOff, musicOn, NULL);
    
    CCMenuItemLabel* reset = CCMenuItemLabel::create(CCLabelTTF::create("重新开始", fontName->getCString(), fontSize), this, menu_selector(SettingLayer::reset));
    
    CCMenu* menu = CCMenu::create(resume, quit, _sound, _music, reset, NULL);
    menu->alignItemsVerticallyWithPadding(10);
    this->addChild(menu);
}
void SettingLayer::quit()
{
    HelloWorld* gameScene = (HelloWorld*)this->getParent();
    gameScene->quitGame();
}
void SettingLayer::resume()
{
    HelloWorld* gameScene = (HelloWorld*)this->getParent();
    gameScene->resume();
}

void SettingLayer::sound()
{
    bool flag = UserData::sharedUserData()->getSoundVolume()>0;
    UserData::sharedUserData()->setSoundVolume(!flag);
    UserData::sharedUserData()->flush();
    PersonalAudioEngine::sharedEngine()->setEffectsVolume(!flag);

}
void SettingLayer::music()
{
    bool flag = UserData::sharedUserData()->getMusicVolume()>0;
    UserData::sharedUserData()->setMusicVolume(!flag);
    UserData::sharedUserData()->flush();
    PersonalAudioEngine::sharedEngine()->setBackgroundMusicVolume(!flag);

}
void SettingLayer::reset()
{
    HelloWorld* gameScene = (HelloWorld*)this->getParent();
    gameScene->restart();
}
void SettingLayer::setSoundAndMusicVolume(float soundVolume, float musicVolume)
{
    bool soundFlag = soundVolume>0;
    bool musicFlag = musicVolume>0;
    _sound->setSelectedIndex(soundFlag);
    _music->setSelectedIndex(musicFlag);
}