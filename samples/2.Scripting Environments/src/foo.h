#ifndef FOO_H
#define FOO_H

#include <cahlua/CahLua.hpp>

class Foo : public CahLua::MetaPointer{
public:
	Foo();
	~Foo();

	int get(lua_State* L);
	int set(lua_State* L);


	std::string testString;
	double testNumber;

private:
};
#endif