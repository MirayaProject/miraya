# miraya

Spiritual successor of [twitch-chatbot-for-gosumemory](https://github.com/Sclafus/twitch-chatbot-for-gosumemory), built in C++ and Qt6.

# Features

## Commands

- [ ] !np
- [ ] !skin

# Dev stuff
This application is currently being developed with Windows 10 (Qt Creator and MinGW) and Arch Linux (VS Code and GCC).

The builds are tested with this two operating systems in mind,
but they should work with any operating system that supports Qt6.

## Branches
- `senpai` is the main branch
- `kouhai` is the beta branch
- `sensei` is the nightly branch

## Building from source

### Windows
1. Clone the repository
	```bash
	git clone https://www.github.com/MirayaProject/miraya.git
	```

2. Checkout your desired [branch](#branches)
	```bash
	cd miraya
	git checkout <branch>
	```
3. Open the CMakeLists.txt file with Qt Creator
	To do that, use the "Open Project" button.

4. Run the project

### Linux
1. Clone the repository
	```bat
	git clone https://www.github.com/MirayaProject/miraya.git
	```

2. Checkout your desired [branch](#branches) with

	```bat
	cd miraya
	git checkout <branch>
	```
3. Open the CMakeLists.txt file with Qt Creator
	To do that, use the "Open Project" button.

4. Run the project
