/* CSCI 261B : Final Project: Polygon Class Implementation File
 *
 * Description: Implements the polygon class. Polygons are the people of flat-
 * land. They are important. May consider making them have speech interaction
 * with the user.
 *
 * Author: Joseph McKinsey
 *
 */

#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include "Polygon.h"

using namespace sf;

// Polygon constructor. TODO Consider better way to use position these around.
// Currently, the getters and setters must all use 3d coordinates (x, z, y)
Polygon::Polygon(Vector2f position, int sides, float radius, float rotation) {
    // Sets temporary angle to 0.
    float angle = 0;
    Vector2f vertex, normal;
    // Default scaling.
    _scale = 1;
    _rotation = rotation;
    // Map flatland position to nromal position.
    _position = Vector3f(position.x, position.y, 0);
    std::vector<Vector2f> vertices, normals;
    std::vector<float> outVertices, outNormals, outColors;

    // Create every vertex of the polygon. Also adds the correct normal for that side.
    // TODO Place normals by vertex directly for smooth shading.
    for (int i = 0; i < sides; i++) {
        vertex.y = radius * sin(angle);
        vertex.x = radius * cos(angle);
        vertices.push_back(vertex);
        normal.x = cos(angle + PI / sides);
        normal.y = sin(angle + PI / sides);
        normals.push_back(normal);
        angle += 2 * PI / sides;
    }
    // Add triangles. add3 simply adds each of the vertices to the passed in array.
    // The actual 3D object is an extension of all the vertices up and down 50.
    for (unsigned int i = 0; i < vertices.size() - 1; i++) {
        // First triangle must be drawn counter clockwise.
        add3(outVertices, vertices.at(i).x, 50.f, vertices.at(i).y);
        add3(outVertices, vertices.at(i).x, -50.f, vertices.at(i).y);
        add3(outVertices, vertices.at(i+1).x, -50.f, vertices.at(i+1).y);
        // Second triangleVertices must be drawn counter clockwise.
        add3(outVertices, vertices.at(i).x, 50.f, vertices.at(i).y);
        add3(outVertices, vertices.at(i+1).x, -50.f, vertices.at(i+1).y);
        add3(outVertices, vertices.at(i+1).x, 50.f, vertices.at(i+1).y);
        // Adds associated normals and colors. Faces are drawn red.
        for (unsigned j = 0; j < 6; j++) {
            add3(outNormals, normals.at(i).x, 0.f, normals.at(i).y);
            // Draws red color.
            add3(outColors, 1.f, 0.f, 0.f);
        }
    }
    // Adds last side to close the figure. Colors it green. This is the "face".
    add3(outVertices, vertices.back().x, 50.f, vertices.back().y);
    add3(outVertices, vertices.back().x, -50.f, vertices.back().y);
    add3(outVertices, vertices.front().x, -50.f, vertices.front().y);

    add3(outVertices, vertices.back().x, 50.f, vertices.back().y);
    add3(outVertices, vertices.front().x, -50.f, vertices.front().y);
    add3(outVertices, vertices.front().x, 50.f, vertices.front().y);
    // Adds final normals and colors.
    for (unsigned j = 0; j < 6; j++) {
        add3(outNormals, normals.back().x, 0.f, normals.back().y);
        // Green coloring.
        add3(outColors, 0.f, 1.f, 0.f);
    }
    // Applies temporary holder variables to the rest of the class.
    _outVertices = outVertices;
    _outNormals = outNormals;
    _outColors = outColors;
}

// Map of Flatland:
//          ^
//          |
//          y
//          |
//          |
//          |
// <--------x------->
