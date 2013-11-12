//
//  UserData.cpp
//  testcocos2d-x
//
//  Created by wangwb on 13-11-7.
//
//

#include "UserData.h"

static UserData* _sharedUserData = NULL;
UserData::UserData()
{


}
UserData::~UserData()
{
    this->flush();
}
bool UserData::init()
{
    _score = CCUserDefault::sharedUserDefault()->getIntegerForKey("score",0);
    _name = CCUserDefault::sharedUserDefault()->getStringForKey("name","wwb");
    
    _musicVolume =CCUserDefault::sharedUserDefault()->getFloatForKey("musicvolume",1);
    _soundVolume =CCUserDefault::sharedUserDefault()->getFloatForKey("soundvolume",1);

    return true;
}
UserData* UserData::sharedUserData()
{
    if (_sharedUserData == NULL) {
        _sharedUserData = new UserData;
        _sharedUserData->init();
    }
    
    return _sharedUserData;
}

void UserData::flush()
{
    CCUserDefault::sharedUserDefault()->setIntegerForKey("score", this->getScore());
    CCUserDefault::sharedUserDefault()->setStringForKey("name", this->getName());
    CCUserDefault::sharedUserDefault()->flush();
    CCUserDefault::sharedUserDefault()->purgeSharedUserDefault();
}

void UserData::purge()
{
    CC_SAFE_RELEASE_NULL(_sharedUserData);
}

void UserData::alertScore(int delta)
{

    this->setScore(delta);
    this->flush();

}



