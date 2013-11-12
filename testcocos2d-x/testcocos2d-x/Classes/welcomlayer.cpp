//
//  welcomlayer.cpp
//  testcocos2d-x
//
//  Created by wangwb on 13-10-30.
//
//

#include "welcomlayer.h"
#include "HelloWorldScene.h"
#include "PersonalAudioEngine.h"
#include "UserData.h"

CCScene* welcomlayer::scene()
{
    CCScene *scene = CCScene::create();
    welcomlayer *layer = welcomlayer::create();
    scene->addChild(layer);
    return scene;
}

welcomlayer::welcomlayer()
{
}

welcomlayer::~welcomlayer()
{
}

void welcomlayer::update(float delta){
    this->backgrouneScroll();
}

// 载入背景
void welcomlayer::loadBackground()
{
    this->BG1 = CCSprite::createWithSpriteFrameName("background_2.png");
    this->BG1->setAnchorPoint(ccp(0.5, 0));
    this->BG1->setPosition(ccp(160, adjustmentBG));
    this->addChild(BG1,0);
    
    this->BG2 = CCSprite::createWithSpriteFrameName("background_2.png");
    this->BG2->setAnchorPoint(ccp(0.5, 0));
    this->BG2->setPosition(ccp(160, 568+adjustmentBG));
    this->addChild(BG2,0);
    
    
}

// 背景滚动
void welcomlayer::backgrouneScroll()
{
    adjustmentBG--;
    
    if (adjustmentBG<=0) {
        adjustmentBG = 568;
    }
    BG1->setPosition(ccp(160, adjustmentBG));
    BG2->setPosition(ccp(160, adjustmentBG-568));
    
    
}

bool welcomlayer::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
//    CCTexture2D *texture = CCTextureCache::sharedTextureCache()->textureForKey("gameArts.png");
//    CCSpriteBatchNode *spriteBatch = CCSpriteBatchNode::createWithTexture(texture);
//    this->addChild(spriteBatch);
//
    
    //加载默认页面
    
    
    CCSize winsize = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite * loading = CCSprite::create("Default.png");
    loading->setPosition(CCPoint(winsize.width/2, winsize.height/2));
//    loading->setAnchorPoint(CCPoint(0.5,0.5));
    
    this->addChild(loading);
    
    CCLabelTTF *scoreLabel = CCLabelTTF::create("loading...", "MarkerFelt-Thin", 18.0, CCSizeMake(200, 0), kCCTextAlignmentLeft);
    scoreLabel->setColor(ccc3(65, 121, 183));
    scoreLabel->setAnchorPoint(ccp(0,1));
    scoreLabel->setScale(1.5);
    scoreLabel->setPosition(CCPoint(winsize.width/2,100));
    
    //this->scoreLabel->setString(CCString::createWithFormat("%u",score)->getCString());
    this->addChild(scoreLabel,4);
//    
//    //初始化数据
//    UserData::sharedUserData();
//    PersonalAudioEngine::sharedEngine();
    return true;
    
    //画上文字 CCLabelTTF::create("Hello World", "Thonburi", 34);
//    CCLabelTTF * lable = CCLabelTTF::create("Hello World", "Thonburi",34);
   //文字的换行
    CCLabelTTF *lable = CCLabelTTF::create("但是把那些字符中间的空格全部去掉他就不换行了 haThisisalonhg22222222longlongdsfdsfsfsflong long long long long long string", "Thonburi", 20, CCSizeMake(200, 0), kCCTextAlignmentLeft);
    lable->setPosition(CCPoint(winsize.width/2, 100));
    lable->setColor(ccc3(65, 121, 183));
    
    CCRenderTexture *stroke=this->createStroke(lable,2, ccRED);
    
    this->addChild(stroke);
    
    this->addChild(lable, 1);
    CCAction* scale=CCScaleTo::create(0.5, 0.2);
    lable->runAction(scale);
    
    
    CCPoint pointL=lable->getPosition();
    CCPoint pointR=lable->getPosition();
    pointL.x-=3;
    pointR.x+=3;
    CCMoveTo* moveLeft=CCMoveTo::create(0.08, pointL);
    CCMoveTo* moveRight=CCMoveTo::create(0.08, pointR);
    CCFiniteTimeAction* action= CCSequence::create(moveLeft,moveRight,NULL);
    CCActionInterval* actionShake=CCRepeatForever::create((CCActionInterval*)action);
    lable->stopAllActions();
//    lable->runAction(actionShake);
    
    
    //加入输入框
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCScale9Sprite * sacel9SprY=CCScale9Sprite::create("boxbg.png");
    CCEditBox * box = CCEditBox::create(CCSizeMake(300,60), sacel9SprY);

    //    获取编辑框内的文字
    CCLOG("Text:%s",box->getText());
    box->setFontColor(ccc3(255, 0, 0));
    //    当编辑框中没有任何字符的提示
    box->setPlaceHolder("zhanghao");
    CCLOG("PlaceHolder:%s",box->getPlaceHolder());
    //    最大输入文本长度
    box->setMaxLength(5);
    CCLOG("Length:%i", box->getMaxLength());
    //设置输入模式
    box->setInputFlag(kEditBoxInputFlagSensitive);
    //    设置return类型
    box->setReturnType(kKeyboardReturnTypeDone);
    box->setPosition(ccp(size.width*0.5, 220));
    box->setDelegate(this);
    box->setTag(113);
    addChild(box);
    
    CCScale9Sprite  * scale9SprG =CCScale9Sprite::create("boxbg.png");
    CCEditBox * box1 = CCEditBox ::create(CCSizeMake(300, 60), scale9SprG);
    box1->setPosition(ccp(size.width* 0.5, 120));
    box1->setFontColor(ccc3(255, 0, 0));
    box1->setPlaceHolder("输入密码");
    box1->setMaxLength(12);
    box1->setInputFlag(kEditBoxInputFlagSensitive);
    box1->setReturnType(kKeyboardReturnTypeGo);
    box1->setDelegate(this);
    box1->setTag(112);
    addChild(box1);
    box1->runAction(actionShake);

    
    
//    //         为编辑框设置背景
//    CCScale9Sprite * sacel9SprG = CCScale9Sprite::create("boxbg.png");
//    //    设置编辑框  将精灵 背景作为对象放到 编辑框里
//    //    同时设置 背景大小
//    CCEditBox* box2 = CCEditBox::create(CCSizeMake(300, 60), sacel9SprG);
//    //    设置显示字符串
//    box2->setPlaceHolder("Delegate");
//    //    设置编辑框的位置
//    box2->setPosition(ccp(200,50));
//    //    添加
//    addChild(box2);
//    //接口绑定

    
                            
//    this->loadBackground();
//    this->scheduleUpdate();
    
    return true;
}


CCRenderTexture* welcomlayer::createStroke(CCLabelTTF*lable,float size,ccColor3B cor)

{
    
    CCRenderTexture*rt=CCRenderTexture::create(lable->getTexture()->getContentSize().width, lable->getTexture()->getContentSize().height+size*2);
    
    
    
    CCPoint originalPos = lable->getPosition();
    
    ccColor3B originalColor = lable->getColor();
    
    bool originalVisibility =lable->isVisible();
    
    lable->setColor(cor);
    
    lable->setVisible(true);
    
    ccBlendFunc originalBlend = lable->getBlendFunc();
    
    ccBlendFunc blendFunc1 = { GL_SRC_ALPHA, GL_ONE };
    
    lable->setBlendFunc(blendFunc1);
    
    float aa=lable->getTexture()->getContentSize().width*lable->getAnchorPoint().x+size;
    
    float bb=lable->getTexture()->getContentSize().height*lable->getAnchorPoint().y+size;
    
    CCPoint bottomLeft=ccp(aa, bb);
    
    float aaa=lable->getTexture()->getContentSize().width*lable->getAnchorPoint().x- lable->getTexture()->getContentSize().width/2;
    
    float bbb=lable->getTexture()->getContentSize().height*lable->getAnchorPoint().y- lable->getTexture()->getContentSize().height/2;
    
    CCPoint positionOffset=ccp(aaa,bbb);
    
    CCPoint position=ccpSub(originalPos, positionOffset);
    
    
    rt->begin();
    
    for (int i=0; i<360; i+=30) // you should optimize that for your needs
        
    {
        
        lable->setPosition(ccp(bottomLeft.x+sin(CC_DEGREES_TO_RADIANS(i)*size), bottomLeft.y+cos(CC_DEGREES_TO_RADIANS(i)*size)));
        
        lable->visit();
        
    }
    
    rt->end();
    
    lable->setPosition(originalPos);
    
    lable->setColor(originalColor);
    
    lable->setBlendFunc(originalBlend);
    
    lable->setVisible(originalVisibility);
    
    rt->setPosition(position);
    
    return  rt;
    
    
}
//    开始进入编辑
void welcomlayer::editBoxEditingDidBegin(cocos2d::extension::CCEditBox*editBox)
{
    CCLOG("editBoxEditingDidBegin");
}
//结束编辑
void welcomlayer::editBoxEditingDidEnd(cocos2d::extension::CCEditBox* editBox)
{
    CCLOG("editBoxEditingDidEnd");
}
//编辑框文本改变
void welcomlayer::editBoxTextChanged(cocos2d::extension::CCEditBox* editBox, const std::string& text)
{
    CCLOG("editBoxTextChanged");
}
//当触发return后的回调函数
void welcomlayer::editBoxReturn(cocos2d::extension::CCEditBox* editBox)
{
    
    CCLOG("editBoxReturn--------content:%s tag:%d",editBox->getText(),editBox->getTag());
}
void welcomlayer::onEnter()
{
//    CCScene *pScene = HelloWorld::scene();
//    CCTransitionFade* transitionScene = CCTransitionFade::create(1.0, pScene,ccWHITE);
//    CCDirector::sharedDirector()->replaceScene(transitionScene);
    
    beginGame();
}

void welcomlayer::beginGame()
{
    CCLog("beginGame");
    
    //CCTransitionScene *trans = CCTransitionScene::create(2, level);
    //CCDirector::sharedDirector()->replaceScene(level);
    //场景切换
    CCTransitionScene *reScene = NULL;
    CCScene *s = HelloWorld::scene();
    
    float t = 1.2f;
    
    //  CCTransitionJumpZoom
    //    作用： 创建一个跳动的过渡动画
    //    参数1：过渡动作的时间
    //    参数2：切换到目标场景的对象
//        reScene = CCTransitionJumpZoom ::create(t , s);
    //    CCDirector::sharedDirector()->replaceScene(reScene);
    
    //    CCTransitionProgressRadialCCW
    //    作用： 创建一个扇形条形式的过渡动画， 逆时针方向
    //    参数1：过渡动作的时间
    //    参数2：切换到目标场景的对象
    //    reScene = CCTransitionProgressRadialCCW::create(t, s);
    //    CCDirector::sharedDirector()->replaceScene(reScene);
    
    //    CCTransitionProgressRadialCW
    //    作用： 创建一个扇形条形式的过渡动画， 顺时针方向
    //    参数1：过渡动作的时间
    //    参数2：切换到目标场景的对象
    //    reScene = CCTransitionProgressRadialCW::create(t,s);
    //    CCDirector::sharedDirector()->replaceScene(reScene);
    
    //    CCTransitionProgressHorizontal
    //    作用： 创建一个水平条形式的过渡动画，
    //    参数1：过渡动作的时间
    //    参数2：切换到目标场景的对象
    //    reScene = CCTransitionProgressHorizontal ::create(t,s);
    //    CCDirector::sharedDirector()->replaceScene(reScene);
    
    //    CCTransitionProgressVertical
    //    作用： 创建一个垂直条形式的过渡动画，
    //    参数1：过渡动作的时间
    //    参数2：切换到目标场景的对象
    //    reScene = CCTransitionProgressVertical::create(t, s);
    //    CCDirector::sharedDirector()->replaceScene(reScene);
    
    
    //    CCTransitionProgressInOut
    //    作用： 创建一个由里向外扩展的过渡动画，
    //    参数1：过渡动作的时间
    //    参数2：切换到目标场景的对象
    //    reScene = CCTransitionProgressInOut::create(t, s);
    //    CCDirector::sharedDirector()->replaceScene(reScene);
    
    //    CCTransitionProgressOutIn
    //    作用： 创建一个由外向里扩展的过渡动画，
    //    参数1：过渡动作的时间
    //    参数2：切换到目标场景的对象
    //    reScene = CCTransitionProgressOutIn::create(t, s);
    //    CCDirector::sharedDirector()->replaceScene(reScene);
    
    //    CCTransitionCrossFade
    //    作用：创建一个逐渐透明的过渡动画
    //    参数1：过渡动作的时间
    //    参数2：切换到目标场景的对象
    //    reScene = CCTransitionCrossFade::create(t, s);
    //    CCDirector::sharedDirector()->replaceScene(reScene);
    
    //    CCTransitionPageTurn
    //    作用：创建一个翻页的过渡动画
    //    参数1：过渡动作持续的时间
    //    参数2：切换的目标场景的对象
    //    参数3：是否逆向翻页
    //    reScene = CCTransitionPageTurn::create(t, s, false);
    //    CCDirector::sharedDirector()->replaceScene(reScene);
    
    //    CCTransitionFadeTR
    //    作用：创建一个部落格过渡动画， 从左下到右上
    //    参数1：过渡动作持续的时间
    //    参数2：切换的目标场景的对象
    //    reScene =CCTransitionFadeTR::create(t, s);
    //    CCDirector::sharedDirector()->replaceScene(reScene);
    
    //    CCTransitionFadeBL
    //    作用：创建一个部落格过渡动画， 从右上到左下
    //    参数1：过渡动作持续的时间
    //    参数2：切换的目标场景的对象
    //    reScene = CCTransitionFadeBL::create(t, s);
    //    CCDirector::sharedDirector()->replaceScene(reScene);
    
    //    CCTransitionFadeUp
    //    作用：创建一个从下到上，条形折叠的过渡动画
    //    参数1：过渡动作持续的时间
    //    参数2：切换的目标场景的对象
    //    reScene= CCTransitionFadeUp::create(t, s);
    //    CCDirector::sharedDirector()->replaceScene(s);
    
    //    CCTransitionFadeDown
    //    作用：创建一个从上到下，条形折叠的过渡动画
    //    参数1：过渡动作持续的时间
    //    参数2：切换的目标场景的对象
    //    reScene = CCTransitionFadeDown::create(t, s);
    //    CCDirector::sharedDirector()->replaceScene(reScene);
    
    //    CCTransitionTurnOffTiles
    //    作用：创建一个随机方格消失的过渡动画
    //    参数1：过渡动作的持续时间
    //    参数2：切换的目标场景的对象
        reScene= CCTransitionTurnOffTiles::create(t, s);
        CCDirector::sharedDirector()->replaceScene(reScene);
    
    //    CCTransitionSplitRows
    //    作用：创建一个分行划分切换的过渡动画
    //    参数1：过渡动作的持续时间
    //    参数2：切换的目标场景的对象
    //    reScene = CCTransitionSplitRows::create(t, s);
    //    CCDirector::sharedDirector()->replaceScene(reScene);
    
    //    CCTransitionSplitCols
    //    作用：创建一个分列划分切换的过渡动画
    //    参数1：过渡动作的持续时间
    //    参数2：切换的目标场景的对象
    //    reScene = CCTransitionSplitCols::create(t, s);
    //    CCDirector::sharedDirector()->replaceScene(reScene);
    
    //    CCTransitionFade
    //    作用：创建一个逐渐过渡到目标颜色的切换动画
    //    参数1：过渡动作的持续时间
    //    参数2：切换的目标场景的对象
    //    参数3：目标颜色
    //    reScene= CCTransitionFade::create(t, s, ccc3(255, 0, 0));
    //    CCDirector::sharedDirector()->replaceScene(reScene);
    
    //    CCTransitionFlipX
    //    作用：创建一个x轴反转的切换动画
    //    参数1：过渡动作的持续时间
    //    参数2：切换的目标场景的对象
    //    参数3：反转类型的枚举变量   左右上下
    //    kOrientationDownOver kOrientationLeftOver kOrientationRightOver  kOrientationUpOver
    //    reScene  = CCTransitionFlipX::create(t, s, kOrientationRightOver);
    //    CCDirector::sharedDirector()->replaceScene(reScene);
    
    //    CCTransitionFlipY
    //    参数1：过渡动作的持续时间
    //    参数2：切换的目标场景的对象
    //    参数3：反转类型的枚举变量   左右上下
    //    reScene = CCTransitionFlipY::create(t, s
    //                                        , kOrientationDownOver);
    //    CCDirector::sharedDirector()->replaceScene(reScene);
    
    //    CCTransitionFlipAngular
    //    作用：创建一个带有反转角切换动画
    //        //    参数1：过渡动作的持续时间
    //    参数2：切换的目标场景的对象
    //    参数3：反转类型的枚举变量   左右上下
    //    reScene = CCTransitionFlipAngular::create(t, s, kOrientationLeftOver);
    //    CCDirector::sharedDirector()->replaceScene(reScene);
    
    //    CCTransitionZoomFlipX
    //     作用：创建一个带有缩放的x轴反转切换的动画
    //    参数1：过渡动作的持续时间
    //    参数2：切换的目标场景的对象
    //    参数3：反转类型的枚举变量   左右上下
    //    reScene=CCTransitionZoomFlipX::create(t, s, kOrientationLeftOver);
    //    CCDirector::sharedDirector()->replaceScene(reScene);
    
    //    CCTransitionZoomFlipY
    //     作用：创建一个带有缩放的Y轴反转切换的动画
    //    参数1：过渡动作的持续时间
    //    参数2：切换的目标场景的对象
    //    参数3：反转类型的枚举变量   左右上下
    //    reScene=CCTransitionZoomFlipY::create(t, s, kOrientationDownOver);
    //    CCDirector::sharedDirector()->replaceScene(reScene);
    
    //    CCTransitionZoomFlipAngular
    //     作用：创建一个带有缩放 ，反转角切换的动画
    //    参数1：过渡动作的持续时间
    //    参数2：切换的目标场景的对象
    //    参数3：反转类型的枚举变量   左右上下
    //    reScene=CCTransitionZoomFlipAngular::create(t, s, kOrientationRightOver);
    //    CCDirector::sharedDirector()->replaceScene(reScene);
    
    //    CCTransitionShrinkGrow
    //    创建一个放缩交替的过渡动画
    //    参数1：过渡动作的持续时间
    //    参数2：切换的目标场景的对象
    //    reScene = CCTransitionShrinkGrow::create(t, s);
    //    CCDirector::sharedDirector()->replaceScene(reScene);
    
    //    CCTransitionRotoZoom
    // 创建一个旋转放缩交替的过渡动画
    // 参数1：过渡动作的持续时间
    // 参数2：切换的目标场景的对象
    //    reScene = CCTransitionRotoZoom::create(t, s);
    //    CCDirector::sharedDirector()->replaceScene(reScene);
    
    //    CCTransitionMoveInL
    //    作用：创建一个从左边推入覆盖的过渡动画
    // 参数1：过渡动作的持续时间
    // 参数2：切换的目标场景的对象
    //    reScene = CCTransitionMoveInL::create(t, s);
    //    CCDirector::sharedDirector()->replaceScene(reScene);
    
    //    CCTransitionMoveInR
    //    作用：创建一个从右边推入覆盖的过渡动画
    // 参数1：过渡动作的持续时间
    // 参数2：切换的目标场景的对象
    //    reScene = CCTransitionMoveInR::create(t, s);
    //    CCDirector::sharedDirector()->replaceScene(reScene);
    
    //    CCTransitionMoveInB
    //    作用：创建一个从下边推入覆盖的过渡动画
    // 参数1：过渡动作的持续时间
    // 参数2：切换的目标场景的对象
    //    reScene = CCTransitionMoveInB::create(t, s);
    //    CCDirector::sharedDirector()->replaceScene(reScene);
    
    //    CCTransitionMoveInT
    //    作用：创建一个从上边推入覆盖的过渡动画
    // 参数1：过渡动作的持续时间
    // 参数2：切换的目标场景的对象
    //    reScene = CCTransitionMoveInT::create(t, s);
    //    CCDirector::sharedDirector()->replaceScene(reScene);
    
    //    CCTransitionSlideInL
    //    作用：创建一个从左侧推入并顶出旧场景的过渡动画
    //    参数1：过渡动作的持续时间
    //    参数2：切换的目标场景的对象
    //    reScene  =CCTransitionSlideInL::create(t, s);
    //    CCDirector::sharedDirector()->replaceScene(reScene);
    
    //    CCTransitionSlideInR
    //    作用：创建一个从右侧推入并顶出旧场景的过渡动画
    //    参数1：过渡动作的持续时间
    //    参数2：切换的目标场景的对象
    //    reScene  =CCTransitionSlideInR::create(t, s);
    //    CCDirector::sharedDirector()->replaceScene(reScene);
    
    
    //    CCTransitionSlideInT
    //    作用：创建一个从顶部推入并顶出旧场景的过渡动画
    //    参数1：过渡动作的持续时间
    //    参数2：切换的目标场景的对象
    //    reScene  =CCTransitionSlideInT::create(t, s);
    //    CCDirector::sharedDirector()->replaceScene(reScene);
    
    //    CCTransitionSlideInB
    //    作用：创建一个从下部推入并顶出旧场景的过渡动画
    //    参数1：过渡动作的持续时间
    //    参数2：切换的目标场景的对象
    //reScene  =CCTransitionSlideInB::create(t, s);
//    CCDirector::sharedDirector()->replaceScene(reScene);


}