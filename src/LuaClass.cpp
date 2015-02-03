#include <LuaClass.h>

std::map<std::string, CahLua::LuaClass> CahLua::LuaClass::classList;

CahLua::LuaClass::LuaClass(std::string className)
{
	this->className = className;
}

CahLua::LuaClass::LuaClass(){

}
CahLua::LuaClass::~LuaClass(){

}

CahLua::LuaClass& CahLua::LuaClass::createClass(std::string classname)
{
	classList[classname] = LuaClass(classname);
	return classList[classname];
}

CahLua::LuaClass& CahLua::LuaClass::addConstructor(void* func)
{
	funcList["new"] = func;
	return classList[className];
}

CahLua::LuaClass& CahLua::LuaClass::addDestructor(void* func)
{
	funcList["destroy"] = func;
	return classList[className];
}
CahLua::LuaClass& CahLua::LuaClass::addFunc(std::string funcName, void* func)
{
	funcList[funcName] = func;
	return classList[className];
}

void CahLua::LuaClass::bind()
{

	luaL_Reg flist[32];

	int i = 0;
	auto it = funcList.begin();
	while (it != funcList.end())
	{
		flist[i] = { (*it).first.c_str(), (lua_CFunction)(*it).second };
		++i;
		++it;
	}
	for (i; i < 32; ++i)
	{
		flist[i] = { NULL, NULL };
	}	


	lua_rawgeti(CahLua::L, LUA_REGISTRYINDEX, LUA_RIDX_GLOBALS);
	lua_newtable(CahLua::L);
	luaL_setfuncs(CahLua::L, flist, 0);
	lua_setglobal(CahLua::L, className.c_str());
}