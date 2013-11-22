//
//  OptionScene.cpp
//  Rocky
//
//  Created by Tuyuer on 13-2-24.
//
//

#include "OptionScene.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "AboutScene.h"
USING_NS_CC;
using namespace CocosDenshion;

CCScene * OptionScene::scene(){
    CCLayer * optionLayer=OptionScene::create();
    CCScene * optionScene=CCScene::create();
    optionScene->addChild(optionLayer);
    return optionScene;
}

void OptionScene::onEnterTransitionDidFinish(){
    int fontSize=36;
    if (CCDirector::sharedDirector()->getWinSize().width==960) {
        fontSize=72;
    }
    
    CCLabelTTF * lblPlay=CCLabelTTF::create("Start Game", "Arial", fontSize);
    CCMenuItemLabel * miLabelPlay=CCMenuItemLabel::create(lblPlay, this, menu_selector(OptionScene::startGame));
    
    CCLabelTTF * lblAbout=CCLabelTTF::create("About Us", "Arial", fontSize);
    CCMenuItemLabel * miLabelAbout=CCMenuItemLabel::create(lblAbout, this, menu_selector(OptionScene::toAbout));
    
    if (CCDirector::sharedDirector()->getWinSize().width==960) {
        miLabelPlay->setPosition(ccp(240*2,180*2));
        miLabelAbout->setPosition(ccp(240*2,120*2));
    }else{
        miLabelPlay->setPosition(ccp(240,180));
        miLabelAbout->setPosition(ccp(240,120));
    }
   
    
    CCMenu * optionMenu=CCMenu::create(miLabelPlay,miLabelAbout,NULL);
    this->addChild(optionMenu);
    optionMenu->setPosition(CCPointZero);
}

void OptionScene::startGame(){
    CCDirector::sharedDirector()->replaceScene(GameScene::scene());
    const char * songPath=CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("song1.mp3");
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic(songPath, true);
}

void OptionScene::toAbout(){
    CCDirector::sharedDirector()->replaceScene(AboutScene::scene());
}




