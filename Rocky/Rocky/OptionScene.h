//
//  OptionScene.h
//  Rocky
//
//  Created by Tuyuer on 13-2-24.
//
//

#ifndef __Rocky__OptionScene__
#define __Rocky__OptionScene__

#include <iostream>
#include "cocos2d.h"

class OptionScene:public cocos2d::CCLayer
{
private:
    void startGame();
    void toAbout();
public:
    virtual void onEnterTransitionDidFinish();
    
    CREATE_FUNC(OptionScene);
    static cocos2d::CCScene * scene();
};
#endif /* defined(__Rocky__OptionScene__) */
