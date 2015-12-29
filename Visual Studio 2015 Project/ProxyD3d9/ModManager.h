#pragma once

#include <vector>
#include <functional>
#include "ModEntry.h"
#include "LuaMod.h"
#include <map>

struct ModMenuEntry {
	std::string text;
	std::function<void()> function;
};

struct ConsoleEntry {
	std::string text;
	float timeout;
};

class ModManager
{
public:
	ModManager();
	~ModManager();

	void update(float dt);

	void addConsoleEntry(std::string text, float timeout = 5);
	void clearConsoleEntries();

private:
	void handleInput();
	void drawMenu();
	void updateMods(float dt);

	void toggleMod(int modindex, int entryindex);
	void runSelectedItem();
	void refreshContent();

	bool _menuEnabled;
	int _selectedItem;
	std::vector<ModMenuEntry> _menuItems;
	std::vector<ModEntry> _modEntries;
	std::vector<ConsoleEntry> _consoleEntries;
};

