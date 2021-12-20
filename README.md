# Strafe Analyzer
[![CS:GO + CS:Source](https://img.shields.io/badge/game-CS:GO%20+%20CS:Source-yellow.svg?style=plastic)](https://store.steampowered.com/app/730/CounterStrike_Global_Offensive/) 
[![Windows](https://img.shields.io/badge/platform-Windows-0078d7.svg?style=plastic)](https://en.wikipedia.org/wiki/Microsoft_Windows) 
[![issues](https://img.shields.io/github/issues/spicy/StrafeAnalyzer.svg?style=plastic)](https://github.com/spicy/StrafeAnalyzer/issues)
[![C++](https://img.shields.io/badge/language-C%2B%2B-%23f34b7d.svg?style=plastic)](https://en.wikipedia.org/wiki/C%2B%2B) 
[![x86](https://img.shields.io/badge/arch-x86-red.svg?style=plastic)](https://en.wikipedia.org/wiki/X86)
[![PayPal](https://img.shields.io/badge/donate-PayPal-104098.svg?style=plastic&logo=PayPal)](https://paypal.me/spicycurrey)
[![Patreon](https://img.shields.io/badge/support%20me-Patreon-104098.svg?style=plastic&logo=Patreon)](https://www.patreon.com/spicycurrey)

Free software for **CS:GO and CS:S**. Designed as an internal cheat - [Dynamic-link library](https://en.wikipedia.org/wiki/Dynamic-link_library) (DLL) which is loaded into either game process.

This is a practice tool that promotes legit movement by telling the user how to improve. The tool analyzes player inputs and shows how to improve with various methods, such as statistics, and realtime graphs / comparisons.

The Strafe Analyzer allows competitive players get precise data on how to improve their movement. The Analyzer is not a cheat by means of its features. It does not manipulate any inputs despite being injected.

Because the Analyzer is a practice tool, I have limited its use to specific -insecure servers **ONLY**. Otherwise, you are able to use it on any LAN server with the command 'sv_lan 1'.

### Screenshot of the Analyzer's loader (1.2) as of (6/11/2021)
![Analyzer 1.2](https://github.com/spicy/StrafeAnalyzer/blob/master/loader.png?raw=true)

## Features
*   **Strafe Trainer** - displays a realtime graph on the players screen of the clients delta yaw, as well as the perfect yaw. (shows how fast to move your mouse).
*   **Sync Trainer** - displays a history of previous keyswitches. (shows if you pressed your keys late or early compared to your mouse direction).
*   **RouteTool** - draws recorded movement routes on the players screen.
*   **Velocity Graph** - displays a graph of the players velocity. (Also able to compare your velocity to any recorded dataset... *Realtime comparisons with replay bots ( ͡° ͜ʖ ͡°)*).
*   **Sensitivity recommendation** - calculates how much the player should increase or decrease their sensitivity in order to bring their strafe speed closer to the correct value (on avg).
*   **Deadzone Visualizer** - draws an arrow towards the players true velocity direction (for movement styles), and visualizes Deadzones (the angles in which a delta yaw results in 0 speedgain).
*   **Mouse/Key direction indicator** - graphs mouse/key direction to visualize key imperfections.
*   **Strafe Range** - finds the total range necessary in order to learn how to do a specific # of strafes per jump. (Finds the total angle of your strafe *before* changing directions *assuming you are moving your mouse at the perfect speed*).
*   **Show Movement Vectors** - draws the players movement vectors as unit vectors on the screen. (Viewangle, Velocity direction, Acceleration direction, Deadzones).
*   **Show Keys** - displays current movement key states, as well as mouse direction.
*   **+ Other misc statistics :)**

<details>

*   **+ changeable UI positions for most features** 

</details>

### Download

Download the [latest release](https://github.com/spicy/StrafeAnalyzer/releases/latest) of my loader to have access to the analyzer.

## FAQ
### How do I open menu?
Press <kbd>INSERT</kbd> while in either game.

### How do I get into -insecure?
Open CS:GO/CS:S Properties in Steam. Click "Set Launch Options" and paste *-insecure* inside. VAC will not be loaded once your game starts.

### What hooking method does the Analyzer use?
The current hooking method is MinHook (trampoline).

## Acknowledgments

*   [rumour](https://github.com/rumoura) for helping setup the base in its early stages.

## License
> Copyright (c) 2020-2022 Daniel Currey

This project is licensed under the [MIT License](https://opensource.org/licenses/mit-license.php) - see the [LICENSE](https://github.com/spicy/StrafeAnalyzer/LICENSE) file for details.
