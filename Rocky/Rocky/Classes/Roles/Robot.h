//
//  Robot.h
//  Rocky
//
//  Created by Tuyuer on 13-2-3.
//
//

#ifndef __Rocky__Robot__
#define __Rocky__Robot__

#include <iostream>
#include "cocos2d.h"
#include "Role.h"

class Robot:public Role
{
private:
    virtual void initActions();
    virtual void initSelf();
public:
    static Robot * createWithSpriteFrameName(const char *pszSpriteFrameName);
    static Robot * createWithSpriteFrame(cocos2d::CCSpriteFrame *pSpriteFrame);
    void findTarget(cocos2d::CCPoint targetPos);
};
#endif /* defined(__Rocky__Robot__) */
