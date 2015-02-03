#include "foo.h"

Foo::Foo(lua_State* L) : CahLua::MetaPointer(L)
{

}

Foo::~Foo()
{

}

int Foo::get(lua_State* L)
{
	std::string key = std::string(CahLua::checkstring(2));

	if (key.find("string") == 0)
		CahLua::pushstring(testString.c_str());
	else if (key.find("number") == 0)
		CahLua::pushnumber(testNumber);
	else 
		return 0;

	return 1;
}

int Foo::set(lua_State* L)
{
	std::string key = std::string(CahLua::checkstring(2));

	if (key.find("string") == 0)
		testString = lua_tostring(L, 3);
	else if (key.find("number") == 0)
		testNumber = lua_tonumber(L, 3);

	return 0;
}