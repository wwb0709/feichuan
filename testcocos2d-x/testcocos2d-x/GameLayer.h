//
//  GameLayer.h
//  testcocos2d-x
//
//  Created by wangwb on 13-10-31.
//
//

#ifndef __testcocos2d_x__GameLayer__
#define __testcocos2d_x__GameLayer__

#include <iostream>
#include "commonheader.h"
#include "CCFoePlane.h"
#include "CCProps.h"
class GameLayer :public CCLayer
{
    GameLayer();
    ~GameLayer();

    virtual bool init();
public:
    CREATE_FUNC(GameLayer);
    
    void menuCloseCallback(CCObject* pSender);

    void myMenuCallback(CCObject* pSender);

    void secondMenuCallback(CCObject* pSender);
    
    // 造大飞机
    CCFoePlane* makeBigFoePlane();
    // 造中飞机
    CCFoePlane* makeMediumFoePlane();
    // 造小飞机
    CCFoePlane* makeSmallFoePlane();
    
    
    // 制作道具
    void makeProps();
    
    // 没接住道具, 出了底屏
    void resetProps();
    // 移动敌机
    void moveFoePlane();
    
    
    
    virtual void update(float delta);
    
    // 触摸事件
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    virtual void registerWithTouchDispatcher();
    
    //触摸点
    CCPoint boundLayerPos(CCPoint newPos);
    void panForTranslation(CCPoint translation);
    
    
    
    // 玩家飞机加载
    void loadPlayer();
    
    // 子弹操作
    void madeBullet();
    void firingBullets();
    void resetBullet();
    
    // 子弹持续时间
    void bulletTimingFn();
    
    

    
    // 载入背景
    void loadBackground();
    // 背景滚动
    void backgroundScroll();
    
    
    // 初始化数据
    void initData();
    
    
    // 添加打击效果
    void fowPlaneHitAnimation(CCFoePlane* foePlane);
    
    // 爆炸动画
    void fowPlaneBlowupAnimation(CCFoePlane*foePlane);
    
    // 飞机爆炸
    void playerBlowupAnimation();
    
    void playerBlowupEnd(CCObject* sender);
    
    void blowupEnd(CCObject* sender);
    // 游戏结束
    void gameOver();
    
    // 重新开始游戏
    void restartGame();
    
    // 碰撞检测
    void collisionDetection();
    
    
    
    // 添加飞机
    void addFoePlane();
    
    // 退出应用
    void logout();
    
//    // 调整难度
//    void changLevel();
    
    // 难度间隔时间
    void levelTimingFn();
    
private:
    
    bool changedirct;//是否改变方向
    // 玩家飞机
    CCSprite *player;
    
    
    // 子弹
    CCSprite *bullet;
    // 子弹数量
    int bulletSum;
    // 子弹样式
    bool isBigBullet;
    bool isChangeBullet;
    // 子弹速度
    int bulletSpeed;
    // 特殊子弹时间
    int bulletTiming;
    
    
    
    // 敌方飞机
    CC_SYNTHESIZE_RETAIN(CCArray*, __foePlanes, FoePlanes);
    
    // 添加飞机时机
    int bigPlan;
    int smallPlan;
    int mediumPlan;
    
    
    // 背景
    CCSprite *BG1;
    CCSprite *BG2;
    int adjustmentBG;
    
    // 分数
    CCLabelTTF *scoreLabel;
    int score;
    
    bool isGameOver;
    
    
    
    
    // 道具
    CC_SYNTHESIZE_RETAIN(CCProps*,__prop,Prop);
    // 添加道具时机
    int props;
    // 是否存在
    bool isVisible;
    
    
    //增量
    int addplane;//增加战机数量
    int addspeed;//增加速度
    
    int jgtime;//增加难度的间隔时间
    

};


#endif /* defined(__testcocos2d_x__GameLayer__) */
