#pragma once
#include <map>
#include <string>
extern "C"
{
#include "inc/lua.h"
#include "inc/lauxlib.h"
#include "inc/lualib.h"
};

using namespace std;

typedef string (CObject::*LPScriptFunction)(string strarg);

typedef struct _tagScript 
{
    CObject *pthis;
    LPScriptFunction pFunction;

    _tagScript(CObject *pobject, LPScriptFunction pfun)
    {
        pthis = pobject;
        pFunction = pfun;
    }
}TScript;

class CLuaScript
{
    CLuaScript(void);
    ~CLuaScript(void);
public:
    //////////////////////////////////////////////////////////////////////////
    //
    static CLuaScript *instance();

    //////////////////////////////////////////////////////////////////////////
    //
    int do_script(string script);

    //////////////////////////////////////////////////////////////////////////
    //
    int register_function(string name, TScript script);

protected:

    //////////////////////////////////////////////////////////////////////////
    //
    int init_script();

    //////////////////////////////////////////////////////////////////////////
    //
    int exit_script();

    static int antiscript(lua_State *luastate);

private:
    map<string, TScript> m_functionlist;
    lua_State * m_luastate;
};
