SmarterQC
=========

Smarter Quick cast for Dota2

Quick cast in Dota2 actually is casted on keypress, which prevent the player to visualize the AoE as if quick cast is disable.

This POC allows the user to press a key to visualize the AoE and only then cast on key release. It can be cancelled at any time using a right click.
Toogle with F8 (Can be changed using args)

This is an implementation of a low level keyobard hook, just as a keylogger. We catch the key pressed and take decision on whatever we should do.
Here, we simulate a key press and release on player press, and simulate a left click on player release.

This make heavy use of Windows.h and therefore will not work on Linux. Feel free to port.
