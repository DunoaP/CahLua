#ifndef CahLuaState_h
#define CahLuaState_h

#include "lua/lua.hpp"

namespace CahLua{
	class State
	{
	public:
		State();
		~State();

		static lua_State* get();
		static bool create();
		static void destroy();

	private:
		static lua_State* L;
	};


	void pushnumber(double);
	double checknumber(int);
	void pushstring(const char*);
	const char* checkstring(int);
	void pushusertype(void*, const char*);
	void* checkusertype(int, const char*);
}

#endif