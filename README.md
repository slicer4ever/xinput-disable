#originally ported from  briankendall/xinput-disable-guide to do more than just suppressing the guide.

# xinput-disable
A wrapper DLL that stops apps from detecting xinput controllers input. Originally created to prevent certain games which don't allow controllers to be disabled(*cough*overwatch, destiny 2, skyrim, etc*cough*)

# Building
Builds were done on MSVS17, it should be possible to build the project in 32 bit and 64 bit form.  

# Installation
Drop the included binarys into the same directory as the application's exe and they should usually be loaded in place, of course not every game is so simple and it might require replacing the system32 files.

When modifying the system32 or SysWOW64 versions of xinput you have to jump through a couple loops, first you need to set your self with the permissions to change the file.  secondly the proxy input has been designed to first look for XInput1_4.old.dll before it tries to load XInput1_4.dll, so if you don't want to make compile the program yourself, just rename the original file to XInput1_4.old.dll. 

now then remember that changing the system level implementation means nothing will see any dx input, I only recommend you use this in conjunction with something like auto hot key where a script can be made that will temporarily replace the file until the target game is launched, then replace it back with the old file(renaming files in use is perfectly legal).

This may also trigger game anti-hack features, it hasn't been severly tested yet.