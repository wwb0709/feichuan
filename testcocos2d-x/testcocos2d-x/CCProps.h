//
//  CCProps.h
//  testcocos2d-x
//
//  Created by wangwb on 13-11-1.
//
//

#ifndef __testcocos2d_x__CCProps__
#define __testcocos2d_x__CCProps__
#include "commonheader.h"
typedef enum{
    propsTypeBomb = 4,
    propsTypeBullet = 5
}propsType;

class CCProps : public CCNode
{
    public:
        CCProps();
        ~CCProps();
        static CCProps* create();
        void initWithType(propsType type);
        void propAnimation();
        CC_SYNTHESIZE_RETAIN(CCSprite*, _prop, Prop);
    public:
        propsType type;
};

#endif /* defined(__testcocos2d_x__CCProps__) */
