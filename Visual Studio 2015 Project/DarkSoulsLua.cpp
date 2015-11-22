// DarkSoulsLua.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "DarkSouls.h"
#include "DarkSouls2.h"
#include "Script.h"

int main()
{
	while (true) {
		std::cout << "press 1 for dark souls, 2 for dark souls 2" << std::endl;
		char selection = getchar();
		Game* game = nullptr;

		if (selection == '1') {
			game = new DarkSouls();
		} if (selection == '2') {
			game = new DarkSouls2();
			game->sendKeyDown(VK_SPACE); 
		}
		else {
			return 0;
		}

		new Script(game, "scripts\\test.lua");
		//game->sendKeyDown(0x44);

		getchar();
	}
    return 0;
}

