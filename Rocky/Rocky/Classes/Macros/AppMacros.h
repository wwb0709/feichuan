//
//  AppMacros.h
//  Rocky
//
//  Created by Tuyuer on 13-2-4.
//
//

#ifndef Rocky_AppMacros_h
#define Rocky_AppMacros_h
#include "cocos2d.h"

typedef struct _ColliderBox{
    cocos2d::CCRect actual;
    cocos2d::CCRect original;
}ColliderBox;

//static bool CCRectContainsPoint(cocos2d::CCRect rect,cocos2d::CCPoint ptTest){
//    bool bInPoint=false;
//    if (rect.origin.x<ptTest.x && ptTest.x<rect.origin.x+rect.size.width) {
//        if (rect.origin.y<ptTest.y && ptTest.y<rect.origin.y+rect.size.height) {
//            bInPoint=true;
//        }
//    }
//    return bInPoint;
//}
//
//static bool CCRectIntersectsRect(cocos2d::CCRect rect1,cocos2d::CCRect rect2){
//
//    cocos2d::CCPoint pt1=rect2.origin;
//    cocos2d::CCPoint pt2=cocos2d::CCPointMake(rect2.origin.x+rect2.size.width, rect2.origin.y);
//    cocos2d::CCPoint pt3=cocos2d::CCPointMake(rect2.origin.x+rect2.size.width, rect2.origin.y+rect2.size.height);
//    cocos2d::CCPoint pt4=cocos2d::CCPointMake(rect2.origin.x, rect2.origin.y+rect2.size.height);
//    
//    if (CCRectContainsPoint(rect1, pt1)) {
//        return true;
//    }
//    if (CCRectContainsPoint(rect1, pt2)) {
//        return true;
//    }
//    if (CCRectContainsPoint(rect1, pt3)) {
//        return true;
//    }
//    if (CCRectContainsPoint(rect1, pt4)) {
//        return true;
//    }
//    return false;
//}


#endif
