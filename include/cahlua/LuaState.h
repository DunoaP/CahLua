#ifndef CahLuaState_h
#define CahLuaState_h

#include "lua/lua.hpp"
#include "LuaMetaPointer.h"

namespace CahLua{
	extern lua_State* L;

	bool open();
	void close();

	lua_State* newThread(lua_State* parentState = nullptr);
	int resumeThread(lua_State* thread);

	void pushnumber(double);
	double checknumber(int);
	void pushstring(const char*);
	const char* checkstring(int);
	void pushusertype(void*, const char*);
	void* checkusertype(int, const char*);
}
#endif