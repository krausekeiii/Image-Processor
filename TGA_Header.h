#pragma once
#include <iostream>
using namespace std;

struct Header {
	char idLength,				//size of image id field
		colorMapType,			//is color map included?  (don't think so)
		dataTypeCode;			//compressed, true color, grayscale?
	short colorMapOrigin,		//should be 0
		colorMapLength;			//0
	char colorMapDepth;			//0
	short xOrigin, yOrigin,		//0
		width, height;			//width and height of image
	char bitsPerPixel;			//should be 24 (8 bits for red, green, and blue)
	char imageDescriptor;		
};