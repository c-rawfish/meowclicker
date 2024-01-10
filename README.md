# meowclicker
### A lightweight, humanized autoclicker written in C++

## Features
- Min/max cps sliders with randomization
- Simulated mouse jitter
- Active toggle (use LMB to autoclick once enabled)
- ImGUI user interface to control settings

## Install
To get the latest version of meowclicker, navigate to the releases tab and download the latest version.
Alternativly, you can compile the source yourself with the following steps:

1. Navigate to the repo's page and click Code > Download Zip (this can also be done with Git CLI/GUI)
2. Extract the .zip to whichever folder you would like to save it in
3. Open the .sln file to open the Visual Studio Project
4. Build as Release/x86

After following these steps you will have a fully functioning build of meowclicker!

## Known Issues
These issues are known problems with meowclicker. They will be fixed soon.
Alternativly, if you're tired of waiting, open a pull request and contribute!

- [Triggers certain anti-virus programs](https://www.virustotal.com/gui/file/b4afef03df82fd9ae2ec34ced99635c9d8561d288996ac50b8135ab803b912ed?nocache=1) (likely caused by Windows API calls)
- Randomization tends to average out and stay at a CPS count towards the middle of your defined range

## Coming soon
Features to be added soon!
Alternativly, if you're tired of waiting, open a pull request and contribute!

- Click sounds
- Customizable toggle hotkey
- Bridge/right clicker
- Config saving
- Additional customization options
- Window selector (only click on certain windows, like Minecraft)
