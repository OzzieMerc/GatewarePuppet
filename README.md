# Gateware Puppet

The Gateware Puppet is a toy that can be manipulated using a controller. You can change expression on the puppet's face by individually controlling the puppets eyes, eyebrows, eyelids, mouth, and face color. This project was created to demonstrate some of the features I worked on for version 1.2a of the [Gateware](https://gitlab.com/gateware-development/gateware/-/releases) middleware.

### The features demonstrated include:
- Xbox One controller support for Mac and Linux.
- PS4 controller support for Mac and Linux.
- Dynamic icon setting at runtime.
- Turning off user window resizing.
- Stability improvements with controller connections on Windows and Linux.
- Wireless controller detection and input mappings on Mac and Linux.

## Platforms Supported
This project has been tested on Windows with Visual Studio 2019.

## Controllers Supported
The project uses Gateware's GController library and therefore supports the same controllers supported by that library.

### Controllers supported on Windows:
- Xbox 360
- Xbox One

### Controllers supported on Mac:
- Xbox 360
- Xbox One
- PS4

### Controllers supported on Linux:
- Xbox 360
- Xbox One
- PS4

## Getting Started
1. Clone the repository.
2. Navigate to the GatewarePuppet/scripts folder.
3. If CMake is not installed, [install CMake.](https://cmake.org/download/)
4. Run Win32Setup.bat to setup the project solution.
5. Navigate to the GatewarePuppet/build/VisualStudio folder.
6. Open GatewarePuppet.sln
7. In the "Solution Explorer" right-click on "GatewarePuppet" and select "Set as Startup Project"
8. You can now build and run the project. A controller is required to manipulate the puppet.

## Links
See more projects I've worked on at [my website.](https://www.ozziemerc.com)
Learn more about Gateware at [the official Gateware repository](https://gitlab.com/gateware-development)