#include "LuaState.h"

lua_State* CahLua::L = nullptr;

bool CahLua::init()
{
	CahLua::L = luaL_newstate();
	if (CahLua::L){

		CahLua::MetaPointer::initialize(CahLua::L);
		return true;
	}
	else {
		return false;
	}
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
}

void* CahLua::checkusertype(int index, const char* tname){
	void* udata = lua_touserdata(L, index);
	return udata;
}