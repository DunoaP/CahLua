#ifndef CahLuaScript_h
#define CahLuaScript_h

#include "lua/lua.hpp"
#include "LuaState.h"

#include <vector>
#include <string>

namespace CahLua
{
	class Script
	{
	public:
		Script(bool global = true, std::string filename = "");
		~Script();

		int load(std::string);


		int execute();
		int getFunc(std::string funcName);
		int call(std::string = "");

		int getError();
		std::string getEnvName();

		

		void pushnumber(double);
		double checknumber(int);
		void pushstring(const char*);
		const char* checkstring(int);
		void pushusertype(void*, const char*);
		void* checkusertype(int, const char*);

	private:
		static int uid;

		int error;
		bool global;

		std::string envName;

		void handleError();
		unsigned short paramCount;

	};
}
#endif