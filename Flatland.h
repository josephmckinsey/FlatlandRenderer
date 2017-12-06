/* CSCI 261B : Final Project: Flatland Class Declaration File
 *
 * Description: Contains record of flatland world. Handles the rotation tranfor-
 * mations and transformation, but not the position and rotations of the indiv-
 * dual objects.
 *
 * Author: Joseph McKinsey
 *
 */

#ifndef FLATLAND
#define FLATLAND

#include <SFML/Graphics.hpp>
#include <vector>
#include "FlatShape.h"

using namespace sf;

class Flatland {
    public:
        // Constructors
        Flatland();
        Flatland(std::vector<FlatShape> shapes);
        // Offseters, setters and getters.
        void offsetRotation(const float &angle);
        void offsetPosition(const Vector2f &position);
        void setRotation(const float &angle);
        void setPosition(const Vector2f &position);
        float getRotation() const;
        Vector2f getPosition() const;
        // Adders and removing stuff from flatland:
        // TODO Can one access derived member functions from it?
        // TODO Add element IDs?
        void addShape(const FlatShape &shape);
        void removeShape();
        FlatShape& at(unsigned int i);
        // Draw function
        void draw();
        // Test drawing 3d rect. Must be called after draw()
        void draw3DRect(const float &angle);
        // Draw HUD
        void drawHUD(const Font &myFont, RenderWindow* window);
    private:
        // Normalize angle prevents floating point errors in angle.
        void normalizeAngle();
        float _cameraAngle;
        Vector2f _cameraPosition;
        std::vector<FlatShape> _population;
};

#endif
