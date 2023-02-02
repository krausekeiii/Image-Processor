#pragma once
#include "Pixels.h"
#include "TGA_Header.h"
#include <vector>
using namespace std;


class Image {
public:
	Header imageHeader;
	vector<Pixels> imagePix;

	Image() {
		
	}

	Image(Header& fileHeader, vector<Pixels>& imagePixels) {
		imageHeader = fileHeader;
		imagePix = imagePixels;
	}
};