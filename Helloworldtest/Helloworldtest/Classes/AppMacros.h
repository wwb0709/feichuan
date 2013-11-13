#ifndef __APPMACROS_H__
#define __APPMACROS_H__

#include "cocos2d.h"


typedef struct tagResource
{
    cocos2d::CCSize size;
    char directory[100];
}Resource;

//���õ���Դ�ߴ�
static Resource smallResource  =  { cocos2d::CCSizeMake(960, 640),   "r.bundle/iphone" };
static Resource mediumResource =  { cocos2d::CCSizeMake(1024, 768),  "r.bundle/ipad"   };
static Resource largeResource  =  { cocos2d::CCSizeMake(2048, 1536), "r.bundle/ipadhd" };

//��Ʒֱ���
static cocos2d::CCSize smallDesignResolutionSize = cocos2d::CCSizeMake(960.0f, 640.0f);
static cocos2d::CCSize mediumDesignResolutionSize = cocos2d::CCSizeMake(1024.0f, 768.0f);
static cocos2d::CCSize largeDesignResolutionSize = cocos2d::CCSizeMake(2048.0f, 1536.0f);

//�������ӣ���Ҫ������ʹ��
#define SCALE_FACTOR  (cocos2d::CCEGLView::sharedOpenGLView()->getDesignResolutionSize().width / smallResource.size.width)

#endif 
