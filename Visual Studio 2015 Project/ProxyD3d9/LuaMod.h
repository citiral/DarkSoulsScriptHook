#pragma once
#include <string>

extern "C" {
#include <lualib.h>
}

class LuaMod
{
public:
	LuaMod(std::string scriptname);
	~LuaMod();

	void start();
	void stop();
	void update(float dt);

private:
	void addBindings();

	std::string _scriptname;
	lua_State* _l;
	bool _running;
};

