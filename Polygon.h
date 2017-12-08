/* CSCI 261B : Final Project: Polygon Declaration File
 *
 * Description: Declares polygon class. Polygons are the people of flatland.
 * They are important. May consider making them have speech interaction
 * with the user.
 *
 * Author: Joseph McKinsey
 *
 */

#ifndef POLYGON
#define POLYGON
#include <SFML/Graphics.hpp>
#include "FlatShape.h"

using namespace sf;

// Inherits all drawing and moving requirements from the FlatShape base class.
class Polygon : public FlatShape {
    public:
        Polygon(Vector2f position, int sides, float radius, float rotation);
};

#endif
