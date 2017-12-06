# `Flatland Rendering` - Inspired by Flatland

This program was created by Joseph McKinsey for CSCI 261B at Colorado School of Mines.

## Description:

*Flatland: A Romance of Many Dimensions* by A. Squaure (Edwin Abbott Abbott) is
beloved book about a civilization in Flatland. These two dimensional creations
often shapes like squares, cirlces, pentagons, etc. When they look out into their
flat world, they see only edges. In the book, this causes many problems in the
strange Victorian-style class system. A Square later encounters a sphere entering
his world, and so the plot begins.

By adapting the OpenGL renderer to only render a thin slice of the 3D world, this
program establishes a basis for a flatland game and demos some elements of such a
game.

Features
* Moving about in flatland.
* Having cardinal directions to find your way in flatland.
* Creates base classes for future developments in flatland.
* Creating regular polygons, moving, rotating, and scaling them.
* Drawing a rotating cube into flatland.
* Loading Wavefront .obj files into flatland.
* Showcasing the above elements.

Note that this program is not as complete as could be hoped, but with a few more adaptations
it could be used to create an actual game in flatland: where you could interact with other
polygons where they make racist or sexist comments as in the book, or perhaps even
a flatland physics engine as described by Martin Gardner and others.

# Using the Program

## Building with Makefile
Because of the OpenGL use, this program has a much more complicated Makefile so it
can include SFMl and OpenGL. Use the bash `make` command in the directory to produce
the tarbombgame executable. You need SFML 2.1 or above to compile it. It is not
compatable with Windows currently because of the Makefile open gl linking.

## Demo User Inputs
When you start the program, you should see a bar in the center of the screen. This
is where everything is rendered as edges in flatland. You can look left and right
with the left and right arrow keys and move around with WASD. W moves forward. A left, and so on.

Press ESC to pause the rotating and movement of objects in the scene.

Press Q to quit.

## Use by Other Programmers
The FlatShape class is used as a basis for drawing more complex objects in flatland.
Other clasess can derive from it and initialize their own vertices in the 3D world
as described by OpenGL's pointer arrays. However, you only need to use vectors, and
the draw function takes the vector and turns it into an array. Currently, the
tranformations in FlatShape need to be changed slightly to allow for better rotation
of 3D objects instead of simple 2D rotation.

Polygon, the class, draws a regular polygon in red, but it draws the last closing
face in green (this is the face of flatlanders). It takes in a position,
sides, radius and rotation. It has limited functionality for color.

Flatland itself is a class that holds and draws all the objects contained within.
It may have difficulty with derived class member functions due to object slicing,
but this has not been tested. It applies the camera transformations as well, and then
draws each of the objects, so it must be called first.

Because this uses OpenGL, someone using only the base classes may have a great deal
of difficulty setting up initiatlly, so use `main.cpp` as a guide for all of the
complicated necessary OpenGL information. If you use some elements of `main.cpp`,
hopefully you have some knowledge of OpenGL before hand. The classes handle almost
none of the setup for OpenGL's camera, lighting, etc.

### Map of Flatland:
          ^
          |
          y
          |
          |
          |
 <--------x------->

 Positions are handled with SFML's Vector class.

### Current demo: Test Cases

1. Rotating 3D cube in front of the camera.
1. Rotating square (Polygon class with 4 sides).
1. Cube loaded from an obj file.
1. Wolf loaded from an obj file.
1. Triangle in the back.

### Potential Improvements for the Future 
- [ ] Add music to demo.
- [ ] More comprehensive FlatShape base class.
- [ ] Using autoconf and others to streamline makefile process.
- [ ] More creative demo with a broader world.
    * Use the object files included in the data folder.
- [ ] Hotkey for minimap for demo
- [ ] Consider changing background color.
- [ ] Use better lighting system in Flatland class (currently in main).
- [ ] Use glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); ?
- [ ] Add better transformations for FlatShape base class.
- [ ] Non regular polygons.
- [ ] Better coloring for regular polygons.
- [ ] More comprehensive loading for Wavefront .obj files
   * Add materials.
   * Texture mapping? Is it even necessary in flatland?
   * Use groups.
   * Accept quadralaterals or otherwise give error message.
   * Negative indexing.
   * Less intensive processes.
   * Render with VBOs (vertex buffer objects)
- [ ] Element ids in Flatland?
- [ ] Resolve potential object slicing in holding vector in Flatland class.
- [ ] Physics Engine with collision detection.
- [ ] Circle class for smooth shading.
- [ ] Create example building in flatland.
- [ ] Interaction with flatland characters.


## Refelctions

This project has really made me realize how daunting and complex modern
programming is. What little I have done in this project cannot be called
even a game, or even a complete game engine. If I had to repeat this assignment,
I would have chosen something less ambitious and less graphics focused,
perhaps involving the GTK tool kit instead of SFML and OpenGL. OpenGL is
very complex, but so useful that it must be learned for any game programming.
Having a clearer roadmap and more extensive knowledge of OpenGL would have
helped a great deal on this project in hindsight.

However, despite all my misgivings, this still accomplished more than I
expected in the short time available, and I learned about OpenGL, which
may be useful in the future. Although a more data science focused project
could have been more useful for my major, applied mathematics.

# Outside Files Used and their licenses.

`LiberationMono-Regular.ttf` comes from [Liberation Fonts](https://pagure.io/liberation-fonts/).
Liberation Fonts are licensed under the SIL Open Font License Version 1.1.

The animal `.obj` files came from snippysnappets on [free3d.com](https://free3d.com/user/snippysnappets).
They are licensed under a non-commercial license.

`test.obj` and `test.mtl` were exported from Blender 2.76.

The rest of the `.obj` files including `magnolia.obj`, `lamp.obj`, `teapot.obj`, and `icosohedron.obj`
originated from http://people.sc.fsu.edu/%7Ejburkardt/data/obj/obj.html.
They are licensed under the GNU LGPL license.

This program is licensed under the MIT license.
