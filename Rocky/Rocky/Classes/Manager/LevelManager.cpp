//
//  LevelManager.cpp
//  Rocky
//
//  Created by Tuyuer on 13-2-3.
//
//

#include "LevelManager.h"
USING_NS_CC;

LevelManager * LevelManager::create(){
    LevelManager * lManager=new LevelManager();
    lManager->autorelease();
    return lManager;
}