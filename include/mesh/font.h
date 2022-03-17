/*
    - This class is made for easy importing of fonts into the 3D space it should be used in main (somehow :shrug: (that is still left for me to design))
*/

// klasa za pretvarjanje fontov v crke ki se lahko risejo na zaslon v sceni

#pragma once

#include <core.h>
#include <structs.h>
#include <util.h>
#include <vecCalc.h>
#include <mesh.h>

namespace ZWET
{
    struct CharInfo
    {
    	int id; //char id (have to find what the ids of chars are)
    	int x; //location of start of char (topleft of the char)
    	int y;
    	int width; //width and height of the char
    	int height;
    	int xoffset; //how much to offset the char on both axis
    	int yoffset;
    	int xadvance; //how much to move forward to the next position to palce the character
    	vec2 UV[4]; //UVs for the letter
    };

    class Font
    {
    	public:
    		Font(std::string fontFilePath, std::string fontPicturePath, int windowHeight, int windowWidth, float scale);

    		~Font();

    		void setLineWidth(int width);

    		void setScale(float scale);

    		mesh convertString(std::string text);

    	private:
    		int maxLineWidth; //width of a line
    		int imageResolution[2];
    		int windowHeight;
    		int windowWidth;
    		int lineHeight;
    		float scale;
    		std::string fontFilePath;
    		std::string fontPicturePath;
    		std::map<int, CharInfo> charMap;

    		void convertToUV(); //converts the data to uvs on the texture

    		void readFontFile(); //reads the .fnt file

    		mesh calculateMesh(std::string text); //calculate the size of the mesh
    };
}