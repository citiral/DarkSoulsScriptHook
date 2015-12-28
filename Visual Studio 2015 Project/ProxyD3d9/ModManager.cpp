#include "ModManager.h"
#include "Drawing.h"
#include "Input.h"
#include "MessageHook.h"
#include <sstream>

ModManager::ModManager() :
	_menuEnabled(false), _selectedItem(0)
{
	refreshContent();
}


ModManager::~ModManager()
{

}

void ModManager::update(float dt)
{
	handleInput();
	if (_menuEnabled) {
		drawMenu();
	}
	updateMods(dt);
}

void ModManager::handleInput()
{
	if (input::getKeyPressed(VK_HOME)) {
		_menuEnabled = !_menuEnabled;
	}

	if (_menuEnabled) {
		if (input::getKeyPressed(VK_NUMPAD8))
			_selectedItem--;
		if (input::getKeyPressed(VK_NUMPAD2))
			_selectedItem++;

		if (_selectedItem < 0)
			_selectedItem = 0;
		else if (_selectedItem >= _menuItems.size())
			_selectedItem = _menuItems.size() - 1;

		if (input::getKeyPressed(VK_NUMPAD5))
			runSelectedItem();
	}
}

void ModManager::drawMenu()
{
	int index = 0;
	for (auto iter = _menuItems.begin(); iter != _menuItems.end(); iter++) {
		if (index == _selectedItem)
			drawing::drawText(("> " + iter->text).c_str(), 10, index * 30 + 10);
		else
			drawing::drawText((iter->text).c_str(), 10, index * 30 + 10);
		index++;
	}
	std::stringstream str;

	drawing::drawText(str.str().c_str(), 10, index * 30 + 10);

}

void ModManager::updateMods(float dt)
{
	for (auto iter = _modEntries.begin(); iter != _modEntries.end(); iter++) {
		if (iter->isRunning()) {
			iter->getMod()->update(dt);
		}
	}
}

void ModManager::runSelectedItem()
{
	_menuItems[_selectedItem].function();
}

void ModManager::refreshContent()
{
	//clear the old content
	_modEntries.clear();
	_menuItems.clear();

	//insert the static content
	_menuItems.push_back({ "refresh", std::bind(std::mem_fn(&ModManager::refreshContent), this) });
	
	//and then insert the mods
	WIN32_FIND_DATA fdata;
	HANDLE iterHandle =FindFirstFile("scripts/*", &fdata);

	int index = 0;

	do {
		std::string filename(fdata.cFileName);
		int extension = filename.rfind('.');

		if (extension != std::string::npos) {
			if (filename.substr(extension, std::string::npos).compare(".conf") == 0) {
				ModEntry mod("scripts/" + filename);
				_modEntries.push_back(mod);
				_menuItems.push_back({ "[disabled] " + mod.getValue("name"), std::bind(std::mem_fn(&ModManager::toggleMod), this, _modEntries.size() - 1, _menuItems.size()) });
				index++;
			}
		}
	} while (FindNextFile(iterHandle, &fdata));
}

void ModManager::toggleMod(int modindex, int entryindex)
{
	_modEntries[modindex].toggleMod();
	if (_modEntries[modindex].isRunning()) {
		_menuItems[entryindex].text = "[enabled] " + _modEntries[modindex].getValue("name");
	}
	else {
		_menuItems[entryindex].text = "[disabled] " + _modEntries[modindex].getValue("name");
	}
}