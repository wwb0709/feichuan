//
//  InputLayer.h
//  Rocky
//
//  Created by Tuyuer on 13-2-3.
//
//

#ifndef __Rocky__InputLayer__
#define __Rocky__InputLayer__

#include <iostream>
#include "cocos2d.h"

class InputLayerDelegate {
public:
    virtual void updatingPosition(cocos2d::CCPoint velocity){};
    virtual void actionHit(){};
};

class SneakyButton;
class SneakyJoystick;
class InputLayer:public cocos2d::CCLayer{
private:
    SneakyButton * _sneakyButton;
    SneakyJoystick * _sneakyStick;
    InputLayerDelegate * _pDelegate;
private:
    void initUI();
public:
    virtual void onEnter();
    virtual void onExit();
    virtual void onEnterTransitionDidFinish();
    virtual void update(float fDelta);
    
    void disableButtons();
    void setDelegate(InputLayerDelegate * pDelegate);
    
    CREATE_FUNC(InputLayer);
};

#endif /* defined(__Rocky__InputLayer__) */
