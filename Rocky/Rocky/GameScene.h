//
//  GameScene.h
//  Rocky
//
//  Created by Tuyuer on 13-2-3.
//
//

#ifndef __Rocky__GameScene__
#define __Rocky__GameScene__

#include <iostream>
#include "cocos2d.h"
#include "InputLayer.h"

class Player;
class Robot;
class GameScene:public cocos2d::CCLayer,
public InputLayerDelegate
{
private:
    cocos2d::CCArray * _arrayRobots;
    cocos2d::CCArray * _arrayRobotsToRemove;
    cocos2d::CCArray * _arrayRobotsToAdd;
    cocos2d::CCArray * _arrayRobotsToRender;
    
    
    cocos2d::CCSpriteBatchNode * _batchNode;
    Player * _player;
    InputLayer * _inputLayer;
    cocos2d::CCTMXTiledMap * _tileMap;
    cocos2d::CCSize _mapBoundingSize;
    cocos2d::CCLayer * _gameLayer;
private:
    void initUI();
    void initRobots();
    void setViewpointCenter(cocos2d::CCPoint pTest);
    void reOrderRoles();
    void robotLogic();
    void retry();
public:
    GameScene();
    ~GameScene();
    
    virtual void onEnter();
    virtual void update(float fDelta);
    virtual void onEnterTransitionDidFinish();
    virtual void draw(void);
    //input delegate
    virtual void updatingPosition(cocos2d::CCPoint velocity);
    virtual void actionHit();
    
    CREATE_FUNC(GameScene);
    static cocos2d::CCScene * scene();
};

#endif /* defined(__Rocky__GameScene__) */
