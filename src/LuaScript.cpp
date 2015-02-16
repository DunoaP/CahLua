#include <LuaScript.h>

int CahLua::Script::uid = 0;

CahLua::Script::Script(bool global, std::string filename)
{
	envName = "_G";
	this->global = global;
	error = 0;
	paramCount = 0;

	if (filename != "")
	{
		error = load(filename);
		handleError();
	}
	++uid;
}

CahLua::Script::~Script()
{
}


int CahLua::Script::load(std::string filename)
{
	FILE* fp;
	if (0 != fopen_s(&fp, filename.c_str(), "r"))
	{
		return 11;
	}

	std::vector<std::string> sLines;
	char sLine[255];
	while (fgets(sLine, 255, fp))sLines.push_back(sLine);
	fclose(fp);

	std::string max = "";
	for (int i = 0; i < (int)sLines.size(); i++){
		max = max + sLines[i];
	}

	std::string whiteList(
		"print = print,"
		"os = os,"
		"dofile = dofile,"
		"string = string"
	);

	if (!global)
	{
		envName = "Env_" + std::to_string(uid);
		std::string lua_sandbox(
			envName + " = { " + whiteList + " }  "
			"_ENV = " + envName + " "
			);
		max = lua_sandbox + max;
	}

	const char* rawScript = max.c_str();
	error = luaL_dostring(CahLua::L, rawScript);

	return error;
}


int CahLua::Script::execute()
{
	if (!global)
	{
		lua_getglobal(CahLua::L, envName.c_str());
		if (!lua_istable(CahLua::L, 1))
		{
			return 1;
		}
		error = CahLua::call(0, 0);
		handleError();

		error = call("Start");	
	}
	else {
		error = CahLua::call(0, 0);	
	}


	handleError();
	return error;
}

int CahLua::Script::call(std::string funcName)
{	
	if (funcName != "")
	{
		if (!global)
		{
			lua_getglobal(CahLua::L, envName.c_str());
			if (!lua_istable(CahLua::L, 1))
			{
				return 1;
			}
			lua_getfield(CahLua::L, -1, funcName.c_str());
		}
	}
	error = CahLua::call(paramCount, 0);	
	
	paramCount = 0;
	return error;
}

int CahLua::Script::getFunc(std::string funcName)
{
	if (!global)
	{
		lua_getglobal(CahLua::L, envName.c_str());
		if (!lua_istable(CahLua::L, 1))
		{
			return 1;
		}
		lua_getfield(CahLua::L, -1, funcName.c_str());
		return 0;
	}
	return 1;
}


int CahLua::Script::getError()
{
	return error;
}

void CahLua::Script::handleError()
{
	if (error > 0)
	{
		printf(lua_tostring(CahLua::L, -1), "\n");
		lua_pop(CahLua::L, 1);
	}
	
}

std::string CahLua::Script::getEnvName()
{
	return envName;
}


void CahLua::Script::pushnumber(double v){
	lua_pushnumber(L, v);
	paramCount++;
}

double CahLua::Script::checknumber(int index){
	return luaL_checknumber(L, index);
}

void CahLua::Script::pushstring(const char* s){
	lua_pushstring(L, s);
	paramCount++;
}

const char* CahLua::Script::checkstring(int index){
	return luaL_checkstring(L, index);
}

void CahLua::Script::pushusertype(void* udata, const char* tname){
	/*lua_pushlightuserdata(L, udata);
	luaL_getmetatable(L, CahLua_MetaPointer);
	lua_setmetatable(L, -2);*/
}

void* CahLua::Script::checkusertype(int index, const char* tname){
	void* udata = lua_touserdata(L, index);
	return udata;
}