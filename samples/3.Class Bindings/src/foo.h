#ifndef FOO_H
#define FOO_H

#include <cahlua/CahLua.hpp>

class Foo {
public:
	Foo();
	~Foo();

	static int bar(lua_State* L);

private:
};
#endif