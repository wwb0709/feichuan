#include "HelloWorldScene.h"
#include "SocketThread.h"
//#include "chat_msg_req.pb.h"
#include "BaseRequestMsg.h"
#include "ResPonseThread.h"
USING_NS_CC;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

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
    i=1;
	this->baseResponseMsg=NULL;
	SocketThread* th=  SocketThread::GetInstance();
	th->start();

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	// ÃÌº”“ª∏ˆ±≥æ∞
	CCSprite* pbg=CCSprite::create("Default.png");
	pbg->setPosition(ccp(visibleSize.width/2,visibleSize.height/2));
	this->addChild(pbg);




	// ¥¥Ω®∑¢ÀÕ∞¥≈•
	CCMenuItemImage* send=CCMenuItemImage::create("send.png","send.png","send.png",this,menu_selector(HelloWorld::menuSendCallback));
	send->setPosition(ccp(visibleSize.width/2,50));
	CCMenu* pme=CCMenu::create(send,NULL);
	pme->setPosition(CCPointZero);
	this->addChild(pme,1);
    

//	// ¥¥Ω® ‰»ÎøÚ
//	CCTextFieldTTF* cctextfiemsg=CCTextFieldTTF::textFieldWithPlaceHolder("input message","Arial",24);
//	cctextfiemsg->setPosition(ccp(origin.x + visibleSize.width/2,280));
//	cctextfiemsg->attachWithIME();
//	this->addChild(cctextfiemsg,2);
	
	ResPonseThread::GetInstance()->addmsgListenerEvent(callFunc_selectormsg(HelloWorld::msgCallBack),this);
	
	ResPonseThread::GetInstance()->addnotconListenerEvent(callFunc_selectormsg(HelloWorld::notContCallBack),this);

	


	 CCLabelTTF *labelWelcome2=CCLabelTTF::create("Welcome","Consolas",48); 
	 labelWelcome2->setPosition(ccp(visibleSize.width/2,visibleSize.height/2));
	 this->addChild(labelWelcome2);
    
    
    CCNode* connet=CCNode::create();
    char tem[40];
    sprintf(tem,"%d%s",10,":");
    CCLabelTTF* lable = CCLabelTTF::create(tem, "Consolas", 24);
    lable->setAnchorPoint(ccp(0,0));
    //		connet->addChild(lable,1);
    //
    ////		CCLabelTTF* msglab=CCLabelTTF::create(this->baseResponseMsg->getMsg().message().c_str(),"Arial",24);
    //        CCLabelTTF* msglab=CCLabelTTF::create(this->baseResponseMsg->msg,"Arial",24);
    //		msglab->setAnchorPoint(ccp(0,0));
    //
    //        CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //
    //		msglab->setPosition(ccp(visibleSize.width/2,visibleSize.height/2));
    //		connet->addChild(msglab,1);
    //
    //		connet->setAnchorPoint(ccp(0,0.5));
//    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //		connet->setPosition(ccp(0,visibleSize.height-i*24));
    lable->setPosition(ccp(visibleSize.width/2,visibleSize.height/2));
    this->addChild(lable,3);
    

    

	return true;
}


void HelloWorld::menuSendCallback(CCObject* pSender)
{
   	CCLabelTTF* lable=CCLabelTTF::create("ddddd","Arial",24);
	BaseRequestMsg<cocos2d::CCString*>* baserlong=new BaseRequestMsg<cocos2d::CCString*>();
	cocos2d::CCString* req = new CCString("hello。。。。");
//	req.set_msgtype(1);
//	req.set_message("ddddd");
    
   
	baserlong->setMessageHead((short)1000,(int)1);
	baserlong->setRequestMessage(req);
	baserlong->sendMessage();
	
	
//	CCDirector::sharedDirector()->end();
//
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    exit(0);
//#endif
}

void HelloWorld::msgCallBack(BaseResponseMsg* baseResponseMsg){			
	this->baseResponseMsg=baseResponseMsg;	
	this->scheduleOnce(schedule_selector(HelloWorld::createConte),0);
}

void HelloWorld::notContCallBack(BaseResponseMsg* baseResponseMsg){
	CCLOG("noconnetction");
	CCMessageBox("not connection","error");
    SocketThread::GetInstance()->state =1;
    SocketThread::GetInstance()->stop();
}

void HelloWorld::createConte(float time){
	
    CCLOG("createConte");
//    return;
	if (this->baseResponseMsg)
	{
	
		int playerId=this->baseResponseMsg->playerId;
        char * msg =this->baseResponseMsg->msg;
//        short code = this->baseResponseMsg->code;
		CCNode* connet=CCNode::create();
		char tem[40];
		sprintf(tem,"---%d%s",playerId,":");
		CCLabelTTF* lable = CCLabelTTF::create(tem, "Consolas", 24,CCSizeMake(100, 26), kCCTextAlignmentLeft);
		lable->setAnchorPoint(ccp(0,0));
		connet->addChild(lable,1);
        
		CCLabelTTF* msglab=CCLabelTTF::create(msg,"Consolas",24,CCSizeMake(300, 26), kCCTextAlignmentLeft);
		msglab->setAnchorPoint(ccp(0,0));
		msglab->setPosition(ccp(100,0));
		connet->addChild(msglab,1);
        
		connet->setAnchorPoint(ccp(0,0.5));
        
        CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
		connet->setPosition(ccp(0,visibleSize.height-i*24));
		this->addChild(connet,3);
        
        CCPoint point = connet->getPosition();
		delete this->baseResponseMsg;
		this->baseResponseMsg=NULL;
		i++;
	}


}