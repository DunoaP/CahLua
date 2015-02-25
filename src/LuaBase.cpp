#include <LuaBase.h>


bool CahLua::open()
{
	if (CahLua::State::get()){
		return false;
	}
	CahLua::State::create();
	if (CahLua::State::get()){
		luaopen_base(CahLua::State::get());
		return true;
	}
	return false;
}

void CahLua::close()
{
	CahLua::State::destroy();
}

