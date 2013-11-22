//
//  AboutScene.h
//  Rocky
//
//  Created by Tuyuer on 13-2-24.
//
//

#ifndef __Rocky__AboutScene__
#define __Rocky__AboutScene__

#include <iostream>
#include "cocos2d.h"
class AboutScene:public cocos2d::CCLayer
{
private:
    void backToOption();
public:
    virtual void onEnterTransitionDidFinish();
    
    CREATE_FUNC(AboutScene);
    static cocos2d::CCScene * scene();
};
#endif /* defined(__Rocky__AboutScene__) */
