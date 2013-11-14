//
//  PersonalAudioEngine.cpp
//  testcocos2d-x
//
//  Created by wangwb on 13-11-7.
//
//

#include "PersonalAudioEngine.h"
#include "UserData.h"
#include "StaticData.h"

void PersonalAudioEngine::setBackgroundMusicVolume(float volume)
{
    SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(volume);
    UserData::sharedUserData()->setMusicVolume(volume);

}
void PersonalAudioEngine::setEffectsVolume(float volume)
{
    SimpleAudioEngine::sharedEngine()->setEffectsVolume(volume);
    UserData::sharedUserData()->setSoundVolume(volume);
}
static PersonalAudioEngine* _personalAudioEngine = NULL;

PersonalAudioEngine* PersonalAudioEngine::sharedEngine()
{
    
    if (_personalAudioEngine == NULL) {
        _personalAudioEngine = new PersonalAudioEngine();
        _personalAudioEngine->init();
    }
    return _personalAudioEngine;
    
}

void PersonalAudioEngine::purge()
{

    
}
bool PersonalAudioEngine::init()
{
    this->preloadBackgroundMusic(STATIC_DATA_STRING("bg_music"));
    this->preloadEffect(STATIC_DATA_STRING("sound_bullet"));
    this->preloadEffect(STATIC_DATA_STRING("game_over"));
    
    this->setBackgroundMusicVolume(UserData::sharedUserData()->getMusicVolume());
    this->setEffectsVolume(UserData::sharedUserData()->getSoundVolume());
    return true;
}

PersonalAudioEngine::PersonalAudioEngine()
{

}
PersonalAudioEngine::~PersonalAudioEngine()
{

}
