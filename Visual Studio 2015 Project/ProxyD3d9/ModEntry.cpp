#include "ModEntry.h"

#include <fstream>

ModEntry::ModEntry(std::string configpath) :
	_running(false), _mod(nullptr)
{
	parseConfig(configpath);
}


ModEntry::~ModEntry()
{
}

std::string ModEntry::getValue(std::string key)
{
	return _data[key];
}

void ModEntry::parseConfig(std::string configpath)
{
	std::fstream configfile;
	configfile.open(configpath, std::fstream::in);
	
	while (!configfile.eof() && configfile.is_open() && configfile.good())
	{
		char string[257];
		configfile.getline(string, 256);
		parseLine(string);
	}

	configfile.close();
}

void ModEntry::parseLine(std::string line)
{
	int splitindex = line.find('=');

	if (splitindex != std::string::npos) {
		std::string key = line.substr(0, splitindex);
		std::string value = line.substr(splitindex+1, std::string::npos);

		_data[key] = value;
	}
}

void ModEntry::startMod()
{
	if (!_running) {
		if (_mod == nullptr) {
			_mod = new LuaMod("scripts/" + getValue("script"));
		}
		_running = true;
		_mod->start();
	}
}

void ModEntry::stopMod()
{
	if (_running) {
		_running = false;
		_mod->stop();
	}
}

void ModEntry::toggleMod()
{
	if (_running)
		stopMod();
	else
		startMod();
}

bool ModEntry::isRunning() const
{
	return _running;
}

LuaMod* ModEntry::getMod()
{
	return _mod;
}