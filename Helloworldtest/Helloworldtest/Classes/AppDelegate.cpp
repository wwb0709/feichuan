#include "cocos2d.h"
#include "CCEGLView.h"
#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

#include "AppMacros.h"

#include <map>

using namespace CocosDenshion;

USING_NS_CC;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
    SimpleAudioEngine::end();
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
	CCEGLView *pEGLView = CCEGLView::sharedOpenGLView();
    pDirector->setOpenGLView(pEGLView);
	
	CCSize frameSize = pEGLView->getFrameSize();
	float ratio = frameSize.width / frameSize.height;
	float ratio1 = largeDesignResolutionSize.width / largeDesignResolutionSize.height;
	float ratio2 = mediumDesignResolutionSize.width / mediumDesignResolutionSize.height;
	float ratio3 = smallDesignResolutionSize.width / smallDesignResolutionSize.height;
	float d1 = abs(ratio - ratio1);
	float d2 = abs(ratio - ratio2);
	float d3 = abs(ratio - ratio3);
	std::map<float, CCSize> designSize;
	designSize[d1] = largeDesignResolutionSize;
	designSize[d2] = mediumDesignResolutionSize;
	designSize[d3] = smallDesignResolutionSize;
	std::map<float, CCSize>::reverse_iterator iter = designSize.rbegin();
	//得到key最大的，因此我这里是横屏，所以以高度为基准，为了确保缩放后宽度能全屏，所以选取宽高比最大的为设计分辨率
	CCSize designResolutionSize = iter->second;

	//pEGLView->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionNoBorder);
	pEGLView->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionShowAll);
	//pEGLView->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionExactFit);

	if (frameSize.height > mediumResource.size.height)
	{ 
		CCFileUtils::sharedFileUtils()->setResourceDirectory(largeResource.directory);
        pDirector->setContentScaleFactor(largeResource.size.height/designResolutionSize.height);
	}
    else if (frameSize.height > smallResource.size.height)
    { 
        CCFileUtils::sharedFileUtils()->setResourceDirectory(mediumResource.directory);
        pDirector->setContentScaleFactor(mediumResource.size.height/designResolutionSize.height);
    }
	else
    { 
		CCFileUtils::sharedFileUtils()->setResourceDirectory(smallResource.directory);
        pDirector->setContentScaleFactor(smallResource.size.height/designResolutionSize.height);
    }

    pDirector->setDisplayStats(true);

    pDirector->setAnimationInterval(1.0 / 60);

    CCScene *pScene = HelloWorld::scene();

    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();

    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();

    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
