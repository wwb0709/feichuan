//
//  Player.cpp
//  Rocky
//
//  Created by Tuyuer on 13-2-3.
//
//

#include "Player.h"
USING_NS_CC;

Player * Player::createWithSpriteFrameName(const char *pszSpriteFrameName){
    CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pszSpriteFrameName);
    
#if COCOS2D_DEBUG > 0
    char msg[256] = {0};
    sprintf(msg, "Invalid spriteFrameName: %s", pszSpriteFrameName);
    CCAssert(pFrame != NULL, msg);
#endif
    
    return createWithSpriteFrame(pFrame);
}

Player* Player::createWithSpriteFrame(CCSpriteFrame *pSpriteFrame)
{
    Player *pobSprite = new Player();
    if (pSpriteFrame && pobSprite && pobSprite->initWithSpriteFrame(pSpriteFrame))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

void Player::initActions(){
    //idle
    CCArray * idleArray=CCArray::createWithCapacity(6);
    for (int i=0; i<6; i++) {
        CCString * strFrameName=CCString::createWithFormat("hero_idle_0%d.png",i);
        CCSpriteFrame * frameIdle=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(strFrameName->getCString());
        idleArray->addObject(frameIdle);
    }
    CCAnimation * animationIdle=CCAnimation::createWithSpriteFrames(idleArray);
    animationIdle->setDelayPerUnit(0.1);
    CCAnimate * animateIdle=CCAnimate::create(animationIdle);
    arrayActions->addObject(CCRepeatForever::create(animateIdle));
    
    //walk
    CCArray * walkArray=CCArray::createWithCapacity(8);
    for (int i=0; i<8; i++) {
        CCString * strFrameName=CCString::createWithFormat("hero_walk_0%d.png",i);
        CCSpriteFrame * frameWalk=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(strFrameName->getCString());
        walkArray->addObject(frameWalk);
    }
    CCAnimation * animationWalk=CCAnimation::createWithSpriteFrames(walkArray);
    animationWalk->setDelayPerUnit(0.1);
    CCAnimate * animateWalk=CCAnimate::create(animationWalk);
    arrayActions->addObject(CCRepeatForever::create(animateWalk));
    
    //attack
    CCArray * hitArray=CCArray::createWithCapacity(3);
    for (int i=0; i<3; i++) {
        CCString * strFrameName=CCString::createWithFormat("hero_attack_00_0%d.png",i);
        CCSpriteFrame * frameHit=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(strFrameName->getCString());
        hitArray->addObject(frameHit);
    }
    CCAnimation * animationHit=CCAnimation::createWithSpriteFrames(hitArray);
    animationHit->setDelayPerUnit(0.05);
    CCAnimate * animateHit=CCAnimate::create(animationHit);
    arrayActions->addObject(CCSequence::create(animateHit,CCCallFunc::create(this, callfunc_selector(Player::idle)),NULL));
 
    //hurt
    CCArray * hurtArray=CCArray::createWithCapacity(3);
    for (int i=0; i<3; i++) {
        CCString * strFrameName=CCString::createWithFormat("hero_hurt_0%d.png",i);
        CCSpriteFrame * frameHurt=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(strFrameName->getCString());
        hurtArray->addObject(frameHurt);
    }
    CCAnimation * animationHurt=CCAnimation::createWithSpriteFrames(hurtArray);
    animationHurt->setDelayPerUnit(0.05);
    CCAnimate * animateHurt=CCAnimate::create(animationHurt);
    arrayActions->addObject(CCSequence::create(animateHurt,CCCallFunc::create(this, callfunc_selector(Player::idle)),NULL));

    
    //knock out
    CCArray * knockOutArray=CCArray::createWithCapacity(5);
    for (int i=0; i<5; i++) {
        CCString * strFrameName=CCString::createWithFormat("hero_knockout_0%d.png",i);
        CCSpriteFrame * frameKnockOut=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(strFrameName->getCString());
        knockOutArray->addObject(frameKnockOut);
    }
    CCAnimation * animationKnockOut=CCAnimation::createWithSpriteFrames(knockOutArray);
    animationKnockOut->setDelayPerUnit(0.05);
    CCAnimate * animateKnockOut=CCAnimate::create(animationKnockOut);
    arrayActions->addObject(animateKnockOut);
}

void Player::initSelf(){
    this->centerToBottom=40;
    this->centerToSides=29;
    this->m_hitBox =this->createBoundingBoxWith(ccp(-this->centerToSides, -this->centerToBottom), CCSizeMake(this->centerToSides * 2, this->centerToBottom * 2));
    this->m_attackBox = this->createBoundingBoxWith(ccp(this->centerToSides, -10),CCSizeMake(20, 20));
    this->totalBlood=600;
    this->damage=100;
    this->live();
}



