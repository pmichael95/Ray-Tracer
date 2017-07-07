-----------------
| PROGRAMMED BY:| 
| Philip Michael|
|		|
|		|
| COURSE:	|
| COMP371	|
-----------------

// 1 \\ -  INTRODUCTION
This project implements a simple ray tracer in C++ using GLM and CImg as primary libraries.
A scene file is loaded from the Scenes folder, calculations are performed, and finally an image is rendered.

// 2 \\ - FILE I/O + FORMATS
All scene files must follow the strict formatting provided in the already-existing scene files.
Furthermore, scene files must be in the Scenes folder.
It is essential that only ONE camera and ONE plane exist per scene.
You can have any number of spheres, triangles, and light sources per scene file.

// 3 \\ - USAGE INSTRUCTIONS
First off, make sure you have the necessary libraries: GLM and CIMG.
For GLM, you need to add it to your project's settings and link it.
Then, open the .sln in Visual Studio, and run to see the result.
If you wish to modify the Scene file, go to main.cpp and change the fpath variable's contents to point to your desired scene file.

// 4 \\ - FINAL REMARKS
This application fully handles loading and processing of scene files.
It will also render it accordingly. 
However, there is currently no anti-aliasing, no shadows, and no actual illumination factors.


Thank you for reading!
Enjoy :)

- Philip M.