#include <cahlua/CahLua.hpp>

#include "foo.h"



int main(){
	int b = CahLua::open();

	Foo f(CahLua::L);
	f.testString = "hello world";
	f.testNumber = 123;
	f.testBool = true;
	f.setGlobal("foo");

	if (luaL_loadfile(CahLua::L, "basic_usage.lua") || lua_pcall(CahLua::L, 0, 0, 0))
	{
		lua_tostring(CahLua::L, -1);
	}

	CahLua::close();

	system("pause");
	return 0;
}