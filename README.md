# meowclicker
### may or may not be asscociated with meowware

## Features
- Min/max cps sliders with randomization
- Simulated mouse jitter
- Active toggle (use LMB to autoclick once enabled)
- ImGUI user interface to control settings
- Toggle hotkey (F6)
- Auto BlockHit
- "Minecraft Window Only" checkbox
- Right clicker

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
Alternatively, if you're tired of waiting, open a pull request and contribute!

- [Triggers certain anti-virus programs](https://www.virustotal.com/gui/file/97e670383a7dc272621a864006caea17b203324e3b57fa6807b070cfc9337fa4?nocache=1) (likely caused by Windows API calls)
- Randomization tends to average out and stay at a CPS count towards the middle of your defined range
- Can't click on non-windowed programs (fullscreen mode). For most games, this can be fixed under Video settings by selection Windowed or Windowed Fullscreen
- Continues to spam when looking at blocks, preventing you from breaking blocks and triggering some anti-cheat programs (Minecraft)

## Coming soon
Features to be added soon!
Alternatively, if you're tired of waiting, open a pull request and contribute!

- Click sounds
- Config saving
- Additional customization options
