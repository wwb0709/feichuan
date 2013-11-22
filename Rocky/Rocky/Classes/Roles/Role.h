//
//  Role.h
//  Rocky
//
//  Created by Tuyuer on 13-2-3.
//
//

#ifndef __Rocky__Role__
#define __Rocky__Role__

#include <iostream>
#include "cocos2d.h"
#include "AppMacros.h"

typedef enum {
    kRoleStateNone=0,
    kRoleStateIdle,
    kRoleStateWalk,
    kRoleStateAttack,
    kRoleStateHurt,
    kRoleStateKnockedOut
}RoleState;

typedef enum {
    kRoleDirectionRight,
    kRoleDirectionLeft,
}RoleDirection;

class Role:public cocos2d::CCSprite{
private:
    bool isAlive;           //是否存活
protected:
    cocos2d::CCArray * arrayActions;
    RoleState roleState;
    RoleDirection roleDirection;
    
    int totalBlood;         //总血
    int currentBlood;       //当前血
    int damage;             //攻击力量，每次攻击打下多少血
    
public:
    ColliderBox m_hitBox;
    ColliderBox m_attackBox;
    float centerToSides;
    float centerToBottom;
public:
    Role();
    ~Role();
    virtual RoleState getState(){ return roleState; }
    virtual void setState(RoleState rState){ roleState=rState; }
    virtual void initActions(){}
    virtual void initSelf(){}
    virtual void onEnterTransitionDidFinish();
    virtual void setPosition(const cocos2d::CCPoint& pos);
    virtual void setPosition(const cocos2d::CCPoint& pos,const cocos2d::CCSize & boundingSize);

    ColliderBox createBoundingBoxWith(cocos2d::CCPoint posOrigin,cocos2d::CCSize szSize);
    void transformBoxes();
    
    void setDirection(RoleDirection rDirection);
    RoleDirection getDirection(){return roleDirection;};
    int getDamage(){ return damage;};
    void move();
    
    void idle();
    void hit();
    void hurt(int damage);
    void live();    //复活
    void die();
};

#endif /* defined(__Rocky__Role__) */
