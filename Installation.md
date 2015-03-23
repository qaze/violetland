# Windows #

The windows executable was created with help of MSVC++ 2008, thus the Microsoft Visual C++ 2008 Redistributable Package may be needed.

# Linux #
Currently violetland is available for many operation systems as package. Check the [Third Party Packages](http://code.google.com/p/violetland/wiki/ThirdParyPackages) page.

An universal way to play violetland on linux is to build the program with help of the cmake build system. You probably can install it from the main repository of your linux distribution. Your system must have some **libraries** and **gcc**:
> ### Libraries ###
  * SDL
  * SDL\_image
  * SDL\_ttf
  * SDL\_mixer
  * boost
  * If you use package-based distribution, you should install also the developement packages (like SDL-devel or libboost-dev).

Besides, some additional steps are required.

First, unzip the downloaded package:

`unzip violetland-v<your version number>-src.zip`

`cd violetland-v<your version number>/`

Second, make the program using cmake:

`mkdir build`

`cd build`

`cmake ..`

`sudo make install`

Third, run the program:

`violetland`

The readme file contains more instructions.

# Mac OS X #

Just download one of the Mac builds, unzip, they should run out of the box on Mac OS X 10.5 and later.