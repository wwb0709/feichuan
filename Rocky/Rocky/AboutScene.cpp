//
//  AboutScene.cpp
//  Rocky
//
//  Created by Tuyuer on 13-2-24.
//
//

#include "AboutScene.h"
#include "OptionScene.h"
USING_NS_CC;

CCScene * AboutScene::scene(){
    CCLayer * optionLayer=AboutScene::create();
    CCScene * optionScene=CCScene::create();
    optionScene->addChild(optionLayer);
    return optionScene;
}

void AboutScene::onEnterTransitionDidFinish(){
    int fontSize=36;
    if (CCDirector::sharedDirector()->getWinSize().width==960) {
        fontSize=72;
    }
    
    CCLabelTTF * lblPlay=CCLabelTTF::create("Created By HitJoy.cn", "Arial", fontSize);
 
    CCLabelTTF * lblAbout=CCLabelTTF::create("Powered With Cocos2dX", "Arial", fontSize);
    
    CCLabelTTF * lblLua=CCLabelTTF::create("Supported With Lua", "Arial", fontSize);
    this->addChild(lblPlay);
    this->addChild(lblAbout);
    this->addChild(lblLua);
    
    
    CCLabelTTF * lblBack=CCLabelTTF::create("Back", "Arial", fontSize);
    CCMenuItemLabel * miLabelPlay=CCMenuItemLabel::create(lblBack, this, menu_selector(AboutScene::backToOption));
    
    if (CCDirector::sharedDirector()->getWinSize().width==960) {
        lblPlay->setPosition(ccp(240*2,220*2));
        lblAbout->setPosition(ccp(240*2,160*2));
        lblLua->setPosition(ccp(240*2, 100*2));
        miLabelPlay->setPosition(ccp(50*2,280*2));
       
    }else{
        lblPlay->setPosition(ccp(240,220));
        lblAbout->setPosition(ccp(240,160));
        lblLua->setPosition(ccp(240, 100));
        miLabelPlay->setPosition(ccp(50,280));
    }
    
    CCMenu * optionMenu=CCMenu::create(miLabelPlay,NULL);
    this->addChild(optionMenu);
    optionMenu->setPosition(CCPointZero);
}

void AboutScene::backToOption(){
    CCDirector::sharedDirector()->replaceScene(OptionScene::scene());
}