#include <LuaBase.h>


bool CahLua::open()
{
	if (CahLua::L){
		return false;
	}
	CahLua::L = luaL_newstate();
	if (CahLua::L){
		luaopen_base(CahLua::L);
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