//
//  Player.h
//  Rocky
//
//  Created by Tuyuer on 13-2-3.
//
//

#ifndef __Rocky__Player__
#define __Rocky__Player__

#include <iostream>
#include "cocos2d.h"
#include "Role.h"

class Player:public Role
{
private:
    virtual void initActions();
    virtual void initSelf();
public:
    static Player * createWithSpriteFrameName(const char *pszSpriteFrameName);
    static Player * createWithSpriteFrame(cocos2d::CCSpriteFrame *pSpriteFrame);
};


#endif /* defined(__Rocky__Player__) */
