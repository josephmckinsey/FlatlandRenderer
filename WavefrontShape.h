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

#ifndef WAVEFRONTSHAPE
#define WAVEFRONTSHAPE
#include <fstream>
#include "FlatShape.h"

using namespace sf;

// WavefrontShape inherits from FlatShape that handles all the drawing.
// TODO Add better rotation changing. Currently its very limited.
class WavefrontShape : public FlatShape {
    public:
        WavefrontShape(Vector3f position, float scale, float rotation, std::ifstream &objFile, Color color);
        WavefrontShape(Vector3f position, float scale, float rotation, std::ifstream &objFile);
        Color getColor() const;
        void setColor(const Color& color);
    private:
        // Helper function for loading wavefront .obj files.
        void loadObj(std::ifstream &objFile);
        Color _color;
};

#endif

