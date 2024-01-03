# **VisuSysSol**
Scientific visualization of the solar system in C++ with OpenGL.

## **Installation**
Compilation is possible using Cmake, both on Windows and Linux.

### Linux:
```
> mkdir build
> cd build
> cmake ..
> make
```

### Windows:
Compilation can be done using command line (similar to Linux), but it's recommended to setup a VSCode c++ compilator and use the integrated options. Here is the steps in VSCode to compile this program:
```
> Go to the CMake Configure tab, choose a compilator and the "Release" option. Select "VisuSysSol" as the Build and Launch targets.
It should launch cmake automatically.

> At the bottom of Vscode, choose the Build option, and it should compile the program.
Please note that warnings are expected because some external libraries are using old programming methods.

> At the bottom of Vscode, choose the Launch option, and it should open the program main window.
```

## **Usage**
The executable should be located in a new directory called bin/.

You can move the camera by clicking on the screen while moving your cursor and scroll to zoom.

You can hide orbits by pressing to O key, or modify the draw methods with the F, L and P keys.

If using the trackball camera, you can use the Z, Q, S and D keys to move (or WASD if English keyboard).

Any others useful information can be found in the report located in the doc/ folder.

## **Project directories**
Textures are stored in assets/textures/ and they are copied automatically to the bin/assets/textures/ during compilation.

Source files are located in the src/ folder. I also added personal source files in the glimac/src/ folder since they all use the template of the glimac library (Circle, FreeflyCamera and TrackballCamera).

Other important pieces of information can be found in the doc/ directory.

## **Authors and acknowledgment**
By Ledoux Johan

Special thanks to Venceslas Biri
