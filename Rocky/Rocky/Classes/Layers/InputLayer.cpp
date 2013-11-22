//
//  InputLayer.cpp
//  Rocky
//
//  Created by Tuyuer on 13-2-3.
//
//

#include "InputLayer.h"
#include "SneakyButton.h"
#include "SneakyButtonSkinnedBase.h"
#include "SneakyJoystick.h"
#include "SneakyJoystickSkinnedBase.h"
USING_NS_CC;
void InputLayer::initUI(){
    SneakyButtonSkinnedBase *buttonBase = new SneakyButtonSkinnedBase();
    
    buttonBase->autorelease();
    buttonBase->init();
    buttonBase->setDefaultSprite(CCSprite::create("Icon-72.png"));
    buttonBase->setActivatedSprite(CCSprite::create("Icon-72.png"));
    CCSprite * pressedSprite=CCSprite::create("Icon-72.png");
    pressedSprite->setColor(ccRED);
    buttonBase->setPressSprite(pressedSprite);
    
    buttonBase->setPosition(CCPointMake(480-48, 54));
    
    _sneakyButton= new SneakyButton();
    _sneakyButton->autorelease();
    _sneakyButton->initWithRect(CCRectZero);
    _sneakyButton->setIsToggleable(false);
    _sneakyButton->setIsHoldable(false);
    
    buttonBase->setButton(_sneakyButton);
    this->addChild(buttonBase);
    
    SneakyJoystickSkinnedBase *joystickBase = new SneakyJoystickSkinnedBase();
    joystickBase->autorelease();
    joystickBase->init();
    joystickBase->setBackgroundSprite(CCSprite::create("pd_dpad.png")); // 底座
    CCSprite * spriteHandle=CCSprite::create("pd_dpad.png");
    spriteHandle->setScale(0.5);
    spriteHandle->setRotation(45);
    joystickBase->setThumbSprite(spriteHandle); // 操控杆
    joystickBase->setPosition(CCPointMake(80, 70));
    
    _sneakyStick= new SneakyJoystick();
    
    _sneakyStick->autorelease();
    _sneakyStick->initWithRect(CCRectZero);
    
    joystickBase->setJoystick(_sneakyStick);
    this->addChild(joystickBase);
}

void InputLayer::onEnter(){
    CCLayer::onEnter();
}

void InputLayer::onExit(){
    CCLayer::onExit();
    this->unscheduleUpdate();
}

void InputLayer::onEnterTransitionDidFinish(){
    CCLayer::onEnterTransitionDidFinish();
    this->initUI();
    this->scheduleUpdate();
}

void InputLayer::update(float fDelta){
    CCPoint moveVelocity=_sneakyStick->getVelocity();
    if (_pDelegate) {
        _pDelegate->updatingPosition(moveVelocity);
    }
    
    if (_sneakyButton->getIsActive()) {
        if (_pDelegate) {
            _sneakyButton->setIsActive(false);
            _pDelegate->actionHit();
        }
    }
}

void InputLayer::disableButtons(){
    this->removeAllChildren();
}

void InputLayer::setDelegate(InputLayerDelegate * pDelegate){
    _pDelegate=pDelegate;
}



