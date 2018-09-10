#originally ported from  briankendall/xinput-disable-guide to do more than just suppressing the guide.

# xinput-disable
A wrapper DLL that stops apps from detecting xinput controllers input. Originally created to prevent certain games which don't allow controllers to be disabled(*cough*overwatch, destiny 2, skyrim, etc*cough*)

# Building
Builds were done on MSVS17, it should be possible to build the project in 32 bit and 64 bit form.  

# Installation
Drop the included binarys into the same directory as the application's exe and they should usually be loaded in place, of course not every game is so simple and it might require replacing the system32 files(in which case the source code will need to be modified to point to the original dll since this is just a proxy).

This may also trigger game anti-hack features, it hasn't been severly tested yet.