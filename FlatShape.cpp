/* CSCI 261B : Final Project: FlatShape Class Implementation File
 *
 * Description: Implements the FlatShape class. It serves an basic class
 * to define all the other drawable classes in flatland.
 *
 * Author: Joseph McKinsey
 *
 */

#include <SFML/OpenGL.hpp>
#include <vector>
#include "FlatShape.h"

using namespace sf;

// Basic initializer. Only there for functional use by normal classes.
FlatShape::FlatShape() {
    return;
}

// Position Getter. Uses 3 dimensional points.
// TODO Consider using 2D setter and getter as well?
Vector3f FlatShape::getPosition() const {
    return _position;
}

// Rotates shape along z-axis. TODO: Add 3D rotation capabilities for
// the WavefrontShape Class (because right there is no way to turn the objects
// in 3D space.).
float FlatShape::getRotation() const {
    return _rotation;
}

// Scales by constant. TODO Do floating point errors occur from repeated use of this?
float FlatShape::getScale() const {
    return _scale;
}

// Sets position
void FlatShape::setPosition(const Vector3f &position) {
    _position = position;
}

// Sets rotation. See TODO above.
void FlatShape::setRotation(const float &rotation) {
    _rotation = rotation;
}

// Sets scale
void FlatShape::setScale(const float &scale) {
    _scale = scale;
}

// Draw function. Used by flatland class. Ignores opacity.
// TODO Add better rotation and scaling.
void FlatShape::draw() {
    // Saves OpenGL states (to protect camera transformation that's
    // already been applied.
    glPushMatrix();
    // Apply location, scaling, and rotation of the object.
    glTranslatef(_position.x, _position.z, -_position.y);
    glScalef(_scale, _scale, _scale);
    glRotatef(_rotation / PI * 180, 0, 1, 0);

    // Use vertex array.
    glEnableClientState(GL_VERTEX_ARRAY);
    if (_outVertices.size() == _outNormals.size()) {
        // Only use normals if they are used everywhere in the object.
        glEnableClientState(GL_NORMAL_ARRAY);
    }
    // Use Color array
    glEnableClientState(GL_COLOR_ARRAY);
    // Uses _outPointer converted to array by "&foo[0]"
    // Must be list of floats with 3 values.
    glVertexPointer(3, GL_FLOAT, 0, &_outVertices[0]);
    // Only use normals if they are used everywhere.
    if (_outVertices.size() == _outNormals.size()) {
        glNormalPointer(GL_FLOAT, 0, &_outNormals[0]);
    }
    glColorPointer(3, GL_FLOAT, 0, &_outColors[0]);

    // Draw triangles.
    glDrawArrays(GL_TRIANGLES, 0, _outVertices.size() / 3);

    // Disable everything.
    glDisableClientState(GL_VERTEX_ARRAY);
    if (_outVertices.size() == _outNormals.size()) {
        glDisableClientState(GL_NORMAL_ARRAY);
    }
    glDisableClientState(GL_COLOR_ARRAY);

    // Reset transformations to what they were before.
    glPopMatrix();
}

// Helper add3 functions. Add the x, y, z to the incoming vector.
void FlatShape::add3(std::vector<float> &vec, float x, float y, float z) {
    vec.push_back(x);
    vec.push_back(y);
    vec.push_back(z);
}

// Helper add3 functions. Add the x, y, z to the incoming vector.
void FlatShape::add3(std::vector<float> &vec, Vector3f addition) {
    vec.push_back(addition.x);
    vec.push_back(addition.y);
    vec.push_back(addition.z);
}

// Map of Flatland:
//          ^
//          |
//          y
//          |
//          |
//          |
// <--------x------->
