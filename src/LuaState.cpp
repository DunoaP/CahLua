#include <LuaState.h>

lua_State* CahLua::L = nullptr;

bool CahLua::open()
{
	if (CahLua::L){
		return false;
	}
	CahLua::L = luaL_newstate();
	if (CahLua::L){
		luaopen_base(CahLua::L);
		CahLua::MetaPointer::initialize(CahLua::L);
		return true;
	}
	return false;
}

void CahLua::close()
{
	if (CahLua::L)
	{
		lua_close(CahLua::L);
	}
}


lua_State* CahLua::newThread(lua_State* parentState)
{
	if (!parentState)
	{
		return lua_newthread(L);
	}
	return lua_newthread(parentState);
}


int CahLua::resumeThread(lua_State* thread)
{
	return lua_resume(thread, NULL, 1);
}

void CahLua::pushnumber(double v){
	lua_pushnumber(L, v);
}

double CahLua::checknumber(int index){
	return luaL_checknumber(L, index);
}

void CahLua::pushstring(const char* s){
	lua_pushstring(L, s);
}

const char* CahLua::checkstring(int index){
	return luaL_checkstring(L, index);
}

void CahLua::pushusertype(void* udata, const char* tname){
	lua_pushlightuserdata(L, udata);
	luaL_getmetatable(L, CahLua_MetaPointer);
	lua_setmetatable(L, -2);
}

void* CahLua::checkusertype(int index, const char* tname){
	void* udata = lua_touserdata(L, index);
	return udata;
}