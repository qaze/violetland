First of all, you need to get [mingw-get](http://sourceforge.net/projects/mingw/files/Automated%20MinGW%20Installer/mingw-get-inst/) and install c++ compiler.

Download [boost](http://www.boost.org/users/download/) and extract it in \Program Files\boost, so you have \Program Files\boost\boost`_<ver>`.

Install [CMake](http://www.cmake.org/cmake/resources/software.html).

Download and extract anywhere devel versions of [libsdl](http://www.libsdl.org/download-1.2.php), [libsdl-image](http://www.libsdl.org/projects/SDL_image/), [libsdl-mixer](http://www.libsdl.org/projects/SDL_mixer/), [libsdl-ttf](http://www.libsdl.org/projects/SDL_ttf/).

Then add MinGW\bin and sdl`*` directories to [Windows path](http://publib.boulder.ibm.com/iseries/v5r2/ic2924/books/5445775168.htm).

Run `mingw-get install mingw32-make mingw32-gmp mingw32-libintl`.

Run cmd and cd to \Program Files\boost\boost`_<ver>`. Run bootstrap. Replace `using msvc ;` with `using gcc ;` in file project-config.jam. Run .\bjam.

Generate Makefile with CMake and run mingw32-make.