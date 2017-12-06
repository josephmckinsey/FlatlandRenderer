/* CSCI 261B : Final Project: WavefrontShape Declaration File 
 *
 * Description: Declares WavefrontShape class. WavefrontShape allows
 * wavefront .obj files to be loaded and drawn correctly in flatland.
 * It inherits from FlatShape, in order to be drawn in the Flatland
 * class.
 *
 * Author: Joseph McKinsey
 *
 */

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include "WavefrontShape.h"

// Initialize object shape with color. Ignores opacity.
// 3D coordinates must be used to create it.
// TODO: Improve rotation capabilities. Currently only allows for rotation along the axis outside of flatland.
WavefrontShape::WavefrontShape(Vector3f position, float scale, float rotation, std::ifstream &objFile, Color color) {
    _scale = scale;
    _rotation = rotation;
    _position = position;
    _color = color;
    // See helper function below.
    loadObj(objFile);
}

// Initialize wavefront without color. Chooses white as default. see above todo..
WavefrontShape::WavefrontShape(Vector3f position, float scale, float rotation, std::ifstream &objFile) {
    _scale = scale;
    _rotation = rotation;
    _position = position;
    _color = Color::White;
    loadObj(objFile);
}

// Get color
Color WavefrontShape::getColor() const {
    return _color;
}

// Set color. Ignores opacity.
void WavefrontShape::setColor(const Color& color) {
    _color = color;
    // Sets _outColors (which is actually used to be drawn by the FlatShape clsas).
    // with the necessary colors. Essentially, every vertex becomes just that color.
    for (unsigned int i = 0; i < _outColors.size(); i += 3) {
        _outColors.at(i) = color.r;
        _outColors.at(i + 1) = color.g;
        _outColors.at(i + 2) = color.b;
    }
}

// Load wavefront .obj file passed in from constructor. Crappy, minimal, barely functions. TODO
// Ignores textures. Ignores materials. Ignores groups. Can't handle quads without giving some crazy
// crazy crazy errors. Ignores new lines (most grievous mistake of all).
void WavefrontShape::loadObj(std::ifstream &objFile) {
    // Initialize numerous temporaro vectors.
    std::vector<Vector3f> vertices, normals;
    std::vector<unsigned int> vertexIndices, normalIndices;
    std::vector<float> outVertices, outNormals, outColors;
    // Initialize temporary variables for reading in from file.
    float x, y, z;
    std::string argument;
    
    // Check if file was opened correctly.
    if ( objFile.fail() ) {
        std::cerr << "Failed to read from file stream." << std::endl;
    }
    // Read in until stream empty.
    while (!objFile.eof()) {
        // Gets argument. Should always be first command on line. 
        objFile >> argument;
        if (argument.at(0) == '#') {
            // Gets rest of line: will only include /n if the argument was just #.
            // Discards output and continues to read next argument.
            std::getline(objFile, argument);
            continue;
        }
        else if (argument == "vt") {
            // Textures. Ignored.
            continue;
        }
        else if (argument == "vn") {
            // Normals. Saved in termorary vector.
            objFile >> x;
            objFile >> y;
            objFile >> z;
            normals.push_back(Vector3f(x, y, z));
        }
        else if (argument == "vp") {
            // Used for cool curves. Ignored.
            continue;
        }
        else if (argument == "v") {
            // Vertices.
            objFile >> x;
            objFile >> y;
            objFile >> z;
            vertices.push_back(Vector3f(x, y, z));
        }
        else if (argument == "f") {
            // Get triangle face..
            for (unsigned int i = 0; i < 3; i++) {
                // Gets first vertex. Of the form v/vt/vn. Some slashes
                // are ignored in some programs and not in others. Indices
                // are put between slashes.
                objFile >> argument;
                unsigned int slash1 = argument.find_first_of("//");
                unsigned int slash2 = argument.find_last_of("//");
                if (slash1 != 0 && slash1 != std::string::npos) {
                   vertexIndices.push_back(stoi(argument.substr(0, slash1)));
                }
                if (slash1 + 1 != slash2) {
                    // Would be texture one.
                    // stoi(argument.substr(slash1 + 1, slash2 - slash1 - 1));
                }
                if (slash2 != std::string::npos && slash1 != slash2) {
                    normalIndices.push_back(stoi(argument.substr(slash2 + 1)));
                }
            }
        }
    }
    // Close file.

    objFile.close();
    // Reorder outVertices and outColors with faces and all of that.
    for (unsigned int i = 0;  i < vertexIndices.size(); i++) {
        // add3 is a helper function that adds each element to outVertices.
        // -1 must be applied because .obj indices start at 1.
        add3(outVertices, vertices.at(vertexIndices.at(i)-1));
        // Must be divided by 255 because OpenGL has everything between 0 and 1.
        add3(outColors, _color.r / 255.0, _color.g / 255.0, _color.b / 255.0);
    }
    for (unsigned int i = 0; i < normalIndices.size(); i++) {
        // For all the normals that may (or may not exist). Similar to vertices
        // code above.
        add3(outNormals, normals.at(normalIndices.at(i)-1));
    }
    // Set class variables to these temporary holders. Makes it easier to identify
    // bugs.
    _outVertices = outVertices;
    _outNormals = outNormals;
    _outColors = outColors;
    return;
}
