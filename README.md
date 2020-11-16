# ***StrafeAnalyzer Version 1.1***
This is a practice tool that promotes legit movement by telling the player how to improve.
The tool analyzes player inputs and tells the player how to improve through statistics, realtime graphs, etc. 

The Strafe Analyzer allows competitive movement players get precise data on their movement. The Analyzer is not a cheat. It **does not** manipulate **any** data despite being injected. 

If you are a supporter of mine on my patreon, fill out this form so I can get you your perks and extra features with an account. @ https://docs.google.com/forms/d/1QUcfo90Yn2CAQp68HmyEr_cX_Fi-id7dwxKzWHjB5nw
If you arent interested in being a supporter, you can use the free version by simply ignoring the login, and press enable.

//--------------------------------FREE------------------------------------

• Access to essentially all features

• Only one choice of a build

//----------------------------------5$--------------------------------------

• Access to beta features

• Switch between the most recent dev build, or stable build

• Discord rank (Supporter)

//----------------------------------10+$-------------------------------------

• Everything noted before...

• VIP in all spicehops servers

• Directly request features or changes

• Access to main function logic (code)

• Everything noted before...

• VIP+ in all spicehops servers, and on twitch

• Perms for fun events in spicehops servers

• You name it brudda (something reasonable)

//------------------------------------------------------------------------------\

> https://www.patreon.com/spicycurrey

![Analyzer 1.1](https://github.com/spicy/StrafeAnalyzer/blob/master/loader.png?raw=true)

Currently I am only allowing its use on my servers (which are -insecure, meaning VAC is not required to be running on your client). The Analyzer will not inject to your game if it detects that “-insecure” is not in your launch options. It does this with ReadProcessMemory, which *can* be detected (but it is better than injecting while running in secure). VAC bans are possible when the player does not include -insecure and -untrusted into their launch options. 

> Obviously all accountability is assumed by the player when they choose to inject

Heres a youtube video demonstrating a few features (ver 0.90 == https://www.youtube.com/watch?v=XSQNXGm-n3I)

NOTE!!
Always use the correct fps_max values when using this tool. You will see inaccurate data on graphs. To fix this, you want to cap your fps to a multiple of the tickrate in order to get accurate data

________________

***Features***

-**Strafe Trainer** : Graphs Mouse Data vs Perfect Mouse Data (shows how fast to move your mouse)

-**Sync Trainer** : Lists all strafe sync accuracy KEYS late or KEYS early

-**Mouse/Key direction indicator** : Graphs mouse/key direction to visualize key imperfections.

-**Deadzone Visualizer** : Shows the players true direction of travel, and visualizes the Dead Zones in your strafe for all styles

-**Strafe Range** : Finds the total strafe range (width of your strafe before changing directions *assuming you are moving it at the correct speed*) in order to learn how to do a specific # of strafes per jump.  

-**TAS Jump Prediction** : Shows the players furthest uncrouched landing position (1tick strafer distance)

-**StrafeDelta** : Shows how long it takes for your player to get your first 80% gain tick.

-**ShowKeys** : Shows current key states.

-**Velocity Graph** : Graphs your players velocity.

-**Vector Visualizer** : Draws the players movement vectors. Viewangle, Velocity direction, Acceleration direction, Deadzones (optional).

-**Fps_Max check** : tells you when your fps_max is set to a bad value.

-**Full Analysis** : Players can record themselves play, and run a full analysis on a large dataset. This creates a list of stats and creates PNG Graphs of their data. **In progress**

-**Sensitivity recommendation** : Calculates how much the player should increase or decrease their sensitivity in order to bring their strafe speed to the correct value (on avg).

-**Record** : Spectate a replay bot (or record yourself while you are playing) and press record once the bot spawns on the map.  Record until the end of the run, and the player can use the bots replay data in other functions. Such as the Client Side Bot Path function (inprogress), or to run Bot Data parallel to the players data (such as to compare velocity at any given time in a run).

-**Anti Cheat** : I will not go into detail about what the Strafe Analyzer does to deter and detect cheats, but because the analyzer is injected- it would be foolish to not also include detections for unfair advantages. **In progress**
