# DarkSoulsScriptHook
LUA Scripthook for Dark Souls 1 and 2 (and hopefully 3)
This program enables the user to run arbitrary lua scripts in a seperate process, while having access to the memory of Dark Souls. 

# What is possible
Right now, not much. You can access basic variables and the inventory of a running Dark Souls 2 process. I was originally making this to automate generating the images for fashion-souls.com . After that is done, I will branch the scripthook out to Dark Souls 1, where I will try to support as much as possible.

# Usage
Currently, the program needs to be started seperately and runs a hardcoded script. In the final version, all scripts in a script folder will be iterated and shown in an overlay in the game, allowing the user to select a script to run.

# How
The script is run through a seperate process, allowing the script to run simultaniously with dark souls.

A small XInput proxy dll is responsible for all logic that needs to run inside the dark souls process. As of now it doesn't do anything, but later it will be responsible both for emulating input and as being a callback for code injection.

Memory access is made possible simply by hooking into the dark souls process, and exposing a set of functions to lua that allows the script to read/write to the memory of dark souls. A small library is written on top of this in C++, which allows for easier access to certain Dark Souls variables. This library is extended in lua, so scripts almost never need to worry about exact memory locations. In short, the more high-level library functions are written in Lua, and the low-level 'hacky' library functions are made in C++.

# Todo
(I only list the important stuff / shit I want done in the near future, since otherwise the list would be endless)

General:
Set up IPC between the lua process and the dark souls process (through the proxy dll) to emulate key-input from the script
Set up more lua libraries to allow for taking screenshots,..

DS2:
Find a way to get the size of the inventory :)

DS1:
Everything
