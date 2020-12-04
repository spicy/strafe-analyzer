# Strafe Analyzer
[![CS:GO + CS:Source](https://img.shields.io/badge/game-CS:GO%20+%20CS:Source-yellow.svg?style=plastic)](https://store.steampowered.com/app/730/CounterStrike_Global_Offensive/) 
[![Windows](https://img.shields.io/badge/platform-Windows-0078d7.svg?style=plastic)](https://en.wikipedia.org/wiki/Microsoft_Windows) 
[![issues](https://img.shields.io/badge/arch-x86-red.svg?style=plastic)](https://en.wikipedia.org/wiki/X86)
[![C++](https://img.shields.io/badge/language-C%2B%2B-%23f34b7d.svg?style=plastic)](https://en.wikipedia.org/wiki/C%2B%2B) 
[![x86](https://img.shields.io/badge/arch-x86-red.svg?style=plastic)](https://en.wikipedia.org/wiki/X86)
[![PayPal](https://img.shields.io/badge/donate-PayPal-104098.svg?style=plastic&logo=PayPal)](https://paypal.me/spicycurrey)
[![Patreon](https://img.shields.io/badge/support%20me-Patreon-104098.svg?style=plastic&logo=Patreon)](https://www.patreon.com/spicycurrey)

Free software for **CS:GO and CS:S**. Designed as an internal cheat - [Dynamic-link library](https://en.wikipedia.org/wiki/Dynamic-link_library) (DLL) which is loaded into either game process.

This is a practice tool that promotes legit movement by telling the user how to improve. The tool analyzes player inputs and shows how to improve with various methods, such as statistics, and realtime graphs / comparisons.

The Strafe Analyzer allows competitive players get precise data on how to improve their movement. The Analyzer is not a cheat by means of its features. It does not manipulate any inputs or gamedata despite being injected. In fact, I am experimenting with my own ClientSide anticheat within the Strafe Analyzer.

Because the Analyzer is a practice tool, and is not globally recognized as permissable, I have limited its use (online) to -insecure servers **ONLY** on CS:S, and to my servers **ONLY** on CS:GO. Otherwise, you are able to use it on any LAN server with the
command 'sv_lan 1'.

Benefits of becoming a Patreon Supporter can be found here [Patreon](https://www.patreon.com/posts/strafe-analyzer-43354531)

## Features
*   **Strafe Trainer** - displays a realtime graph on the players screen of the clients delta yaw, as well as the perfect yaw. (shows how fast to move your mouse).
*   **Sync Trainer** - displays a history of previous keyswitches. (shows if you pressed your keys late or early compared to your mouse direction).
*   **Velocity Graph** - displays a graph of the players velocity. (Also able to compare your velocity to any recorded dataset... *Realtime comparisons with replay bots ( ͡° ͜ʖ ͡°)*).
*   **Record** - records ingame movement (Viewangles, keypresses, etc..) that can be analyzed later (*helpful for record analysis, visualizing cheaters inputs for bans, etc*).
*   **Sensitivity recommendation** - calculates how much the player should increase or decrease their sensitivity in order to bring their strafe speed closer to the correct value (on avg).
*   **Deadzone Visualizer** - draws an arrow towards the players true velocity direction (for movement styles), and visualizes Deadzones (the angles in which a delta yaw results in 0 speedgain).
*   **Mouse/Key direction indicator** - graphs mouse/key direction to visualize key imperfections.
*   **Strafe Range** - finds the total range necessary in order to learn how to do a specific # of strafes per jump. (Finds the total angle of your strafe *before* changing directions *assuming you are moving your mouse at the perfect speed*).
*   **TAS Jump Prediction** - shows the players furthest uncrouched landing position (1tick strafer distance).
*   **Show Movement Vectors** - draws the players movement vectors as unit vectors on the screen. (Viewangle, Velocity direction, Acceleration direction, Deadzones).
*   **Strafe Delta** - times how many ticks it takes to reach at least 80% of perfangle after changing directions.
*   **Show Keys** - displays current movement key states, as well as mouse direction.
*   **Fps_Max check** - tells you when your fps_max is set to a value that decreases speedgain.
*   **+ Other misc statistics :)**

<details>

*   **+ changeable UI positions for most features** 

</details>

### Download

Download the latest release of my loader to have access to the analyzer [Latest Release](https://github.com/spicy/StrafeAnalyzer/releases/latest).

### Using the loader

You might notice there is a username and password. A login is not necessary for the free version, and you can bypass these by pressing enable. If you would like to be able to choose between the most recent stable and dev build, including
other benefits, you can visit my patreon page above to learn more about supporting the project.

## FAQ
### How do I open menu?
Press <kbd>INSERT</kbd> while in either game.

### How do I get into -insecure?
Open CS:GO/CS:S Properties in Steam. Click "Set Launch Options" and paste *-insecure* inside. VAC will not be loaded once your game starts.

### What hooking method does the Analyzer use?
The current hooking method is MinHook (trampoline).

### Screenshot of the Analyzer's loader (1.1) as of (12/3/2020)
![Analyzer 1.1](https://github.com/spicy/StrafeAnalyzer/blob/master/loader.png?raw=true)

## Acknowledgments

*   [rumour](https://github.com/rumoura) For helping setup the base in its early stages.

## License
> Copyright (c) 2020-2022 Daniel Currey

This project is licensed under the [MIT License](https://opensource.org/licenses/mit-license.php) - see the [LICENSE](https://github.com/spicy/StrafeAnalyzer/LICENSE) file for details.
