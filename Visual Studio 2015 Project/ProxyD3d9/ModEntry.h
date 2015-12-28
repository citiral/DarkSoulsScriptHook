#pragma once

#include <string>
#include <map>
#include "LuaMod.h"

class ModEntry
{
public:
	ModEntry(std::string configpath);
	~ModEntry();
	std::string getValue(std::string key);
	void startMod();
	void stopMod();
	void toggleMod();
	LuaMod* getMod();
	bool isRunning() const;

private:
	void parseConfig(std::string configpath);
	void parseLine(std::string line);

	std::map<std::string, std::string> _data;
	LuaMod* _mod;
	bool _running;
};

