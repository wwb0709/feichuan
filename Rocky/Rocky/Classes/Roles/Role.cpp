//
//  Role.cpp
//  Rocky
//
//  Created by Tuyuer on 13-2-3.
//
//

#include "Role.h"
USING_NS_CC;

Role::Role(){
    arrayActions=CCArray::createWithCapacity(5);
    arrayActions->retain();
}

Role::~Role(){
    CC_SAFE_RELEASE(arrayActions);
}

void Role::move(){
    this->stopAllActions();
    this->runAction((CCAction*)arrayActions->objectAtIndex(1));
    this->setState(kRoleStateWalk);
}

void Role::idle(){
    this->stopAllActions();
    CCAction * actionIdle=(CCAction *)arrayActions->objectAtIndex(0);
    this->runAction(actionIdle);
    this->setState(kRoleStateIdle);
}

void Role::live(){
    currentBlood=totalBlood;
    this->isAlive=true;
    this->idle();
}

void Role::die(){
    this->stopAllActions();
    CCAction * actionDie=(CCAction *)arrayActions->objectAtIndex(4);
    this->runAction(actionDie);
    this->setState(kRoleStateKnockedOut);
}

void Role::onEnterTransitionDidFinish(){
    this->initActions();
    this->initSelf();
    this->idle();
}

void Role::setDirection(RoleDirection rDirection){
    roleDirection=rDirection;
    switch (roleDirection) {
        case kRoleDirectionLeft:
            this->setScaleX(-1);
            break;
        case kRoleDirectionRight:
            this->setScaleX(1);
            break;
        default:
            break;
    }
}


void Role::hit(){
    this->stopAllActions();
    CCAction * actionHit=(CCAction *)arrayActions->objectAtIndex(2);
    this->runAction(actionHit);
    this->setState(kRoleStateAttack);
}

void Role::hurt(int damage){
    this->stopAllActions();
    CCAction * actionHurt=(CCAction *)arrayActions->objectAtIndex(3);
    this->runAction(actionHurt);
    this->setState(kRoleStateHurt);
    this->currentBlood-=damage;
    if (this->currentBlood<=0) {
        this->die();
    }
}

void Role::setPosition(const cocos2d::CCPoint& pos,const cocos2d::CCSize & boundingSize){
    float yPos=pos.y;
    float xPos=pos.x;
    if (pos.y+centerToBottom>=boundingSize.height) {
        yPos=boundingSize.height-centerToBottom;
    }
    if (pos.y-centerToBottom<=0) {
        yPos=centerToBottom;
    }
    if (pos.x-centerToSides<=0) {
        xPos=centerToSides;
    }
    if (pos.x+centerToSides>=boundingSize.width) {
        xPos=boundingSize.width-centerToSides;
    }
    CCPoint targetPos=ccp(xPos,yPos);
    this->setPosition(targetPos);
}

ColliderBox Role::createBoundingBoxWith(cocos2d::CCPoint posOrigin,cocos2d::CCSize szSize){
    ColliderBox boundingBox;
    boundingBox.original.origin = posOrigin;
    boundingBox.original.size = szSize;
    boundingBox.actual.origin = ccpAdd(this->getPosition(), ccp(boundingBox.original.origin.x, boundingBox.original.origin.y));
    boundingBox.actual.size = szSize;
    return boundingBox;
}

void Role::transformBoxes() {
    m_hitBox.actual.origin = ccpAdd(this->getPosition(), ccp(m_hitBox.original.origin.x, m_hitBox.original.origin.y ));
    m_hitBox.actual.size = CCSizeMake(m_hitBox.original.size.width , m_hitBox.original.size.height );
    if (this->getScaleX()<0) {
        m_attackBox.actual.origin = ccpAdd(this->getPosition(), ccp(m_attackBox.original.origin.x* this->getScaleX()-centerToSides+6 , m_attackBox.original.origin.y ));
        
    }else{
        m_attackBox.actual.origin = ccpAdd(this->getPosition(), ccp(m_attackBox.original.origin.x , m_attackBox.original.origin.y ));
    }
   m_attackBox.actual.size = CCSizeMake(m_attackBox.original.size.width , m_attackBox.original.size.height);
}

void Role::setPosition(const cocos2d::CCPoint& pos){
    CCSprite::setPosition(pos);
    this->transformBoxes();
}









