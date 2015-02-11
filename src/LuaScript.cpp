#include <LuaScript.h>

int CahLua::Script::uid = 0;

CahLua::Script::Script(bool global, std::string filename)
{
	envName = "_G";
	this->global = global;
	error = 0;

	if (filename != "")
	{
		error = load(filename);
		handleError();
	}
	++uid;
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
		error = callFunc("Start");	
	}
	else {
		error = lua_pcall(CahLua::L, 0, 0, 0);
	}


	handleError();
	return error;
}

int CahLua::Script::callFunc(std::string funcName)
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
	return lua_pcall(CahLua::L, 0, 0, 0);
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
	}
	
}

std::string CahLua::Script::getEnvName()
{
	return envName;
}