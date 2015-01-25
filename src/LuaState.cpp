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
		//CahLua::MetaPointer::initialize(CahLua::L);
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

void CahLua::pushnumber(double v){
	lua_pushnumber(L, v);
}

double CahLua::checknumber(int index){
	return luaL_checknumber(L, index);
}

void CahLua::pushboolean(bool v){
	lua_pushboolean(L, v);
}

double CahLua::checkboolean(int index){
	return lua_toboolean(L, index);
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