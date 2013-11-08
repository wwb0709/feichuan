//
//  UserData.h
//  testcocos2d-x
//
//  存放用户数据的类
//  Created by wangwb on 13-11-7.
//
//

#ifndef __testcocos2d_x__UserData__
#define __testcocos2d_x__UserData__

#include "commonheader.h"



class UserData : public CCObject
{
protected:
    UserData();//构造函数
    ~UserData();//析构函数
    bool init();//初始化函数
    
public:
    static  UserData* sharedUserData();
    
    void flush();//把内存中的数据同步到文件中
    
    void purge();//内存不足时调用释放
    
    void alertScore(int delta);//修改成绩
    
    //打的成绩
    CC_SYNTHESIZE(int, _score, Score);
    
    //名字
    CC_SYNTHESIZE(std::string, _name, Name);
    
    //音效的音量
    CC_SYNTHESIZE(float, _soundVolume, SoundVolume);
    
    //背景音乐的音量
    CC_SYNTHESIZE(float, _musicVolume, MusicVolume);
    
    



};


#endif /* defined(__testcocos2d_x__UserData__) */
