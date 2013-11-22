//
//  GameScene.cpp
//  Rocky
//
//  Created by Tuyuer on 13-2-3.
//
//

#include "GameScene.h"
#include "InputLayer.h"
#include "Player.h"
#include "Robot.h"
#include "CCLuaEngine.h"
USING_NS_CC;

GameScene::GameScene(){
    _arrayRobots=CCArray::createWithCapacity(100);
    _arrayRobotsToRemove=CCArray::createWithCapacity(100);
    _arrayRobotsToAdd=CCArray::createWithCapacity(100);
    _arrayRobotsToRender=CCArray::createWithCapacity(100);
    _arrayRobots->retain();
    _arrayRobotsToAdd->retain();
    _arrayRobotsToRemove->retain();
    _arrayRobotsToRender->retain();
    
    CCLuaEngine* pEngine = CCLuaEngine::defaultEngine();
    
    std::string path = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("RobotLogic.lua");
    pEngine->addSearchPath(path.substr(0, path.find_last_of("/")).c_str());
    pEngine->executeScriptFile(path.c_str());
}
GameScene::~GameScene(){
    CC_SAFE_RELEASE(_arrayRobots);
    CC_SAFE_RELEASE(_arrayRobotsToAdd);
    CC_SAFE_RELEASE(_arrayRobotsToRemove);
    CC_SAFE_RELEASE(_arrayRobotsToRender);
    this->unscheduleUpdate();
}

CCScene * GameScene::scene(){
    CCLayer * gameLayer=GameScene::create();
    CCScene * gameScene=CCScene::create();
    gameScene->addChild(gameLayer);
    return gameScene;
}

void GameScene::onEnter(){
    CCLayer::onEnter();
}

void GameScene::onEnterTransitionDidFinish(){
    CCLayer::onEnterTransitionDidFinish();
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("pd_sprites.plist");
    _batchNode=CCSpriteBatchNode::create("pd_sprites.pvr.ccz",100);
    this->initRobots();
    this->initUI();
    this->scheduleUpdate();
    this->schedule(schedule_selector(GameScene::reOrderRoles), 0.2);
    this->schedule(schedule_selector(GameScene::robotLogic), 1);
}

void GameScene::initRobots(){
    for (int i=0; i<40; i++) {
        Robot * robot=Robot::createWithSpriteFrameName("robot_idle_00.png");
        _arrayRobots->addObject(robot);
    }
}

void GameScene::initUI(){
    _gameLayer=CCLayer::create();
    this->addChild(_gameLayer);
    //add map
    _tileMap=CCTMXTiledMap::create("pd_tilemap.tmx");
    _gameLayer->addChild(_tileMap);
    //map box
    _mapBoundingSize=CCSizeMake(_tileMap->getTileSize().width* _tileMap->getMapSize().width, 160);
    
    //add batchNode
    _gameLayer->addChild(_batchNode);
    
    //add Player
    CCSize winSize=CCDirector::sharedDirector()->getWinSize();
    _player=Player::createWithSpriteFrameName("hero_idle_00.png");
    _batchNode->addChild(_player);
    _player->setPosition(ccp(40, 160),_mapBoundingSize);
    _player->setState(kRoleStateIdle);
   
    _arrayRobotsToRender->addObject(_player);
    for (int i=0; i<_arrayRobots->count(); i++) {
        Robot * robotTest=(Robot*)_arrayRobots->objectAtIndex(i);
        _batchNode->addChild(robotTest);
        robotTest->setPosition(ccp(winSize.width/2+60*i, winSize.height/2),_mapBoundingSize);
        _arrayRobotsToAdd->addObject(robotTest);
    }
    
    //add input
    _inputLayer=InputLayer::create();
    _inputLayer->setDelegate(this);
    this->addChild(_inputLayer);
    
    if (CCDirector::sharedDirector()->getWinSize().width!=480) {
        this->setScale(2.0);
        this->setPosition(ccp(480,320));
    }
}

void GameScene::retry(){
    
    this->removeAllChildren();
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("pd_sprites.plist");
    _batchNode=CCSpriteBatchNode::create("pd_sprites.pvr.ccz",100);
    
    _arrayRobots->removeAllObjects();
    _arrayRobotsToAdd->removeAllObjects();
    _arrayRobotsToRemove->removeAllObjects();
    _arrayRobotsToRender->removeAllObjects();
    this->unscheduleAllSelectors();
    
    this->initRobots();
    this->initUI();
    this->scheduleUpdate();
    this->schedule(schedule_selector(GameScene::reOrderRoles), 0.2);
    this->schedule(schedule_selector(GameScene::robotLogic), 1);
}

void GameScene::update(float fDelta){
    //检测机器人的攻击碰撞
    for (int i=0; i<_arrayRobots->count(); i++) {
        Robot * robotTest=(Robot*)_arrayRobots->objectAtIndex(i);
        bool bHit=robotTest->m_attackBox.actual.intersectsRect(_player->m_hitBox.actual);
        RoleState playerState = _player->getState();
        int yOffset=abs(_player->getPosition().y-robotTest->getPosition().y);
        if (robotTest->getState()==kRoleStateAttack&&
            playerState!=kRoleStateKnockedOut&&
            playerState!=kRoleStateHurt&&
            yOffset<10&&
            bHit) {
            
            _player->hurt(robotTest->getDamage());
            if (_player->getState()==kRoleStateKnockedOut) {
                CCLabelTTF * lblAbout=CCLabelTTF::create("Tap Play Again !!", "Arial", 36);
                CCMenuItemLabel * miLabelAbout=CCMenuItemLabel::create(lblAbout, this, menu_selector(GameScene::retry));
                
                miLabelAbout->setPosition(ccp(240,180));
                
                CCMenu * optionMenu=CCMenu::create(miLabelAbout,NULL);
                this->addChild(optionMenu);
                optionMenu->setPosition(CCPointZero);
                _inputLayer->removeFromParent();
            }
        }
    }
}

void GameScene::setViewpointCenter(CCPoint pTest){
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    int x = MAX(pTest.x, 480 / 2);
    x = MIN(x, _mapBoundingSize.width - 480 / 2);
    CCPoint actualPosition = ccp(x, 0);
    
    CCPoint centerOfView = ccp(480/2, 0);
    CCPoint viewPoint = ccpSub(centerOfView, actualPosition);
    _gameLayer->setPosition(viewPoint);
}

void GameScene::reOrderRoles(){
    _arrayRobotsToRender->removeObjectsInArray(_arrayRobotsToRemove);
    _arrayRobotsToRender->addObjectsFromArray(_arrayRobotsToAdd);

    for (int i=0; i<_arrayRobotsToRender->count(); i++) {
        Role * role=(Role *)_arrayRobotsToRender->objectAtIndex(i);
        _batchNode->reorderChild(role, (_tileMap->getMapSize().height * _tileMap->getTileSize().height) - role->getPosition().y);
    }
}

void GameScene::robotLogic(){
    for (int i=0; i<_arrayRobots->count(); i++) {
        Robot * robotTest=(Robot*)_arrayRobots->objectAtIndex(i);
        //如果机器人还活着,则继续使它寻找目标
        if (robotTest->getState()!=kRoleStateKnockedOut) {
            if (robotTest->getState()==kRoleStateIdle) {
                robotTest->findTarget(_player->getPosition());
            }
        }
    }
}

#pragma - 主角操作
#pragma InputLayer Delegate
void GameScene::updatingPosition(cocos2d::CCPoint velocity){
    if (ccpLength(velocity)>0) {
        if (CCDirector::sharedDirector()->getWinSize().width==480) {
            _player->setPosition(ccpAdd(_player->getPosition(), ccpMult(velocity, 1.5)),_mapBoundingSize);

        }else{
            _player->setPosition(ccpAdd(_player->getPosition(), ccpMult(velocity, 3.0)),_mapBoundingSize);
        }
        this->setViewpointCenter(_player->getPosition());
        //设置角色方向
        if (velocity.x>0) {
            _player->setDirection(kRoleDirectionRight);
        }else if (velocity.x<0){
            _player->setDirection(kRoleDirectionLeft);
        }
        //设置玩家状态
        if (_player->getState()==kRoleStateIdle) {
            _player->move();
        }
    }else{
        if (_player->getState()==kRoleStateWalk) {
            _player->idle();
        }
    }
}

void GameScene::actionHit(){
    _player->hit();

    for (int i=1; i<_arrayRobotsToRender->count(); i++) {
        Robot * robot=(Robot *)_arrayRobotsToRender->objectAtIndex(i);
        //检测是否击中
        bool bHitEnemy=_player->m_attackBox.actual.intersectsRect(robot->m_hitBox.actual);
        int yOffset=abs(_player->getPosition().y-robot->getPosition().y);
        RoleState robotState=robot->getState();
        if (bHitEnemy&&
            yOffset<10&&
            robotState!=kRoleStateHurt&&
            robotState!=kRoleStateKnockedOut) {
            
              robot->hurt(_player->getDamage());
        }
    }
}

void GameScene::draw(void){
    CCLayer::draw();
}









