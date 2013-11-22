//
//  GameScene.h
//  Rocky
//
//  Created by Tuyuer on 13-2-3.
//
//

#ifndef __Rocky__GameScene__
#define __Rocky__GameScene__

#include <iostream>
#include "cocos2d.h"

class GameScene:public cocos2d::CCLayer{
private:
    void initUI();
public:
    virtual void onEnter();
    virtual void onEnterTransitionDidFinish();
    
    CREATE_FUNC(GameScene);
    static cocos2d::CCScene * scene();
};

#endif /* defined(__Rocky__GameScene__) */
