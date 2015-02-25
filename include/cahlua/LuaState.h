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
}
#endif