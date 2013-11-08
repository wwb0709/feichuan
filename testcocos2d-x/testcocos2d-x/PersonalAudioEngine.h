//
//  PersonalAudioEngine.h
//  testcocos2d-x
//
//  Created by wangwb on 13-11-7.
//
//

#ifndef __testcocos2d_x__PersonalAudioEngine__
#define __testcocos2d_x__PersonalAudioEngine__
#include "SimpleAudioEngine.h"
#include "commonheader.h"

class PersonalAudioEngine: public CocosDenshion::SimpleAudioEngine
{
    
public:
    void setBackgroundMusicVolume(float volume);
    void setEffectsVolume(float volume);
    
    static PersonalAudioEngine* sharedEngine();
    
    void purge();
    bool init();
protected:
    PersonalAudioEngine();
    ~PersonalAudioEngine();

};

#endif /* defined(__testcocos2d_x__PersonalAudioEngine__) */
