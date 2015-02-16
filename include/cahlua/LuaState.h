#ifndef CahLuaState_h
#define CahLuaState_h

#include "lua/lua.hpp"

namespace CahLua{
	extern lua_State* L;

	lua_State* newThread(lua_State* parentState = nullptr);
	int resumeThread(lua_State* thread);
	int call(int inCount = 0, int outCount = 0);
}
#endif