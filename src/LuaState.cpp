#include <LuaState.h>

lua_State* CahLua::L = nullptr;


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

int CahLua::call(int inCount, int outCount)
{
	lua_pcall(CahLua::L, inCount, outCount, 0);
}