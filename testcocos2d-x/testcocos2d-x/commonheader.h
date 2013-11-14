//
//  commonheader.h
//  testcocos2d-x
//
//  Created by wangwb on 13-10-31.
//
//

#ifndef testcocos2d_x_commonheader_h
#define testcocos2d_x_commonheader_h
#include "cocos2d.h"
#include "cocos-ext.h"
#include "StaticData.h"
#include "UserData.h"

#define WINDOWHEIGHT CCDirector::sharedDirector()->getWinSize().height
#define WINDOWWIDTH CCDirector::sharedDirector()->getWinSize().width


using namespace cocos2d;
using namespace cocos2d::extension;

typedef enum{
    k_Operate_Pause = 0,
    k_Operate_Resume
}OperateFlag;

#endif
