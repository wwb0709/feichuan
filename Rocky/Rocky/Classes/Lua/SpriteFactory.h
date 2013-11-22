//
//  SpriteFactory.h
//  Rocky
//
//  Created by Tuyuer on 13-2-5.
//
//

#ifndef __Rocky__SpriteFactory__
#define __Rocky__SpriteFactory__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

class SpriteFactory
{
public:
    enum SpriteType
    {
        en_close,
        en_grossini,
        en_grossinis_sister,
        en_grossinis_sister2,
    };
    
    static SpriteFactory* sharedSpriteFactory();
    
    CCSprite* createSprite(CCLayer* mLayer, SpriteType enSpriteType);
private:
    static SpriteFactory* mFactory;
};

#endif /* defined(__Rocky__SpriteFactory__) */
