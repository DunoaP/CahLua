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