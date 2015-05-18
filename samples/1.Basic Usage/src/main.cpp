#include <cahlua/CahLua.hpp>

#include "foo.h"



int main(){
	int b = CahLua::open();

	Foo f;
	f.testString = "hello world";
	f.testNumber = 123;
	f.testBool = true;
	f.setGlobal("foo");

	if (luaL_loadfile(CahLua::State::get(), "basic_usage.lua") || lua_pcall(CahLua::State::get(), 0, 0, 0))
	{
		lua_tostring(CahLua::State::get(), -1);
	}

	CahLua::close();

	system("pause");
	return 0;
}