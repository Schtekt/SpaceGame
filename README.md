SpaceGame
=======
This is a simple game created so that the creators would try their hands at procedural generation.
___
Acknowledgements
-----------
* This project is developed and tested for windows, but probably works for Mac and Linux as well (no promises!).
* This idea takes heavy inspiration from from the youtube video _Procedural Generation: Programming The Universe_, by the user javidx9 Link: https://www.youtube.com/watch?v=ZZY9YE7rZJw (Last accessed: 2020-06-11).

* This repo uses premake5 to build its solution and/or projects. Only the source code is meant to be stored on github.

How to build the solution
-----------
To set up this solution on windows:
1. Create a folder and name it _dependencies_ in the repository root folder. 
2. Download sfml and put the folders _include_ and _lib_ in the created folder.
3. Download premake5 (https://premake.github.io/) and move the executable to the repository root folder.
4. Run the executable in the repository folder through the command prompt. Use the input to specify what you wish to build (For Visual Studio 2019 the full command would be **premake5 vs2019**).
5. A new folder should now have been created called _build_. In this folder any solutions should have been placed.