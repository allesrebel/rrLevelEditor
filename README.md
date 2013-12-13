#Level Editor Using SDLGameEngine API#

##Dependencies##
SDL 1.2, SDL_image 1.2, SDL_mixer 1.2, SDL_ttf 2.0

For those who have Advanced Packaging Tool available, you can enter the following command in the terminal:
    
    apt-get install libsdl1.2-dev libsdl-image1.2-dev libsdl-mixer1.2-dev libsdl-ttf2.0-dev

##Suggested Developer Tools##
Eclipse Kepler 4.3 for C/C++ Developers - http://www.eclipse.org/downloads/packages/eclipse-ide-cc-developers/keplersr1

##How to Setup and Build Using Eclipse on Ubuntu 13.10##
1. After forking the project and using the clone URL to make a local copy (git clone <clone URL>), open Eclipse and import the project.

2. Right click on the project and click on Properties. Under C/C++ Build, click on Settings. Go to the Tool Settings tab and underneath GCC C++ Linker, click on Libraries. In the Libraries(-l) section add "SDL", "SDL_image", "SDL_mixer", and "SDL_ttf" all separately.

   See the following links for more information and images:

   http://lazyfoo.net/SDL_tutorials/lesson01/linux/eclipse/index.php

   http://lazyfoo.net/SDL_tutorials/lesson03/linux/eclipse/index.php

3. Go back and underneath C/C++ Build, click on Tool Chain Editor. Make sure the Current toolchain is Linux GCC and the Current builder is Gnu Make Builder. Click OK.

4. Right click on the project inside Project Explorer and click "Build Project". Next hit Ctrl + F11 to run. Instructions for how to use the level editor are below.

##So this is a VERY basic level editor!##
***_To Add Figures_***

1. Select what piece you wish to place with numbers 1-9
	-This will remove you from delete mode if a valid piece is selected

2. Click to add piece to scene
	-A figure will be following your mouse, once you click it should not move

***_To Remove Figures_***

1. Press escape to exit placing mode 
	-This will get rid of any pieces following your mouse
2. Click on a figure in the scene to delete it
	-Will only work if you click with in the figure

***_To Save Scene_***

1. Simply press s on the keyboard
	-Scene will be saved to level.txt

***_To Load Scene_***

1. Simply restart the editor

##Playing Your Level##
Use w, a, s, d to move, and the mouse with left click to aim and grab!
