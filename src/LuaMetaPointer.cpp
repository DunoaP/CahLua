#include <LuaMetaPointer.h>

//-----------------------------------------------------------------------------
#define lua_checkmpointer(L)    (MetaPointer*)luaL_checkudata(L, 1, CahLua_MetaPointer)
//-----------------------------------------------------------------------------
lua_State* CahLua::MetaPointer::m_lua = NULL;
std::map<CahLua::MetaPointer*, std::string> CahLua::MetaPointer::m_pointers;
const luaL_Reg CahLua::MetaPointer::m_lmembers[] = { { NULL, NULL } };
const luaL_Reg CahLua::MetaPointer::m_lfunctions[] =
{
	{ "__index", CahLua::MetaPointer::__index },
	{ "__gc", CahLua::MetaPointer::__destroy },
	{ "__newindex", CahLua::MetaPointer::__newindex },
	{ NULL, NULL }
};
//-----------------------------------------------------------------------------

CahLua::MetaPointer::MetaPointer() : m_name("")
{
	//-- Make sure we have created the metatable
	initialize(CahLua::State::get());

	//-- Add this pointer as of kind LUA_METAPOINTER metatable. This bit of code
	//   might not be necessary here. (To be removed)
	lua_pushlightuserdata(m_lua, this);
	luaL_getmetatable(m_lua, CahLua_MetaPointer);
	lua_setmetatable(m_lua, -2);

	//-- Add myself to the map of all metapointers
	m_pointers[this] = m_name;
}
//-----------------------------------------------------------------------------

CahLua::MetaPointer::~MetaPointer()
{
	//-- Remove myself from the map of metapointers
	std::map<MetaPointer*, std::string>::iterator found = m_pointers.find(this);

	if (found != m_pointers.end())
		m_pointers.erase(found);
}
//-----------------------------------------------------------------------------

int CahLua::MetaPointer::__index(lua_State* L)
{
	//-- Obtain the object that called us and call its get method.
	//   Since get and set are pure virtual, all inherited classes of LMetaPointer
	//   must implement it, and, upon the call from here, the correct 'get' method
	//   will be called.
	MetaPointer* p = lua_checkmpointer(L);
	return p->get(L);
}
//-----------------------------------------------------------------------------

int CahLua::MetaPointer::__newindex(lua_State* L)
{
	//-- Obtain the object that called us and call its set method
	//   Since get and set are pure virtual, all inherited classes of LMetaPointer
	//   must implement it, and, upon the call from here, the correct 'get' method
	//   will be called.
	MetaPointer* p = lua_checkmpointer(L);
	return p->set(L);
}
//-----------------------------------------------------------------------------

int CahLua::MetaPointer::__destroy(lua_State* L)
{
	//-- Obtain the object that called us and call its set method
	//   Since get and set are pure virtual, all inherited classes of LMetaPointer
	//   must implement it, and, upon the call from here, the correct 'get' method
	//   will be called.
	MetaPointer* p = lua_checkmpointer(L);
	if (p != nullptr)
	{
		//delete p;
		return 1;
	}
	return 0;
}
//-----------------------------------------------------------------------------




void CahLua::MetaPointer::initialize(lua_State* L)
{
	//-- Only create the metatable the first time and instance of LMetaPointer is created
	if (!m_lua)
	{
		m_lua = L;

		luaL_newmetatable(m_lua, CahLua_MetaPointer);
		luaL_setfuncs(L, m_lfunctions, 0);
		luaL_newlib(L, m_lmembers);
	}
}
//-----------------------------------------------------------------------------

void CahLua::MetaPointer::setGlobal(std::string n)
{
	//-- Make myself (this) a global variable in LUA with name given by 'n'
	std::map<MetaPointer*, std::string>::iterator found = m_pointers.find(this);

	if (found != m_pointers.end())
	{
		m_name = n;
		found->second = m_name;

		lua_pushlightuserdata(m_lua, this);
		luaL_getmetatable(m_lua, CahLua_MetaPointer);
		lua_setmetatable(m_lua, -2);
		lua_setglobal(m_lua, m_name.c_str());
	}
}
//-----------------------------------------------------------------------------

void CahLua::MetaPointer::setLocal(std::string envName, std::string n)
{
	//-- Make myself (this) a global variable in LUA with name given by 'n'
	std::map<MetaPointer*, std::string>::iterator found = m_pointers.find(this);

	if (found != m_pointers.end())
	{
		m_name = n;
		found->second = m_name;

		lua_pushlightuserdata(m_lua, this);
		luaL_getmetatable(m_lua, CahLua_MetaPointer);
		lua_setmetatable(m_lua, -2);
		lua_getglobal(m_lua, envName.c_str());
		if (!lua_istable(m_lua, 1))
		{
			return;
		}
		lua_setfield(m_lua, -1, n.c_str());
	}
}
//-----------------------------------------------------------------------------

CahLua::MetaPointer* CahLua::MetaPointer::operator [](std::string n)
{
	//-- Simply for completeness, allow all metapointer access all other by their
	//   name. (Notice though that since names are only assigned to instances made
	//   global, this operator will only work properly when searching for a pointer
	//   made global. All other pointers have an empty name.
	std::map<MetaPointer*, std::string>::iterator iter = m_pointers.begin();

	int i = 1;
	while (iter != m_pointers.end())
	{
		if (iter->second == n)
		{
			return iter->first;
		}

		iter = std::next(m_pointers.begin(), i);
		++i;
	}

	return NULL;
}