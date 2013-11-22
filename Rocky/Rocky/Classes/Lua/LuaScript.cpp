#include "StdAfx.h"
#include "LuaScript.h"

#pragma comment(lib, "lua51.lib")

int operator<(string name1, string name2)
{
    return strcmp(name1.c_str(), name2.c_str());
}

CLuaScript::CLuaScript(void)
{
    m_luastate = NULL;
    init_script();
}

CLuaScript::~CLuaScript(void)
{
    exit_script();
}

CLuaScript *CLuaScript::instance()
{
    static CLuaScript g_pthis;
    return &g_pthis;
}

int CLuaScript::antiscript(lua_State *luastate)
{
    if (instance() == NULL)
    {
        return 0;
    }

    /* get number of arguments */
    int n = lua_gettop(luastate);

    if (n != 2)
    {
        lua_pushstring(luastate, "Incorrect argument to 'luascript'");
        lua_error(luastate);
        return 0;
    }

    if (!lua_isstring(luastate, 1))
    {
        lua_pushstring(luastate, "Incorrect argument to 'luascript'");
        lua_error(luastate);
        return 0;
    }

    if (!lua_isstring(luastate, 2))
    {
        lua_pushstring(luastate, "Incorrect argument to 'luascript'");
        lua_error(luastate);
        return 0;
    }
    
    const char *pfunction = lua_tostring(luastate, 1);
    const char *pargs = lua_tostring(luastate, 2);


    map<string, TScript>::iterator iter = instance()->m_functionlist.find(pfunction);

    if (iter != instance()->m_functionlist.end())
    {
        TScript script = iter->second;

        (script.pthis->*script.pFunction)(string(pargs));
    }
    
   

    return 0;
}

int CLuaScript::init_script()
{
    /* initialize Lua */

    if (m_luastate != NULL)
    {
        lua_close(m_luastate);
        m_luastate = NULL;
    }

    m_luastate = lua_open();



    /* load Lua base libraries */

    luaL_openlibs(m_luastate);



    /* register our function */

    lua_register(m_luastate, "antiscript", antiscript);



    /* run the script */

    //luaL_dofile(L, "average.lua");

    return 0;
}

int CLuaScript::exit_script()
{
    if (m_luastate != NULL)
    {
        lua_close(m_luastate);
        m_luastate = NULL;
    }

    return 0;
}

int CLuaScript::register_function(string name, TScript script)
{
    map<string, TScript>::iterator iter = m_functionlist.find(name);

    if (iter != m_functionlist.end())
    {
        return -1;
    }

    m_functionlist.insert(pair<string, TScript>(name, script));

    return 0;
}

int CLuaScript::do_script(string script)
{
    if (m_luastate == NULL)
    {
        return -1;
    }

    int res = luaL_dofile(m_luastate, script.c_str());

    TRACE("res:%d\n", res);

    return 0;
}