#ifndef LuaState_h
#define LuaState_h

#include <lua.hpp>
#include "LuaMetaPointer.h"

namespace CahLua{
	extern lua_State* L;

	bool init();
	void pushnumber(double);
	double checknumber(int);
	void pushstring(const char*);
	const char* checkstring(int);
	void pushusertype(void*, const char*);
	void* checkusertype(int, const char*);
}
#endif