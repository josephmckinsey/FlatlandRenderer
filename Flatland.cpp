/* CSCI 261B : Final Project: Flatland Class Implementation File
 *
 * Description: Contains record of flatland world. Handles the rotation tranfor-
 * mations and transformation, but not the position and rotations of the indiv-
 * dual objects.
 *
 * Author: Joseph McKinsey
 *
 */

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <vector>
#include <cmath>
#include "FlatShape.h"
#include "Flatland.h"

using namespace sf;

// Default constructor.
Flatland::Flatland() {
    _cameraAngle = 0;
    _cameraPosition.x = 0;
    _cameraPosition.y = -200;
}

// Constructor but with shapes.
Flatland::Flatland(std::vector<FlatShape> shapes) {
    _population = shapes;
    _cameraAngle = 0;
    _cameraPosition.x = 0;
    _cameraPosition.y = -200;
}

// Helper function that preserves precision by adjusting the camera angle
// if it exceeds 2 * PI or is less than 0. It wraps the values around to
// the other end.
void Flatland::normalizeAngle() {
    if (_cameraAngle >= 2 * PI) {
        // Make the value fall between 0 and 2 * PI
        _cameraAngle += -2 * PI * ceil((_cameraAngle - 2 * PI) / (2 * PI));
    }
    else if (_cameraAngle < 0) {
        // Make the value fall between 0 and 2 * PI
        _cameraAngle += -2 * PI * floor(_cameraAngle / (2 * PI));
    }
}

// Offsets rotation. Uses normalizeAngle
void Flatland::offsetRotation(const float &angle) {
    _cameraAngle += angle;
    normalizeAngle();
}

// Offsets position.
void Flatland::offsetPosition(const Vector2f &position) {
    _cameraPosition += position;
}

// Sets rotation (uses normalizeAngle);
void Flatland::setRotation(const float &angle) {
    _cameraAngle = angle;
    normalizeAngle();
}

// Sets position.
void Flatland::setPosition(const Vector2f &position) {
    _cameraPosition = position;
}

// Get rotation.
float Flatland::getRotation() const {
    return _cameraAngle;
}

// Get position.
Vector2f Flatland::getPosition() const {
    return _cameraPosition;
}

// Add Shape to Flatland.
// TODO Because of how minimal the derived classes are to everything,
// some object slicing occurs. Currently its not a problem, but definitely in the future
// it could be a big problem. I'm not sure if you can use the derived member functions
// from main.cpp because of that.
void Flatland::addShape(const FlatShape &shape) {
    _population.push_back(shape);
}

// Remove shape.
void Flatland::removeShape() {
    _population.pop_back();
}

// Get shape as reference (allows for assignment and such in main.cpp
// See above TODO.
FlatShape& Flatland::at(unsigned int i) {
    return _population.at(i);
}

// Draw objects in flatland.
void Flatland::draw() {
    // Rotate camera. (also adjusts for radians)
    glRotatef(_cameraAngle / PI * 180, 0, 1, 0);
    // Positions camera.
    glTranslatef(_cameraPosition.x, 0, _cameraPosition.y);
    // Draw all of the objects.
    for (unsigned int i = 0; i < _population.size(); i++) {
        _population.at(i).draw();
    }
}

// Draws hud with specified font (so that the font can be loaded once
// in the main.cpp
void Flatland::drawHUD(const Font &myFont, RenderWindow* window) {
    // Currently the HUD consists only of a basic compass.
    Text compass;
    compass.setFont(myFont);
    compass.setColor(Color::White);
    // Makes the font relatively small
    compass.setCharacterSize(15);
    if (_cameraAngle < PI / 4 || _cameraAngle >= 7 * PI / 4) {
        compass.setString("N");
        // Because the FOV is always 90 degrees. This simplies the
        // placement of the center of the compass easily.
        FloatRect textRect = compass.getLocalBounds();
        // Sets position of text to the center.
        compass.setOrigin(textRect.left + textRect.width/2.0f,
               textRect.top  + textRect.height/2.0f);
        // Sets the compass just above the other stuff. Sets the x variation with the FOV parameter from before.
        compass.setPosition(-sin(_cameraAngle) * window->getSize().x + window->getSize().x / 2.0, 11 * window->getSize().y / 25.0);
    }
    else if (_cameraAngle >= PI / 4 && _cameraAngle < 3 * PI / 4) {
        compass.setString("E");
        FloatRect textRect = compass.getLocalBounds();
        compass.setOrigin(textRect.left + textRect.width/2.0f,
               textRect.top  + textRect.height/2.0f);
        compass.setPosition(-sin(_cameraAngle - PI / 2) * window->getSize().x + window->getSize().x / 2.0, 11 * window->getSize().y / 25.0);
    }
    else if (_cameraAngle >= 3 * PI / 4 && _cameraAngle < 5 * PI / 4) {
        compass.setString("S");
        FloatRect textRect = compass.getLocalBounds();
        compass.setOrigin(textRect.left + textRect.width/2.0f,
               textRect.top  + textRect.height/2.0f);
        compass.setPosition(-sin(_cameraAngle - PI) * window->getSize().x + window->getSize().x / 2.0, 11 * window->getSize().y / 25.0);
    }
    else if (_cameraAngle >= 5 * PI / 4 && _cameraAngle < 7 * PI / 4) {
        compass.setString("W");
        FloatRect textRect = compass.getLocalBounds();
        compass.setOrigin(textRect.left + textRect.width/2.0f,
               textRect.top  + textRect.height/2.0f);
        compass.setPosition(-sin(_cameraAngle - 3 * PI / 2) * window->getSize().x + window->getSize().x / 2.0, 11 * window->getSize().y / 25.0);
    }

    window->draw(compass);
}

// Test cube. Rotates in 3D space. Very confusing, may cause headaches.
// Very very simple execution. Hard coded so nothing can go wrong.
// Some people can actually see that this thing is a cube. Uses very basic code.
void Flatland::draw3DRect(const float &angle) {
    glPushMatrix();
    glRotatef(angle * 60, 1, 0, 0);
    glRotatef(angle * 20, 0, 1, 0);
    glRotatef(angle * 95, 0, 0, 1);

    // GL_QUADS is deprecated past OpenGL 2.0, so be warned.
    glBegin(GL_QUADS);
    glColor3f(0, 1, 1); //cyan
    glNormal3f(0, 0, -1);
    glVertex3f(-50.f, -50.f, -50.f);
    glVertex3f(-50.f,  50.f, -50.f);
    glVertex3f( 50.f,  50.f, -50.f);
    glVertex3f( 50.f, -50.f, -50.f);

    glColor3f(0, 0, 1); //blue
    glNormal3f(0, 0, 1);
    glVertex3f( 50.f, -50.f, 50.f);
    glVertex3f( 50.f,  50.f, 50.f);
    glVertex3f(-50.f,  50.f, 50.f);
    glVertex3f(-50.f, -50.f, 50.f);

    glColor3f(1, 0, 1); //magenta
    glNormal3f(-1, 0, 0);
    glVertex3f(-50.f, -50.f,  50.f);
    glVertex3f(-50.f,  50.f,  50.f);
    glVertex3f(-50.f,  50.f, -50.f);
    glVertex3f(-50.f, -50.f, -50.f);

    glColor3f(0, 1, 0); //green
    glNormal3f(1, 0, 0);
    glVertex3f(50.f, -50.f, -50.f);
    glVertex3f(50.f,  50.f, -50.f);
    glVertex3f(50.f,  50.f,  50.f);
    glVertex3f(50.f, -50.f,  50.f);

    glColor3f(1, 1, 0); //yellow
    glNormal3f(0, -1, 0);
    glVertex3f(-50.f, -50.f,  50.f);
    glVertex3f(-50.f, -50.f, -50.f);
    glVertex3f( 50.f, -50.f, -50.f);
    glVertex3f( 50.f, -50.f,  50.f);

    glColor3f(1, 0, 0); //red
    glNormal3f(0, 1, 0);
    glVertex3f( 50.f, 50.f,  50.f);
    glVertex3f( 50.f, 50.f, -50.f);
    glVertex3f(-50.f, 50.f, -50.f);
    glVertex3f(-50.f, 50.f,  50.f);
    glEnd();
    glPopMatrix();
}
