#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

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
    
    
    
//    /////////////////////////////
//    // 2. add a menu item with "X" image, which is clicked to quit the program
//    //    you may modify it.
//
//    // add a "close" icon to exit the progress. it's an autorelease object
//    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
//                                        "CloseNormal.png",
//                                        "CloseSelected.png",
//                                        this,
//                                        menu_selector(HelloWorld::menuCloseCallback) );
//    pCloseItem->setPosition( ccp(WINDOWWIDTH - 20, 20) );
//
//    // create menu, it's an autorelease object
//    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
//    pMenu->setPosition( CCPointZero );
//    this->addChild(pMenu,3);
    
    
//    CCMenuItemImage *pSettingItem = CCMenuItemImage::create(
//                                                          "CloseNormal.png",
//                                                          "CloseSelected.png",
//                                                          this,
//                                                          menu_selector(HelloWorld::menuSettingCallback) );
//    pSettingItem->setPosition( ccp(WINDOWWIDTH - 20, WINDOWHEIGHT-20) );
    CCString* fontName = CCString::create("MarkerFelt-Thin");
    CCMenuItemLabel* settingItem = CCMenuItemLabel::create(CCLabelTTF::create("设置", fontName->getCString(), 18), this, menu_selector(HelloWorld::menuSettingCallback));
//    
//    CCMenuItemFont *pSettingItem = CCMenuItemFont::create("设置", this, menu_selector(HelloWorld::menuSettingCallback));
//    pSettingItem->setColor(ccGRAY);
////    pSettingItem->setFontName("MarkerFelt-Thin");
//    pSettingItem->setFontSize(10);
    settingItem->setPosition( ccp(WINDOWWIDTH - 30, WINDOWHEIGHT-20) );
    
    // create menu, it's an autorelease object
    pSettingMenu = CCMenu::create(settingItem, NULL);
    pSettingMenu->setPosition( CCPointZero );
    this->addChild(pSettingMenu,3);
    

    
    
    //游戏层
    gameLayer = GameLayer::create();
    this->addChild(gameLayer,2);
    
    //设置层
    settingLayer =  SettingLayer::create();
    this->addChild(settingLayer,3);
    settingLayer->setVisible(false);
    
    
    return true;
}


void HelloWorld::menuSettingCallback(CCObject* pSender)
{
    settingLayer->setVisible(true);
    this->pause();
}


//退出游戏
void HelloWorld::quitGame()
{
    CCDirector::sharedDirector()->end();
    CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->purgeSharedSpriteFrameCache();
    
    
    PersonalAudioEngine::sharedEngine()->end();
}

void HelloWorld::onExit()
{

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::restart()
{
    gameLayer->restartGame();
    this->resume();
}
void HelloWorld::pause()
{
    PersonalAudioEngine::sharedEngine()->pauseBackgroundMusic();
    PersonalAudioEngine::sharedEngine()->playEffect(STATIC_DATA_STRING("sound_button"));
    this->operateAllSchedulerAndActions(this, k_Operate_Pause);
//    _touchLayer->setTouchEnabled(false);
    this->setTouchEnabled(false);
    gameLayer->setTouchEnabled(false);
    pSettingMenu->setTouchEnabled(false);
//    this->addChild(SettingLayer);
    settingLayer->setVisible(true);
    
}
void HelloWorld::resume()
{
    this->operateAllSchedulerAndActions(this, k_Operate_Resume);
    PersonalAudioEngine::sharedEngine()->resumeBackgroundMusic();
//    this->removeChild(_menuLayer, false);
    settingLayer->setVisible(false);
    pSettingMenu->setTouchEnabled(true);
    gameLayer->setTouchEnabled(true);
//    _touchLayer->setTouchEnabled(true);
}

//暂停 继续游戏
void HelloWorld::operateAllSchedulerAndActions(cocos2d::CCNode* node, OperateFlag flag)
{
    if(node->isRunning()){
        switch (flag) {
            case k_Operate_Pause:
                node->pauseSchedulerAndActions();
                break;
            case k_Operate_Resume:
                node->resumeSchedulerAndActions();
                break;
            default:
                break;
        }
        CCArray* array = node->getChildren();
        if(array != NULL && array->count()>0){
            CCObject* iterator;
            CCARRAY_FOREACH(array, iterator){
                CCNode* child = (CCNode*)iterator;
                this->operateAllSchedulerAndActions(child, flag);
            }
        }
    }
}