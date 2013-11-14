//
//  welcomlayer.h
//  testcocos2d-x
//
//  Created by wangwb on 13-10-30.
//
//

#ifndef __testcocos2d_x__welcomlayer__
#define __testcocos2d_x__welcomlayer__

#include <iostream>
#include "commonheader.h"
class welcomlayer : public CCLayer,public CCEditBoxDelegate
{
    
public:
    // 背景
    CCSprite *BG1;
    CCSprite *BG2;
    int adjustmentBG;
    
    welcomlayer();
	~welcomlayer();
    CREATE_FUNC(welcomlayer);
    virtual bool init();
    virtual void update(float delta);
//    virtual void onEnter();
    static CCScene* scene();
    void loadBackground();
    void backgrouneScroll();
    CCRenderTexture* createStroke(CCLabelTTF*lable,float size,ccColor3B cor);
    
    
    void beginGame();
    
    void addProgressBar();
    void updateProgressBar();
    
    
    //开始进入编辑
    virtual void editBoxEditingDidBegin(CCEditBox* editBox);
    //结束编辑
    virtual void editBoxEditingDidEnd(CCEditBox* editBox);
    //编辑框文本改变
    virtual void editBoxTextChanged(CCEditBox* editBox, const std::string& text);
    //当触发return后的回调函数
    virtual void editBoxReturn(CCEditBox* editBox);
    
private:
    CCProgressTimer* progress1;
    CCLabelTTF* numsTTF;
};

#endif /* defined(__testcocos2d_x__welcomlayer__) */
