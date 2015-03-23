# Eclipse #

Install subclipse and CDT.

Checkout the project from SVN as empty C++ project using wizard.

Goto project properties -> C/C++ Build -> Settings.

Select Tool Settings -> GCC C++ Compiler -> Directories.
Add include path for SDL (f.e. -l/usr/include/SDL).

Select Tool Settings -> Libraries.
Add libraries SDL, SDL\_mixer, SDL\_ttf, SDL\_image, GL (-l).

You're done. Now you can build or debug the project.

# KDevelop 4 #
(weaselweb@web.de)

## Setup ##

  1. Checkout project.
  1. Start Kdevelop and Select Project -> Open / Import Project.
  1. Select top-level CMakeLists.txt.
  1. Confirem CMake buildsystem.
  1. Select build and install dir (e.g. $SRC\_ROOT/build and $SRC\_ROOT/dist).
  1. Select build type.
  1. Build and install.

## Create launch target ##

  1. Select Run -> Configure Launches...
  1. Select violetland and click the green +.
  1. Check Executeable and select absolut path to installed binary (e.g. $SRC\_ROOT/dist/bin/violetland).
  1. Set wirking directory to $SRC\_ROOT/dist/bin.
  1. Select "Build and Install" as dependency actions.

You should be done now be able to launch normally or in a debug session using gdb.

# Visual Studio 2008 #

Checkout the project.

Run the Visual Studio and create a new project from template "Win32 Console Application".
Deselect the precompiled header option and select the empty project option in wizard.

After project creating, add source files to the project (add existing item...).

Go to the project properties -> Configuration properties -> C/C++ -> General and add additional include directories (you must download SDL, SDL\_mixer, SDL\_ttf, SDL\_image packages and also a dirent.h file (see FileUtility.h for details).

Go to the project properties -> Configuration properties -> Linker -> General and add additional library directories (same as in previous step).

Last, go to project properties -> Configuration properties -> General and change character set from unicode to multi-byte.

You're done. Now you can build or debug the project.