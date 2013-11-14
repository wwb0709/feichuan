//
//  GameLayer.cpp
//  testcocos2d-x
//
//  Created by wangwb on 13-10-31.
//
//

#include "GameLayer.h"
static int __cnt = 1;
bool GameLayer::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }

//    CCSprite* pSprite = CCSprite::create("HelloWorld.png");
//   
//
//    CCSize size = CCDirector::sharedDirector()->getWinSize();
//    pSprite->setPosition(ccp(size.width/2, size.height/2));
//    
//    pSprite->setTag(111);
//    pSprite->setVisible(false);
//    this->addChild(pSprite, 0);
//    
//    
//    
//    
//    // 1. Add a menu item with "X" image, which is clicked to quit the program.
//    
//    // Create a "close" menu item with close icon, it's an auto release object.
//    CCMenuItemImage *pCloseItem = CCMenuItemImage::create("CloseNormal.png",
//                                                                       "CloseSelected.png",
//                                                                       this,
//                                                                       menu_selector(GameLayer::menuCloseCallback));
//  
//    
//    // Place the menu item bottom-right conner.
//    pCloseItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20));
//    
//    // Create a menu with the "close" menu item, it's an auto release object.
//    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
//    pMenu->setPosition(CCPointZero);
//
//    
//    // Add the menu to HelloWorld layer as a child layer.
//    this->addChild(pMenu, 1);
//    

//
//    
//    // Get window size and place the label upper.
//
//    
//    //
//    CCMenuItemImage* myItems = CCMenuItemImage::create(  "normal.png", "down.png",
//                                                                    this,
//                                                                    menu_selector(GameLayer::myMenuCallback));
//
//    myItems->setPosition(ccp(size.width/2, size.height - 50));
//    CCMenu* myMenu = CCMenu::create(myItems, NULL);
//    myMenu->setPosition(CCPointZero);
//
//    this->addChild(myMenu, 1);
//    
//    //
//    CCLabelTTF* pLabel = CCLabelTTF::create("sceondMenu", "Arial",40);
//    CCMenuItemLabel* pItemLabel = CCMenuItemLabel::create(pLabel,
//                                                           this, menu_selector(GameLayer::secondMenuCallback));
//    CCMenu* pSecondMenu = CCMenu::create(pItemLabel, NULL);
//    pItemLabel->setPosition(ccp(size.width/2, size.height-150));
//    pSecondMenu->setPosition(CCPointZero);
//    
//    this->addChild(pSecondMenu, 2);
    //初始化数据
    this->initData();
    
    //加载背景
    this->loadBackground();
    
    
    
    //加载玩家飞机
    this->loadPlayer();
    //加载子弹
    this->madeBullet();
    //子弹还原
    this->resetBullet();
    
    //启动定时器
    this->scheduleUpdate();
    //添加触摸事件
    this->setTouchEnabled(true);
    
    return true;
}

void GameLayer::initData() {
    adjustmentBG = 0;
    bulletSum = 0;
    isBigBullet = false;
    isChangeBullet = false;
    bulletTiming = 900;
    bulletSpeed = 25;
    bigPlan = 0;
    smallPlan = 0;
    mediumPlan = 0;
    props = 0;
    score = 10000;
    isVisible = false;
    isGameOver = false;
    
    addplane = 0;
    addspeed = 0;
    jgtime = 6000;
    


    this->setFoePlanes(CCArray::create());
    
}
void GameLayer::menuCloseCallback(CCObject* pSender)
{
    // "close" menu item clicked
    CCDirector::sharedDirector()->end();
     this->schedule(schedule_selector(GameLayer::logout), 1000.0f);

//    if (changedirct)
//        changedirct =false;
//    else
//        changedirct = true;
}
void GameLayer::logout()
{
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        exit(0);
    #endif
}
void GameLayer::myMenuCallback(CCObject* pSender)
{
    
    CCSprite* pSprite = (CCSprite*)this->getChildByTag(111);
    if(pSprite->isVisible())
        pSprite->setVisible(false);
    else
        pSprite->setVisible(true);
    
    
    
}

void GameLayer::secondMenuCallback(CCObject* pSender)
{
//	CCScene* scene = CCScene::node();
//	CCSprite* pSprite = CCSprite::spriteWithFile("HelloWorld.png");
//    
	CCSize size = CCDirector::sharedDirector()->getWinSize();
    
//	pSprite->setPosition(ccp(size.width/2, size.height/2));
//
//	CCLayer* pLayer = CCLayer::node();
//	pLayer->addChild(pSprite);
//	scene->addChild(pLayer);
//	CCDirector::sharedDirector()->replaceScene(scene);
    CCFoePlane* plane = makeBigFoePlane();
//    plane->setPosition(ccp(size.width/2, size.height/2-50));
    plane->setTag(112);
	this->addChild(plane);
}

//// 造大飞机
//CCFoePlane* GameLayer::makeBigFoePlane()
//{
//    
//    CCArray *bigFoePlaneActionArray = CCArray::create();
//    for (int i = 1 ; i<=2; i++) {
//        CCString* key = CCString::createWithFormat("enemy2_fly_%i.png", i);
//        //从内存池中取出Frame
//        CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(key->getCString());
//        //添加到序列中
//        bigFoePlaneActionArray->addObject(frame);
//    }
//    
//    //将数组转化为动画序列,换帧间隔0.1秒
//    CCAnimation* animPlayer = CCAnimation::createWithSpriteFrames(bigFoePlaneActionArray, 0.1f);
//    //生成动画播放的行为对象
//    CCAnimate* actPlayer = CCAnimate::create(animPlayer);
//    //清空缓存数组
//    bigFoePlaneActionArray->removeAllObjects();
//    
//    CCFoePlane *bigFoePlane = CCFoePlane::createWithSpriteFrameName("enemy2_fly_1.png");
//    bigFoePlane->setPosition(ccp((arc4random()%210)+55, 732));
//    bigFoePlane->planeType = 2;
//    bigFoePlane->hp = 30;
//    bigFoePlane->runAction(CCRepeatForever::create(actPlayer));
//    bigFoePlane->speed = (arc4random()%2)+2 ;
//    bigFoePlane->__id = __cnt++;
//    return bigFoePlane;
//}

GameLayer::GameLayer():__foePlanes(NULL),__prop(NULL)
{

}
GameLayer::~GameLayer()
{
    CC_SAFE_RELEASE_NULL(__foePlanes);
    CC_SAFE_RELEASE_NULL(__prop);
}
void GameLayer::update(float delta)
{
 
    if (!isGameOver) {
        this->backgroundScroll();
        this->firingBullets();
        this->addFoePlane();
        this->moveFoePlane();
        this->collisionDetection();
        this->makeProps();
        this->bulletTimingFn();
        this->resetProps();
        
        this->levelTimingFn();
        
        
    }
    
//    this->backgrouneScroll();
//    this->firingBullets();
    return;
    
    CCFoePlane* plane = (CCFoePlane*)this->getChildByTag(112);
    if (!plane) {
        return;
    }
    CCPoint position = plane->getPosition();
    
    if (changedirct) {
        plane->CCNode::setPosition(ccp(position.x,position.y+plane->speed));
    }
    else
    {
     plane->CCNode::setPosition(ccp(position.x,position.y-plane->speed));
    }
    
}

// 移动敌机
void GameLayer::moveFoePlane()
{
    CCObject* foeObj;
    CCARRAY_FOREACH(this->getFoePlanes(), foeObj){
        CCFoePlane *foe = (CCFoePlane *)foeObj;
        foe->setPosition(ccp(foe->getPositionX(), foe->getPositionY()-foe->speed));
        // 敌机出了底屏
        if (foe->getPositionY()< -75) {
            //CCLog("-------  out of scream  1   __id=%d",foe->__id);
            foe->stopAllActions();
            this->getFoePlanes()->removeObject(foe);
            if(foe == NULL){
            }else{
                //CCLog("-------  out of scream  2   __id=%d",foe->__id);
                foe->removeFromParentAndCleanup(false);
            }
        }
    }
}
// 添加飞机
void GameLayer::addFoePlane()
{
    bigPlan++;
    smallPlan++;
    mediumPlan++;
    
    if (bigPlan>500-addplane) {
        CCFoePlane *foePlane = this->makeBigFoePlane();
        this->addChild(foePlane,3);
        this->getFoePlanes()->addObject(foePlane);
        bigPlan = 0;
    }
    
    if (mediumPlan>400-addplane) {
        CCFoePlane *foePlane = this->makeMediumFoePlane();
        this->addChild(foePlane,3);
        this->getFoePlanes()->addObject(foePlane);
        mediumPlan = 0;
    }
    
    if (smallPlan>45-addplane) {
        CCFoePlane *foePlane = this->makeSmallFoePlane();
        this->addChild(foePlane,3);
        this->getFoePlanes()->addObject(foePlane);
        smallPlan = 0;
    }
    
}

// 造大飞机
CCFoePlane* GameLayer::makeBigFoePlane()
{
    
    CCArray *bigFoePlaneActionArray = CCArray::create();
    for (int i = 1 ; i<=2; i++) {
        CCString* key = CCString::createWithFormat("enemy2_fly_%i.png", i);
        //从内存池中取出Frame
        CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(key->getCString());
        //添加到序列中
        bigFoePlaneActionArray->addObject(frame);
    }
    
    //将数组转化为动画序列,换帧间隔0.1秒
    CCAnimation* animPlayer = CCAnimation::createWithSpriteFrames(bigFoePlaneActionArray, 0.1f);
    //生成动画播放的行为对象
    CCAnimate* actPlayer = CCAnimate::create(animPlayer);
    //清空缓存数组
    bigFoePlaneActionArray->removeAllObjects();
    
    CCFoePlane *bigFoePlane = CCFoePlane::createWithSpriteFrameName("enemy2_fly_1.png");
    bigFoePlane->setPosition(ccp((arc4random()%210)+55, 732));
    bigFoePlane->planeType = 2;
    bigFoePlane->hp = 30;
    bigFoePlane->runAction(CCRepeatForever::create(actPlayer));
    bigFoePlane->speed = (arc4random()%2)+2+addspeed ;
    bigFoePlane->__id = __cnt++;
    return bigFoePlane;
}

// 造中飞机
CCFoePlane* GameLayer::makeMediumFoePlane()
{
    CCFoePlane *mediumFoePlane = CCFoePlane::createWithSpriteFrameName("enemy3_fly_1.png");
    mediumFoePlane->setPosition(ccp((arc4random()%268)+23, 732));
    mediumFoePlane->planeType=3;
    mediumFoePlane->hp=15;
    mediumFoePlane->speed = (arc4random()%3)+2+addspeed;
    mediumFoePlane->__id = __cnt++;
    return mediumFoePlane;
}

// 造小飞机
CCFoePlane* GameLayer::makeSmallFoePlane()
{
    CCFoePlane *smallFoePlane = CCFoePlane::createWithSpriteFrameName("enemy1_fly_1.png");
    smallFoePlane->setPosition(ccp((arc4random()%240)+17, 732));
    smallFoePlane->planeType=1;
    smallFoePlane->hp=1;
    smallFoePlane->speed=(arc4random()%4)+2+addspeed;
    smallFoePlane->__id = __cnt++;
    return smallFoePlane;
}

// 制作道具
void GameLayer::makeProps()
{
    props++;
    if (props>500&&!isVisible) {
//        int retaincount = this->getProp()->retainCount();
        
        this->setProp(CCProps::create());
        
        this->getProp()->initWithType((propsType)((arc4random()%2)+4));
        this->addChild(this->getProp()->getProp());
        this->getProp()->propAnimation();
//        this->getProp()->retain();
        props = 0;
        isVisible = true;
    }
}
//  没接住道具, 出了底屏
void GameLayer::resetProps()
{
    if (isVisible) {
        if(this->getProp()->getProp()->getPositionY() < -75){
            
            this->getProp()->getProp()->stopAllActions();
            this->getProp()->getProp()->removeFromParentAndCleanup(false);
            
            isVisible = false;
            CC_SAFE_RELEASE_NULL(__prop);
            CCLog("==============  没接住道具, 出了底屏");
        }
    }
}



// 子弹持续时间
void GameLayer::bulletTimingFn()
{
    if (isBigBullet) {
        if (bulletTiming>0) {
            bulletTiming--;
        }else {
            isBigBullet = false;
            isChangeBullet = true;
            bulletTiming = 900;
        }
    }
}

// 难度间隔时间
void GameLayer::levelTimingFn()
{

        if (jgtime>0) {
            jgtime--;
        }else {
            addplane = 2;
            addspeed = 1;
            jgtime = 1000;
        }
   
}


// 发射子弹
void GameLayer::firingBullets()
{
    this->bullet->setPosition(ccp(this->bullet->getPositionX(),this->bullet->getPositionY()+bulletSpeed));
    if (this->bullet->getPositionY()>WINDOWHEIGHT-20) {
        //[self resetBullet];
        this->resetBullet();
    }
    
}

// 子弹还原
void GameLayer::resetBullet()
{
    
    if ((isBigBullet&&isChangeBullet)||(!isBigBullet&&isChangeBullet)) {
        this->bullet->removeFromParentAndCleanup(false);
        this->madeBullet();
        isChangeBullet = false;
    }
    
    bulletSpeed = (460-(this->player->getPositionY() + 50))/15;
    if (bulletSpeed<5)
    {
        bulletSpeed=5;
    }
    this->bullet->setPosition(ccp(this->player->getPositionX(),this->player->getPositionY()+50));
}


// 制造子弹
void GameLayer::madeBullet()
{
    bullet= CCSprite::createWithSpriteFrameName((!isBigBullet)?"bullet1.png":"bullet2.png");
    bullet->setAnchorPoint(ccp(0.5,0.5));
    this->addChild(bullet);
}


// 玩家飞机加载
void GameLayer::loadPlayer()
{
    CCArray *playerActionArray = CCArray::create();
    for (int i = 1 ; i<=2; i++) {
        CCString* key = CCString::createWithFormat("hero_fly_%d.png", i);
        //从内存池中取出Frame
        CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(key->getCString());
        //添加到序列中
        playerActionArray->addObject(frame);
    }
    CCLog("----------  %d",playerActionArray->count());
    //将数组转化为动画序列,换帧间隔0.1秒
    CCAnimation* animPlayer = CCAnimation::createWithSpriteFrames(playerActionArray, 0.1f);
    //生成动画播放的行为对象
    CCAnimate* actPlayer = CCAnimate::create(animPlayer);
    //清空缓存数组
    playerActionArray->removeAllObjects();
    
    player = CCSprite::createWithSpriteFrameName("hero_fly_1.png");
    player->setPosition(ccp(160,50));
    this->addChild(player,3);
    player->runAction(CCRepeatForever::create(actPlayer));
    
    
}




CCPoint GameLayer::boundLayerPos(CCPoint newPos)
{
    CCPoint retval = newPos;
    retval.x = player->getPositionX()+newPos.x;
    retval.y = player->getPositionY()+newPos.y;
    
    if (retval.x>=286) {
        retval.x = 286;
    }else if (retval.x<=33) {
        retval.x = 33;
    }
    
    if (retval.y >=WINDOWHEIGHT-50) {
        retval.y = WINDOWHEIGHT-50;
    }else if (retval.y <= 43) {
        retval.y = 43;
    }
    
    return retval;
}

void  GameLayer::panForTranslation(CCPoint translation){
   
//    CCFoePlane* plane = (CCFoePlane*)this->getChildByTag(112);
//    if (!plane) {
//        return;
//    }
    
     player->setPosition(this->boundLayerPos(translation));
    
}
//触摸事件
bool GameLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
    CCLOG("ccTouchBegan");
    return true;
}
void GameLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){
     CCLOG("ccTouchMoved");
    CCPoint touchLocation = this->convertTouchToNodeSpace(pTouch);
    CCPoint oldTouchLocation = pTouch->getPreviousLocationInView();
    
    oldTouchLocation = CCDirector::sharedDirector()->convertToGL(oldTouchLocation);
    oldTouchLocation = this->convertToNodeSpace(oldTouchLocation);
    
    CCPoint translation = ccpSub(touchLocation, oldTouchLocation);
    this->panForTranslation(translation);

}

void GameLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent){
    CCLOG("ccTouchEnded");
    
}

void GameLayer::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent){
    CCLOG("ccTouchCancelled");
    
}

void GameLayer::registerWithTouchDispatcher(){
    CCLOG("registerWithTouchDispatcher");
    
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority + 1, true);
    
}



/* ----资源加载-------*/

// 载入背景
void GameLayer::loadBackground()
{
    this->BG1 = CCSprite::createWithSpriteFrameName("background_2.png");
    this->BG1->setAnchorPoint(ccp(0.5, 0));
    this->BG1->setPosition(ccp(160, adjustmentBG));
    this->addChild(BG1,0);
    
    this->BG2 = CCSprite::createWithSpriteFrameName("background_2.png");
    this->BG2->setAnchorPoint(ccp(0.5, 0));
    this->BG2->setPosition(ccp(160, 568+adjustmentBG));
    this->addChild(BG2,0);
    
    this->scoreLabel = CCLabelTTF::create("0000", "MarkerFelt-Thin", 18.0,CCSizeMake(200, 0), kCCTextAlignmentLeft);
    this->scoreLabel->setColor(ccc3(0, 0, 0));
    this->scoreLabel->setAnchorPoint(ccp(0,1));
    this->scoreLabel->setPosition(ccp(30, WINDOWHEIGHT-10));
    
    //this->scoreLabel->setString(CCString::createWithFormat("%u",score)->getCString());
    this->addChild(this->scoreLabel,4);
    
}

// 背景滚动
void GameLayer::backgroundScroll()
{
    adjustmentBG--;
    
    if (adjustmentBG<=0) {
        adjustmentBG = 568;
    }
    BG1->setPosition(ccp(160, adjustmentBG));
    BG2->setPosition(ccp(160, adjustmentBG-568+1));
    
    
}


// 碰撞检测
void GameLayer::collisionDetection()
{
    
    // 判断子弹跟敌机是否碰撞
    CCRect bulletRec = bullet->boundingBox();
    
    CCObject* foeObj;
    CCARRAY_FOREACH(this->getFoePlanes(), foeObj){
        CCFoePlane *foePlane = (CCFoePlane *)foeObj;
        if (bulletRec.intersectsRect(foePlane->boundingBox())  ) {
            this->resetBullet();
            this->fowPlaneHitAnimation(foePlane);
            foePlane->hp = foePlane->hp - (isBigBullet?2:1);
            if (foePlane->hp<=0) {
                //CCLog("##### move out animation:   %d   for hp(%d)",foePlane->__id,foePlane->hp);
                this->fowPlaneBlowupAnimation(foePlane);
                //CCLog("##### move out begin:   %d   for hp(%d)",foePlane->__id,foePlane->hp);
                this->getFoePlanes()->removeObject(foePlane);
                //CCLog("##### move out end:   %d   for hp(%d)",foePlane->__id,foePlane->hp);
            }
        }
    }
    
    // 飞机跟打飞机
    CCRect playerRec = player->boundingBox();
    playerRec.origin.x += 25;
    playerRec.size.width -= 50;
    playerRec.origin.y -= 10;
    playerRec.size.height -= 10;
    
    CCObject *foeObj3;
    CCARRAY_FOREACH(this->getFoePlanes(), foeObj3){
        CCFoePlane *foePlane = (CCFoePlane *)foeObj3;
        if (playerRec.intersectsRect(foePlane->boundingBox()) ) {
            CCLog("@@@@@ shit,i was killed  by:   %d",foePlane->__id);
            
            this->playerBlowupAnimation();
            this->fowPlaneBlowupAnimation(foePlane);// 同归于尽
            this->getFoePlanes()->removeObject(foePlane);
            this->gameOver();
        }
    }
    
    // 飞机跟道具
    
    if (isVisible) {
        CCRect playerRec1 = player->boundingBox();
        CCRect propRec = this->getProp()->getProp()->boundingBox();
        if (playerRec1.intersectsRect(propRec)) {
            
            this->getProp()->getProp()->stopAllActions();
            this->getProp()->getProp()->removeFromParentAndCleanup(false);
            isVisible = false;
            
            if (this->getProp()->type == propsTypeBullet) {
                CCLog("========= 大力丸子");
                isBigBullet = true;
                isChangeBullet = true;
            }else if (this->getProp()->type == propsTypeBomb) {
                CCLog("========= 意念一直线，敌人死光光");
                CCObject *foeObj4;
                CCARRAY_FOREACH(this->getFoePlanes(), foeObj4){
                    CCFoePlane *foePlane = (CCFoePlane *)foeObj4;
                    this->fowPlaneBlowupAnimation(foePlane);
                }
                this->getFoePlanes()->removeAllObjects();
            }
            CC_SAFE_RELEASE_NULL(__prop);
        }
    }
    
    
}



// 添加打击效果
void GameLayer::fowPlaneHitAnimation(CCFoePlane* foePlane)
{
    if (foePlane->planeType == 3) {
        if (foePlane->hp==13) {
            CCArray *playerActionArray = new CCArray;
            for (int i = 1 ; i<=2; i++) {
                CCString* key = CCString::createWithFormat("enemy3_hit_%d.png",i);
                //从内存池中取出Frame
                CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(key->getCString());
                //添加到序列中
                playerActionArray->addObject(frame);
            }
            
            //将数组转化为动画序列,换帧间隔0.1秒
            CCAnimation* animPlayer = CCAnimation::createWithSpriteFrames(playerActionArray,0.1f);
            //生成动画播放的行为对象
            CCAnimate* actPlayer = CCAnimate::create(animPlayer);
            //清空缓存数组
            playerActionArray->removeAllObjects();
            foePlane->stopAllActions();
            foePlane->runAction(CCRepeatForever::create(actPlayer));
        }
    }else if (foePlane->planeType == 2) {
        if (foePlane->hp==20) {
            CCArray *playerActionArray = new CCArray;
            for (int i = 1 ; i<=1; i++) {
                CCString* key = CCString::createWithFormat("enemy2_hit_%d.png",i);
                //从内存池中取出Frame
                CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(key->getCString());
                //添加到序列中
                playerActionArray->addObject(frame);
            }
            
            //将数组转化为动画序列,换帧间隔0.1秒
            CCAnimation* animPlayer = CCAnimation::createWithSpriteFrames(playerActionArray,0.1f);
            //生成动画播放的行为对象
            CCAnimate* actPlayer = CCAnimate::create(animPlayer);
            //清空缓存数组
            playerActionArray->removeAllObjects();
            foePlane->stopAllActions();
            foePlane->runAction(CCRepeatForever::create(actPlayer));
        }
    }
}

// 爆炸动画
void GameLayer::fowPlaneBlowupAnimation(CCFoePlane*foePlane)
{
    int forSum=0;
    if (foePlane->planeType == 3) {
        forSum = 4;
        score+=6000;
    }else if (foePlane->planeType  == 2) {
        score+=3000;
        forSum = 7;
    }else if (foePlane->planeType  == 1) {
        forSum = 4;
        score+=1000;
    }
    
    this->scoreLabel->setString(CCString::createWithFormat("%d",score)->getCString());
    
    foePlane->stopAllActions();
    CCArray *foePlaneActionArray = new CCArray;
    
    for (int i = 1; i<=forSum ; i++ ) {
        CCString* key = CCString::createWithFormat("enemy%d_blowup_%i.png",foePlane->planeType , i);
        //从内存池中取出Frame
        CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(key->getCString());
        //添加到序列中
        foePlaneActionArray->addObject(frame);
    }
    
    //将数组转化为动画序列,换帧间隔0.1秒
    CCAnimation* animPlayer = CCAnimation::createWithSpriteFrames(foePlaneActionArray,0.1f);
    //生成动画播放的行为对象
    CCAnimate* actFowPlane = CCAnimate::create(animPlayer);
    //清空缓存数组
    foePlaneActionArray->removeAllObjects();
    
    //CCLog("----- 爆炸动画 begin: %d",foePlane->__id);
    
    foePlane->runAction(CCSequence::create(actFowPlane, CCCallFuncN::create(this, callfuncN_selector(GameLayer::blowupEnd)), NULL));
    
    
    //CCLog("----- 爆炸动画 end: %d",foePlane->__id);
}

// 飞机爆炸
void GameLayer::playerBlowupAnimation()
{
    
    CCArray *foePlaneActionArray = new CCArray;
    for (int i = 1; i<=4 ; i++ ) {
        CCString* key = CCString::createWithFormat("hero_blowup_%i.png", i);
        //从内存池中取出Frame
        CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(key->getCString());
        //添加到序列中
        foePlaneActionArray->addObject(frame);
    }
    
    //将数组转化为动画序列,换帧间隔0.1秒
    CCAnimation* animPlayer = CCAnimation::createWithSpriteFrames(foePlaneActionArray,0.1f);
    //生成动画播放的行为对象
    CCAnimate* actFowPlane = CCAnimate::create(animPlayer);
    //清空缓存数组
    foePlaneActionArray->removeAllObjects();
    
    player->runAction(CCSequence::create(actFowPlane, NULL));
}
//
void GameLayer::playerBlowupEnd(CCObject* sender)
{
    
}

void GameLayer::blowupEnd(CCObject* sender)
{
    CCFoePlane *foePlane = (CCFoePlane *) sender;
    CCLog("----- blow up end: %d",foePlane->__id);
    foePlane->removeFromParentAndCleanup(false);
}

void GameLayer::gameOver()
{
    
    isGameOver = true;
    CCObject *nodeObj;
    CCARRAY_FOREACH(this->getChildren(), nodeObj){
        CCNode *node = (CCNode *)nodeObj;
        node->stopAllActions();
    }
    //设置成绩
    bool isGood = false;
    int lastScore =UserData::sharedUserData()->getScore();
    if(this->score>UserData::sharedUserData()->getScore())
    {
    isGood = true;
    UserData::sharedUserData()->alertScore(this->score);
    }
    
    CCLabelTTF *gameOverLabel = CCLabelTTF::create("太空大战" ,"MarkerFelt-Thin",35);
    gameOverLabel->setPosition(ccp(160, 400));
    this->addChild(gameOverLabel,4);
    
    CCLabelTTF *scoreLabel = CCLabelTTF::create(CCString::createWithFormat("本次%d",this->score)->getCString() ,"MarkerFelt-Thin",25,CCSizeMake(200, 0), kCCTextAlignmentCenter);
    scoreLabel->setPosition(ccp(160, 250));
    this->addChild(scoreLabel,4);
    
    if (UserData::sharedUserData()->getScore()>0) {
        CCLabelTTF *scoreLabel = CCLabelTTF::create(CCString::createWithFormat("最高记录：%d",UserData::sharedUserData()->getScore())->getCString() ,"MarkerFelt-Thin",25,CCSizeMake(200, 0), kCCTextAlignmentCenter);
        scoreLabel->setPosition(ccp(160, 350));
        this->addChild(scoreLabel,4);
    }
    
    if (isGood) {
        CCLabelTTF *scoreLabel = CCLabelTTF::create(CCString::createWithFormat("恭喜你超越了最高记录%d！",lastScore)->getCString() ,"MarkerFelt-Thin",25,CCSizeMake(280, 0), kCCTextAlignmentCenter);
        scoreLabel->setPosition(ccp(160, 300));
        this->addChild(scoreLabel,4);
    }
    else
    {
        CCLabelTTF *scoreLabel = CCLabelTTF::create("加油哦！" ,"MarkerFelt-Thin",25,CCSizeMake(200, 0), kCCTextAlignmentCenter);
        scoreLabel->setPosition(ccp(160, 300));
        this->addChild(scoreLabel,4);
    
    }
    
    CCMenuItemFont *gameOverItem = CCMenuItemFont::create("重玩", this, menu_selector(GameLayer::restartGame));
    gameOverItem->setFontName("MarkerFelt-Thin");
    gameOverItem->setFontSize(30);
    CCMenu *restart = CCMenu::create(gameOverItem,NULL);
    restart->setPosition(ccp(160, 200));
    this->addChild(restart,4);
    
    //添加触摸事件
    this->setTouchEnabled(false);
}


void GameLayer::restartGame()
{
    //添加触摸事件
    this->setTouchEnabled(true);
    //__cnt = 1;
    this->removeAllChildrenWithCleanup(false);

    this->initData();
    this->loadBackground();
    this->loadPlayer();
    this->madeBullet();
    this->resetBullet();
    
}



void GameLayer::pauseGame()
{
    this->unscheduleUpdate();
    CCObject *nodeObj;
    CCARRAY_FOREACH(this->getChildren(), nodeObj){
        CCNode *node = (CCNode *)nodeObj;
        node->stopAllActions();
    }
}

void GameLayer::resumeGame()
{
    
    
    CCArray *playerActionArray = CCArray::create();
    for (int i = 1 ; i<=2; i++) {
        CCString* key = CCString::createWithFormat("hero_fly_%d.png", i);
        //从内存池中取出Frame
        CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(key->getCString());
        //添加到序列中
        playerActionArray->addObject(frame);
    }
    CCLog("----------  %d",playerActionArray->count());
    //将数组转化为动画序列,换帧间隔0.1秒
    CCAnimation* animPlayer = CCAnimation::createWithSpriteFrames(playerActionArray, 0.1f);
    //生成动画播放的行为对象
    CCAnimate* actPlayer = CCAnimate::create(animPlayer);
    //清空缓存数组
    playerActionArray->removeAllObjects();
    
   
    player->runAction(CCRepeatForever::create(actPlayer));
    
    this->scheduleUpdate();
    
}