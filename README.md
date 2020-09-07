# StrafeAnalyzer Version 1.0
This is a practice tool that promotes legit movement by telling the player how to improve.
The tool analyzes player inputs and tells the player how to improve through statistics, realtime graphs, etc. 

The Strafe Analyzer is an idea that I have had for some time, where a competitive player could get precise data on their movement imperfections. The Analyzer is not a cheat. It does not manipulate any data despite being injected. Currently I am only allowing its use on my servers (which are -insecure, meaning VAC is not required to be running on your client when you play on my servers). The Analyzer will not inject to your game if it detects that “-insecure” is not in your launch options. It does this with ReadProcessMemory, which *can* be detected (but it is better than injecting while running in secure). This injects into the game. VAC bans are possible when the player does not include -insecure and -untrusted into their launch options. 

Obviously all accountability is assumed by the player when they choose to inject, however this application does

Currently, it is only usable on my servers on CSGO. But once CSS integration is finished, you will be able to use this on many other servers.


You can request to make a beta account through a google forms link @ https://docs.google.com/forms/d/e/1FAIpQLSfZvBdjR4gZqw90hwvtgY_6iKO-iXUHs1068soIey2Lli8Mdg/viewform?usp=sf_link

Heres a youtube video demonstrating a few features (ver 0.90 == https://www.youtube.com/watch?v=XSQNXGm-n3I)

NOTE!!
Always use the correct fps_max values when using this tool. You will see inaccurate data on graphs! To fix this, you want to cap your fps to a multiple of the tickrate in order to get accurate data

