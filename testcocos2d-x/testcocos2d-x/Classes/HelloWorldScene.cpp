#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "GameLayer.h"
#include "PersonalAudioEngine.h"

//void HelloWorld::onEnterTransitionDidFinish()
//{
//    CCScene::onEnterTransitionDidFinish();
//  
//}

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);
//    PersonalAudioEngine::sharedEngine()->playBackgroundMusic(STATIC_DATA_STRING("bg_music"),true);
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    CCSprite* pSprite = CCSprite::create("HelloWorld.png");
    pSprite->setPosition(ccp(200, 100));
    pSprite->setRotation(45);
    
//    this->addChild(pSprite, 0);
    
//    CCCamera *cam;
//    cam = pSprite->getCamera();
//    cam->setEyeXYZ(0, -200, 200);
    
    
    
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback) );
    pCloseItem->setPosition( ccp(WINDOWWIDTH - 20, 20) );

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu,3);
//
//    /////////////////////////////
//    // 3. add your codes below...
//
//    // add a label shows "Hello World"
//    // create and initialize a label
//    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Thonburi", 34);
//
//    // ask director the window size
//    CCSize size = CCDirector::sharedDirector()->getWinSize();
//
//    // position the label on the center of the screen
//    pLabel->setPosition( ccp(size.width / 2, size.height - 20) );
//
//    // add the label as a child to this layer
//    this->addChild(pLabel, 1);
//
//    // add "HelloWorld" splash screen"
//    CCSprite* sprite1 = CCSprite::create("HelloWorld.png");
//
//    sprite1->setPosition(ccp(20,40));
//    
//    sprite1->setAnchorPoint(ccp(1,1));
//    // position the sprite on the center of the screen
////    pSprite->setPosition( ccp(size.width/2, size.height/2) );
//
//    // add the sprite as a child to this layer
//    this->addChild(sprite1, 0);
//    
//    
//    
//    CCSprite *sprite2 = CCSprite::create("CloseNormal.png");
//    
//    sprite2->setPosition(ccp(-5,-20));
//    
//    sprite2->setAnchorPoint(ccp(1,1));
//   
//    this->addChild(sprite2);
//    
//    CCPoint point1 = sprite1->convertToNodeSpace(sprite2->getPosition());
//    
//    CCPoint point2 = sprite1->convertToWorldSpace(sprite2->getPosition());
//    
//    CCPoint point3 = sprite1->convertToNodeSpaceAR(sprite2->getPosition());
//    
//    CCPoint point4 = sprite1->convertToWorldSpaceAR(sprite2->getPosition());
//
//  
//    CCLog("position = (%f,%f)",point1.x,point1.y);
//   
//    CCLog("position = (%f,%f)",point2.x,point2.y);
//    
//    CCLog("position = (%f,%f)",point3.x,point3.y);
//   
//    CCLog("position = (%f,%f)",point4.x,point4.y);
    
//    this->scheduleUpdate();
    
    
    
    GameLayer * gamelayer = GameLayer::create();
    this->addChild(gamelayer,2);
    
    return true;
}




void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
    CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->purgeSharedSpriteFrameCache();
//   this->schedule(schedule_selector(HelloWorld::logout), 10.0f);
}
//void HelloWorld::onEnter()
//{
//    PersonalAudioEngine::sharedEngine()->playBackgroundMusic(STATIC_DATA_STRING("bg_music"),true);
//
//}
void HelloWorld::onExit()
{

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::logout()
{

}
void HelloWorld::update(float delta){
    CCLog("HelloWorld::update");
}
