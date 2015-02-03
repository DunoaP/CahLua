#include "foo.h"

Foo::Foo()
{

}

Foo::~Foo()
{

}


int Foo::bar(lua_State* L)
{
	printf("Hello universe!");
	return 1;
}