#include <cahlua/CahLua.hpp>





int main(){
	bool b = CahLua::open();

	if (b){

		return 1;
	}



	CahLua::close();

	system("pause");
	return 0;
}