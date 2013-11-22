//
//  Robot.cpp
//  Rocky
//
//  Created by Tuyuer on 13-2-3.
//
//

#include "Robot.h"
#include "script_support/CCScriptSupport.h"
#include "CCLuaEngine.h"

#include "tolua++.h"
#include "LuaCocos2d.h"
extern "C" {
#include "lualib.h"
#include "lauxlib.h"
#include "tolua_fix.h"
}

USING_NS_CC;

Robot * Robot::createWithSpriteFrameName(const char *pszSpriteFrameName){
    CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pszSpriteFrameName);
    
#if COCOS2D_DEBUG > 0
    char msg[256] = {0};
    sprintf(msg, "Invalid spriteFrameName: %s", pszSpriteFrameName);
    CCAssert(pFrame != NULL, msg);
#endif
    
    return createWithSpriteFrame(pFrame);
}

Robot* Robot::createWithSpriteFrame(CCSpriteFrame *pSpriteFrame)
{
    Robot *pobSprite = new Robot();
    if (pSpriteFrame && pobSprite && pobSprite->initWithSpriteFrame(pSpriteFrame))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

void Robot::initActions(){
    CCArray * idleArray=CCArray::createWithCapacity(5);
    for (int i=0; i<5; i++) {
        CCString * strFrameName=CCString::createWithFormat("robot_idle_0%d.png",i);
        CCSpriteFrame * frameIdle=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(strFrameName->getCString());
        idleArray->addObject(frameIdle);
    }
    CCAnimation * animationIdle=CCAnimation::createWithSpriteFrames(idleArray);
    animationIdle->setDelayPerUnit(0.1);
    CCAnimate * animateIdle=CCAnimate::create(animationIdle);
    arrayActions->addObject(CCRepeatForever::create(animateIdle));
    
    CCArray * walkArray=CCArray::createWithCapacity(6);
    for (int i=0; i<6; i++) {
        CCString * strFrameName=CCString::createWithFormat("robot_walk_0%d.png",i);
        CCSpriteFrame * frameWalk=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(strFrameName->getCString());
        walkArray->addObject(frameWalk);
    }
    CCAnimation * animationWalk=CCAnimation::createWithSpriteFrames(walkArray);
    animationWalk->setDelayPerUnit(0.1);
    CCAnimate * animateWalk=CCAnimate::create(animationWalk);
    
    arrayActions->addObject(CCRepeatForever::create(animateWalk));
    
    CCArray * hitArray=CCArray::createWithCapacity(5);
    for (int i=0; i<5; i++) {
        CCString * strFrameName=CCString::createWithFormat("robot_attack_0%d.png",i);
        CCSpriteFrame * frameHit=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(strFrameName->getCString());
        hitArray->addObject(frameHit);
    }
    CCAnimation * animationHit=CCAnimation::createWithSpriteFrames(hitArray);
    animationHit->setDelayPerUnit(0.05);
    CCAnimate * animateHit=CCAnimate::create(animationHit);
    
    arrayActions->addObject(CCSequence::create(animateHit,CCCallFunc::create(this, callfunc_selector(Robot::idle)),NULL));

    CCArray * hurtArray=CCArray::createWithCapacity(3);
    for (int i=0; i<3; i++) {
        CCString * strFrameName=CCString::createWithFormat("robot_hurt_0%d.png",i);
        CCSpriteFrame * frameHurt=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(strFrameName->getCString());
        hurtArray->addObject(frameHurt);
    }
    CCAnimation * animationHurt=CCAnimation::createWithSpriteFrames(hurtArray);
    animationHurt->setDelayPerUnit(0.05);
    CCAnimate * animateHurt=CCAnimate::create(animationHurt);
    arrayActions->addObject(CCSequence::create(animateHurt,CCCallFunc::create(this, callfunc_selector(Robot::idle)),NULL));

    
    //knock out
    CCArray * knockOutArray=CCArray::createWithCapacity(5);
    for (int i=0; i<5; i++) {
        CCString * strFrameName=CCString::createWithFormat("robot_knockout_0%d.png",i);
        CCSpriteFrame * frameKnockOut=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(strFrameName->getCString());
        knockOutArray->addObject(frameKnockOut);
    }
    CCAnimation * animationKnockOut=CCAnimation::createWithSpriteFrames(knockOutArray);
    animationKnockOut->setDelayPerUnit(0.05);
    CCAnimate * animateKnockOut=CCAnimate::create(animationKnockOut);
    arrayActions->addObject(animateKnockOut);
}

void Robot::findTarget(cocos2d::CCPoint targetPos){
    
    CCLuaEngine* pEngine = CCLuaEngine::defaultEngine();
    
    pEngine->executeGlobalFunction("findTarget", this, &targetPos, "Role","CCPoint");

}

void Robot::initSelf(){
    this->centerToBottom=40;
    this->centerToSides=30;
    this->m_hitBox =this->createBoundingBoxWith(ccp(-this->centerToSides, -this->centerToBottom), CCSizeMake(this->centerToSides * 2, this->centerToBottom * 2));
    this->m_attackBox = this->createBoundingBoxWith(ccp(this->centerToSides, -15),CCSizeMake(30, 30));
    this->totalBlood=400;
    this->damage=50;
    this->live();
}









