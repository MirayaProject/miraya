![image](https://github.com/MirayaProject/miraya/assets/31241607/9992b3d7-ff3e-4479-af21-655359705bff)

Spiritual successor of [twitch-chatbot-for-gosumemory](https://github.com/Sclafus/twitch-chatbot-for-gosumemory), built in C++ and Qt6.

# First Time?
- [Click here](https://github.com/MirayaProject/miraya/releases/latest) to get the latest version of miraya
- Scroll down to "Assets", and download the zip file that corresponds to your operating system
- Extract the downloaded zip
- Open the executable for miraya & enjoy! 

# Features
We have _a couple_
## Simple static commands
On Miraya             |  On Twitch
:-------------------------:|:-------------------------:
![image](https://github.com/MirayaProject/miraya/assets/31241607/87391eea-1108-4562-84aa-370b1393b060)  |  ![image](https://github.com/MirayaProject/miraya/assets/31241607/ced8e4f1-51a8-444e-a57d-3e0a671ca7f9)


To add a command, just use the "Add Command" button, type the command and the response you'd like to have.

## !np
When connected correctly with gosumemory, users can do a !np to obtain the current map with the corresponding URL.
> **Note**
> This feature works only when gosumemory is connected (press "Start")

![image](https://github.com/MirayaProject/miraya/assets/31241607/5efe55a2-840a-4120-a72b-46ee00aadcbc)


## !skin
When connected correctly with gosumemory, users can ask for the current skin. If added via the dedicated menu "Responses>Skins", users can also receive a download URL for it.
> **Note**
> This feature works only when gosumemory is connected (press "Start")

On Miraya             |  On Twitch
:-------------------------:|:-------------------------:
![image](https://github.com/MirayaProject/miraya/assets/31241607/66b2a944-757c-4872-922d-4ae1426d704d)  |  ![image](https://github.com/MirayaProject/miraya/assets/31241607/b39e6abf-5bc3-46de-a3dd-6b91cdc29f5b)

## In Game Requests
When a user sends a map in the chat, it will be automatically forwarded in the game chat.
> **Note**
> This feature works only when the osu! IRC is connected (press "Start")

On Twitch             |  In Game
:-------------------------:|:-------------------------:
![image](https://github.com/MirayaProject/miraya/assets/31241607/36c4cccc-7e7a-4df9-a621-8c124b2f2f4f)   |  ![image](https://github.com/MirayaProject/miraya/assets/31241607/55391c14-c278-458e-a643-7fdcc367de4b)


## Dark Mode
On Windows, the prefered system theme will be followed.
Light Theme             |  Dark Mode
:-------------------------:|:-------------------------:
![image](https://github.com/MirayaProject/miraya/assets/31241607/7a82154c-2610-4f30-85e4-65ecf5b24349)  |  ![image](https://github.com/MirayaProject/miraya/assets/31241607/bc9635f4-99ff-4d55-a22b-8f9f96d37a16)

## Backup & Restore
You can backup all your skins, custom commands and credentials with a single click
> **Warning**
> Credentials are stored in plain text. Please don't send your backup file to anyone if you selected to export personal data.

![image](https://github.com/MirayaProject/miraya/assets/31241607/82945f0b-f4b1-4688-ac7b-a6e23845d171)


# Dev stuff
This application is currently being developed with Windows 10 (Qt Creator/VS Code and MinGW) and Arch Linux (VS Code with Clang).
Builds are tested with Qt 6.3.0 on Windows and the latest Qt6 version available from the Arch repos

The builds are tested with this two operating systems in mind,
but they should work with any operating system that supports Qt6.

## Building from source
Feel free to build from source if you'd like.

### All platforms
1. Clone the repository
	```bash
	git clone https://www.github.com/MirayaProject/miraya.git
	```

2. Open the CMakeLists.txt file with Qt Creator
	To do that, use the "Open Project" button.


3. Run the project
