#include <LuaState.h>

lua_State* CahLua::State::L = nullptr;


CahLua::State::State()
{
}

CahLua::State::~State()
{
}

bool CahLua::State::create()
{
	L = luaL_newstate();
	if (L)
	{ 
		return true;
	}
	return false;
}

void CahLua::State::destroy()
{
	lua_close(L);
}


lua_State* CahLua::State::get(){
	return L;
}

void CahLua::pushnumber(double v){
	lua_pushnumber(CahLua::State::get(), v);
}

double CahLua::checknumber(int index){
	return luaL_checknumber(CahLua::State::get(), index);
}

void CahLua::pushstring(const char* s){
	lua_pushstring(CahLua::State::get(), s);
}

const char* CahLua::checkstring(int index){
	return luaL_checkstring(CahLua::State::get(), index);
}

void CahLua::pushusertype(void* udata, const char* tname){
	/*lua_pushlightuserdata(L, udata);
	luaL_getmetatable(L, CahLua_MetaPointer);
	lua_setmetatable(L, -2);*/
}

void* CahLua::checkusertype(int index, const char* tname){
	void* udata = lua_touserdata(CahLua::State::get(), index);
	return udata;
}