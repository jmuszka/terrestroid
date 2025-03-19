# Terrestroid

A planet-exploration sandbox with procedurally-generated worlds and expansive physics simulations.

## About

Inspired by Terraria and No Man's Sky, I envisioned a 2D sandbox with spherical planet physics and randomly-generated terrain.

During the development of this project, I seek to learn more about computer graphics and expand my experience with low-level programming, as well as applying some cool linear algebra and other math concepts as core game mechanics. As such, I will document my learning and design choices throughout this entire process, including handling the graphics pipeline and OpenGL API with a rudimentary game engine, concept design, the mathematics behind the physics simulations, planet generation, optimization techniques, entity AI, and other game mechanics, and more.

For this game I will be using C++, GLEW for interfacing with OpenGL, and GLFW for displaying graphics to the window and handling input; it is my intention for this source code to be portable across Linux (where I will be developing and running the game), Windows, and MacOS. As you can see, we will be working rather close to the hardware - not too many abstractions above the OS-level.

## Installation

Soon, I will create a detailed installation guide. But all the necessary dependencies are located in `dependecies.txt`. I recommend installing each of those from source. Essentially, you need a C++ compiler, OpenGL, an OpenGL wrapper, and a library for displaying OpenGL graphics to the screen.

Once dependencies are installed, simply run `make` in the project directory and run the resulting executable. As this project grows larger and more complex, I may switch to CMake for quality of life purposes.

## Roadmap

Here is a preliminary roadmap for this project:

Before beginning the actual game development (the fun part), we must create wrapper classes to seamlessly automate the graphics rendering, as working directly working with OpenGL interfaces is unwieldy and intellectually draining. As much as I love C, the greatest programming language ever made (sorry Bjarne Stroustrup), an object-oriented paradigm will prove immensely useful for abstracting and reusing OpenGL code; it's no wonder C++ is so widely-used in game development. This will require us to create roughly the following classes:

- **Window** - allow us to configure position, resolution, framerate, and other features
- **Surface** - to draw our OpenGL buffers onto
- **Vertex** - specify a point in 2D space: translate from window coordinates to OpenGL coordinates
- **Triangle** - to automate the OpenGL triangle-drawing process
- **Color** - allow us to change background color and drawing color

With the graphics pipeline streamlined, we can focus our efforts on streamlining the game engine functions:

- **Screen** - handle both the window and the surface; where the game loop will draw objects
- **Input** - to handle keyboard and mouse input from the user (may need to be multiple classes)
- **Shapes** - various classes for shapes, including line, triangle, rectangle, circle, etc.
- **Image** - draw images to the screen; will be useful for later stages of development when we add game sprites

And here's an idea of what some of the game-specific classes will look like:

- **Player** - keep track of player state, with info such as position, speed, sprite, etc.
- **Inventory** - if we decide to add usable and/or collectible items
- **Planet** - the spherical surface which the player will explore
- **Vector** - an internal class that will help with the mathematical computations

Obviously, many more classes will be added and some may be revised. In terms of housekeeping, I need to move documentation and tasks to a separate place in the repo, and make way for a more detailed README file, including a detailed installation guide and a game tutorial.