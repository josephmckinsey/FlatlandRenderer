/* CSCI 261B : Final Project: Flatland Rendering
 *
 * Description: It's like the book Flatland, but it renders the world into
 * first person mode on your computer.
 *
 * Author: Joseph McKinsey
 *
 */

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "Flatland.h"
#include "Polygon.h"
#include "WavefrontShape.h"

using namespace sf;

// Map of Flatland:
//          ^
//          |
//          y
//          |
//          |
//          |
// <--------x------->

// Helper function to initiatialize lighting in OpenGL
// Currently only positions lighting right by users head. TODO
void initLighting() {
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    // Enalbe color material lighting lighting
    glEnable(GL_COLOR_MATERIAL);
    // Ambient Light
    GLfloat ambientColor[] = {0.4, 0.4, 0.4, 100};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
    // Positioned light
    GLfloat lightColor0[] = {0.7, 0.7, 0.7, 100};
    GLfloat lightPos0[] = {4, 0, 15, 1};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
}

// Makes sure everything is drawn in the correct order in OpenGL
void initZBuffer() {
    // Handle zbuffer + corrective perspective.
    glClearDepth(1);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    // Unnecessary or necessary: find out: TODO
    // glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

// Function for debugging purposes. Prints camera position and rotation.
void reportCoordinates(Flatland &flatland) {
    std::cout << "x: " << flatland.getPosition().x << " y: "
              << flatland.getPosition().y << " theta: "
              << flatland.getRotation() << std::endl;
}

// Handle Keyboard Input. Called from event loop.
// WASD to move around. Arrows keys to look left and right.
void handleKeyboardInput(Flatland &flatland) {
    // Values by which keyboard presses are multiplied.
    // Flatlad is larger than 2*pi which is why movementMult
    // is so much larger than rotateMult.
    // Determined by trial/error.
    float movementMult = 1.7;
    float rotateMult = 0.035;
    // Creates movement and rotation values.
    Vector2f movement(0, 0);
    float rotation = 0;
    // Checks which keys are placed. Trigonometry to make user go
    // where pointed.
    if (Keyboard::isKeyPressed(Keyboard::W)) {
        // See graph of flatland for interpretration of values.
        movement.x += -movementMult * sin(flatland.getRotation());
        movement.y += movementMult * cos(flatland.getRotation());
    }
    if (Keyboard::isKeyPressed(Keyboard::S)) {
        movement.x += movementMult * sin(flatland.getRotation());
        movement.y += -movementMult * cos(flatland.getRotation());
    }
    if (Keyboard::isKeyPressed(Keyboard::D)) {
        movement.x += -movementMult * cos(flatland.getRotation());
        movement.y += -movementMult * sin(flatland.getRotation());
    }
    if (Keyboard::isKeyPressed(Keyboard::A)) {
        movement.x += movementMult * cos(flatland.getRotation());
        movement.y += movementMult * sin(flatland.getRotation());
    }
    // Rotation values are much easier.
    if (Keyboard::isKeyPressed(Keyboard::Left)) {
        rotation += -rotateMult;
    }
    if (Keyboard::isKeyPressed(Keyboard::Right)) {
        rotation += rotateMult;
    }
    // Apply changes to flatland.
    flatland.offsetPosition(movement);
    flatland.offsetRotation(rotation);
    // Optional Debugging.
    // reportCoordinates(flatland);
}

int main() {
    // Initialize settings. Allows for depth checks during rasterization
    // on older intel cards.
    // Note that these may cause errors when compiling on Cloud9.
    ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 2;
    // Create window.
    RenderWindow window(VideoMode(640, 480), "Flatland",
                        Style::Default, settings);
    // Prevent screen tearing.
    window.setVerticalSyncEnabled(true);
    // Set view on window. Allows for better resizing in event loop.
    window.setView(View(FloatRect(0, 0, 640, 480)));
    // Sets openGl context to the window.
    window.setActive(true);
    // See helper function above.
    initZBuffer();
    // Creates clock: used for rotation.
    Clock clock;
    // Background color. TODO consider changing.
    glClearColor(0.1, 0.1, 0.1, 1);
    // See helper function above.
    initLighting();

    // Sets viewport of open gl to take up 1/25 of the vertical section of the
    // screen.
    glViewport(0, 12 * window.getSize().y / 25,
            window.getSize().x, window.getSize().y / 25);
    // Sets projection matrices for open gl. Frustum only takes only a very 
    // thin slice of the world.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Creates 90 degree FOV into Flatland.
    // glFrustum(-1, 1, -1, 1, 1, 900);
    glFrustum(-1, 1, -0.0003, 0.0003, 1, 900);
    // Normalizes normal vectors drawn by OpenGL. Necessary for scaling.
    glEnable(GL_NORMALIZE);
    
    // TODO add music?

    // Load font.
    Font myFont;
    if (!myFont.loadFromFile("data/LiberationMono-Regular.ttf")) {
        std::cerr << "Could not load font" << std::endl;
        return -1;
    }
    // Rotates objects
    bool rotate = true;
    float angle = 0;
    
    // TODO
    // Add actual creativity to my project. Like flowers. that would be cool.
    // Initialize flatland.
    Flatland flatland;
    // Adds square of radius 50 (distance from center to point).
    flatland.addShape(Polygon(Vector2f(200, 0), 4, 50, 0));
    // Load wolf.obj
    std::ifstream testWolf ("data/wolf.obj");
    flatland.addShape(WavefrontShape(Vector3f(0, -400, 0), 0.2, 0, testWolf));
    // Load test cube
    std::ifstream testCube ("data/test.obj");
    flatland.addShape(WavefrontShape(Vector3f(0, 200, 0), 50, 0, testCube)); 
    // Adds triangle of radius 50.
    flatland.addShape(Polygon(Vector2f(0, 600), 3, 50, PI));

    // Draw loop.
    while (window.isOpen()) {
        // Event loop.
        Event event;
        while (window.pollEvent(event)) {
            // Close window.
            if (event.type == Event::Closed) {
                window.close();
            }
            // Resize window.
            else if (event.type == Event::Resized) {
                // Adjusts viewport for increased height. Width adjusts automatically.
                glViewport(0, 12 * event.size.height / 25,
                        event.size.width, event.size.height / 25);
                window.setView(View(FloatRect(0, 0, event.size.width, event.size.height)));

            }
            else if (event.type == Event::KeyPressed) {
                if (Keyboard::isKeyPressed(Keyboard::Escape)) {
                    // Cease rotation.
                    rotate = !rotate;
                }
                if (Keyboard::isKeyPressed(Keyboard::Q)) {
                    window.close();
                }
            }
        }
        // Process keyboard input for user movement. See helper function above.
        handleKeyboardInput(flatland);
        // Clear open gl for drawing. Switch to modelview.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        // Add angle of rotation since clock started.
        if (rotate) {
            angle += clock.getElapsedTime().asSeconds();
        }
        // Restart clock so time is only added every loop.
        clock.restart();

        // Refresh open gl states. Allows drawing of SFML Objects.
        // TODO Add minimap!
        window.pushGLStates();
        // Draws HUD from flatland. Currenly only draws cardinal directions to help get around.
        flatland.drawHUD(myFont, &window);
        window.popGLStates();

        // Update flat land. Rotate square. Mave the goat wave in an out.
        flatland.at(0).setRotation(angle);
        flatland.at(1).setPosition(Vector3f(0, -400, 100*sin(angle) - 100));
        // flatland.draw() automatically sets the position, but all other direct drawing must occur after.
        flatland.draw();
        // test rotating 3d rectangle.
        flatland.draw3DRect(angle);
        // Display window.
        window.display();
    }
    return EXIT_SUCCESS;
}
