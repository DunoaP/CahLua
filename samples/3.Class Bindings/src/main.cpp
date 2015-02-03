#include <cahlua/CahLua.hpp>

#include "foo.h"



int main(){
	bool b = CahLua::open();
	if (b != true)
	{
		return b;
	}

	CahLua::LuaClass::createClass("foo")
		.addFunc("Bar", Foo::bar)
		.bind();

	CahLua::Script script(true, "sample_script.lua");

	CahLua::close();

	system("pause");
	return 0;
}