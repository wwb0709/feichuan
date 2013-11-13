//
//  testcocos2d_xAppDelegate.cpp
//  testcocos2d-x
//
//  Created by wangwb on 13-10-15.
//  Copyright __MyCompanyName__ 2013年. All rights reserved.
//

#include "AppDelegate.h"

#include "cocos2d.h"
#include "HelloWorldScene.h"
#include "welcomlayer.h"
#include "SimpleAudioEngine.h"
#include "PersonalAudioEngine.h"

USING_NS_CC;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    std::map <int, int> m1, m2, m3;
    std::map <int, int>::iterator m1_Iter;
    m1[1]=10;
    m1[4]=11;
    m1[3]=2;

     std::map<int, int>::reverse_iterator iter = m1.rbegin();
//    　　m1.insert ( pair<int, int> ( 1, 10 ) );
//    　　m1.insert ( pair <int, int> ( 2, 20 ) );
//    　　m1.insert ( pair <int, int> ( 3, 30 ) );
//    　　m2.insert ( pair <int, int> ( 10, 100 ) );
//    　　m2.insert ( pair <int, int> ( 20, 200 ) );
//    　　m3.insert ( pair <int, int> ( 30, 300 ) );
    m1_Iter = m1.begin( );
    int c= iter->first;
    c = iter->second;
    
    CCFileUtils::sharedFileUtils()->setResourceDirectory("iphone");
    const char* ch = CCFileUtils::sharedFileUtils()->getResourceDirectory();
 
    
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
    pDirector->setOpenGLView(pEGLView);
    CCSize size = pDirector->getWinSize();
    
    pEGLView->setDesignResolutionSize(320, 480, kResolutionShowAll);
    size = pDirector->getWinSize();
    
    
    
    CCSize frameSize = pEGLView->getFrameSize();
    
    // turn on display FPS
//    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

//    // create a scene. it's an autorelease object
//    CCScene *pScene = HelloWorld::scene();
//
//    // run
//    pDirector->runWithScene(pScene);
    
    
    CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->addSpriteFramesWithFile("gameArts.plist", "gameArts.png");
    
    // create a scene. it's an autorelease object
    CCScene *pScene = welcomlayer::scene();
    
    // run
    pDirector->runWithScene(pScene);
    
//    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(STATIC_DATA_STRING("bg_music"));
//    CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(1);
//    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(STATIC_DATA_STRING("bg_music"),true);
//     CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(STATIC_DATA_STRING("bg_music"));
//    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(STATIC_DATA_STRING("bg_music"),true);
//    CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.5);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->pause();

    // if you use SimpleAudioEngine, it must be paused
CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->resume();
    
    // if you use SimpleAudioEngine, it must resume here
CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
