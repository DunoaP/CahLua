#include <cahlua/CahLua.hpp>

#include "foo.h"



int main(){
	bool b = CahLua::open();
	if (b != true)
	{
		return b;
	}
	//Foo f(CahLua::L);
	//f.testString = "hello world";
	//f.testNumber = 123;


	CahLua::Script script(false, "class1.lua");

	//f.setLocal(script.getBoundState(), "foo");
	script.execute();

	//CahLua::Script script2(false, "class2.lua");
	//script2.execute();	//We want to see an error here about foo being undefined

	CahLua::close();

	system("pause");
	return 0;
}