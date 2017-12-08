/* CSCI 261B : Final Project: FlatShape Declaration File
 *
 * Description: Declares FlatShape class. This serves as an inheritance class
 * for the other shapes and models in flatland.
 *
 * Author: Joseph McKinsey
 *
 */

#ifndef FLATSHAPE
#define FLATSHAPE
#include <vector>
#include <SFML/Graphics.hpp>

using namespace sf;

// PI defined here.
const double PI = 3.14159265358979323846264;

class FlatShape {
    public:
        // Initializer
        FlatShape();
        // Draw function (Used by Flatland Class)
        void draw();
        // Getters and setters. TODO allow for better 3D rotation.
        // Does OpenGL cause floating point errors with scaling?
        Vector3f getPosition() const;
        float getRotation() const;
        float getScale() const;
        void setPosition(const Vector3f &position);
        void setRotation(const float& position);
        void setScale(const float& scale);
    protected:
        // Protected variables can be accessed by derived classes.
        std::vector<float> _outVertices;
        std::vector<float> _outNormals;
        std::vector<float> _outColors;
        // Position.
        Vector3f _position;
        // TODO 3D rotation
        float _rotation;
        float _scale;
        // Helper add3 functions. Add the x, y, z to the incoming vector.
        void add3(std::vector<float> &vec, float x, float y, float z);
        void add3(std::vector<float> &vec, Vector3f addition);
};

#endif
