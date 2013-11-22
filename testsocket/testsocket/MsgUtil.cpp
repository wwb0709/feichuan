//
//  MsgUtil.cpp
//  testsocket
//
//  Created by wangwb on 13-11-21.
//
//

#include "MsgUtil.h"
#include "json.h"
using namespace Json;

void MsgUtil::paraseJson(string json)
{
    const char * jsongroupinfo="[{\"groupId\" :946838524,\"groupname\" :\"bababa\", \"mask\":1,\"parentid\":946755072},{\"groupId\" :946838524,\"groupname\" :\"bababa0000000汉字\", \"mask\":1,\"parentid\":946755072}]";
    
    Json::Reader reader;
    Json::Value json_object;
    if (!reader.parse(jsongroupinfo, json_object))
        return;
    User user;
    vector<User> m_groupInfo;
    for(int i = 0; i < json_object.size(); i ++)
    {
        Json::Value &current = json_object[i];
        user.m_groupId = current["groupId"].asInt();
        user.m_groupName = current["groupname"].asString();
        user.m_mask = current["mask"].asInt();
        user.m_parentId = current["parentid"].asInt();
        m_groupInfo.push_back(user);
    }
    
    
    
    vector<User>::iterator iter;
    for (iter=m_groupInfo.begin();iter!=m_groupInfo.end();iter++)
    {
         User user=*iter;
        cout<<"--groupname:"+user.m_groupName<<endl;
        
    }
    cout<<endl;
//    Reader reader;
//    Value value;
//    if (reader.parse(json, value)) {
//        const Json::Value arrayObj = value["array"];
//        for (size_t i=0; i<arrayObj.size(); i++) {
//            int id = arrayObj[i]["age"].asInt();
//            string name = arrayObj[i]["name"].asString();
//            cout << id << " " << name << endl;
//        }
//    } else {
//        cout << "parse error" << endl;
//    }

}
string MsgUtil::createJson()
{
    FastWriter writer;
    
    Value allperson;
    Value arrp;
    Value person;
    person["name"] = "hello world";
    person["age"] = 100;
    arrp.append(person);
    
    Value person2;
    person2["name"] = "hello";
    person2["age"] = 102;
    arrp.append(person2);
    
    allperson["array"] = arrp;
    
    
    string json_file = writer.write(allperson);
    
    cout << " json_file " << json_file << endl;
    
    return json_file;
}