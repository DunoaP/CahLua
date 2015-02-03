#include <cahlua/CahLua.hpp>

#include "foo.h"



int main(){
	bool b = CahLua::open();
	if (b != true)
	{
		return b;
	}
	Foo f;


	CahLua::Script script(false, "class1.lua");

	f.setLocal(script.getEnvName(), "foo");
	script.execute();

	CahLua::Script script2(false, "class2.lua");
	script2.execute();	//We want to see an error here about foo being undefined

	CahLua::close();

	system("pause");
	return 0;
}