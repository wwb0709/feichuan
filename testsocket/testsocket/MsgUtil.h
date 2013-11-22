//
//  MsgUtil.h
//  testsocket
//
//  Created by wangwb on 13-11-21.
//
//

#ifndef __testsocket__MsgUtil__
#define __testsocket__MsgUtil__
#include <iostream>
using namespace std;

struct User{
    int m_groupId;
    string m_groupName;
    int m_mask;
    int m_parentId;
};
class MsgUtil
{
public:
	static void paraseJson( string json);
	static string createJson();
};

#endif /* defined(__testsocket__MsgUtil__) */
