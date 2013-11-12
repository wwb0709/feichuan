//
//  CCProps.cpp
//  testcocos2d-x
//
//  Created by wangwb on 13-11-1.
//
//


#include "CCProps.h"


CCProps::CCProps():_prop(NULL)
{
    CCLog("CCProps::CCProps");
}

CCProps::~CCProps()
{
    CC_SAFE_RELEASE_NULL(_prop);
}


CCProps * CCProps::create(void)
{
	CCProps * pRet = new CCProps();
    if (pRet)
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
	return pRet;
}

void CCProps::initWithType(propsType type)
{
    this->type = type;
    CCString *propKey = CCString::createWithFormat("enemy%d_fly_1.png",type);
    this->setProp(CCSprite::createWithSpriteFrameName(propKey->getCString()));
    this->getProp()->setPosition(ccp((arc4random()%268)+23, 732));
    
}

void CCProps::propAnimation()
{
    CCMoveTo* act1 = CCMoveTo::create(1, ccp(_prop->getPosition().x, 400));
    CCMoveTo* act2 = CCMoveTo::create(0.2, ccp(_prop->getPosition().x, 402));
    CCMoveTo* act3 = CCMoveTo::create(1, ccp(_prop->getPosition().x, 732));
    CCMoveTo* act4 = CCMoveTo::create(1, ccp(_prop->getPosition().x, -55));
    _prop->runAction(CCSequence::create(act1, act2, act3, act4,NULL));
}
