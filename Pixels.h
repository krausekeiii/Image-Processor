#pragma once
using namespace std;

class Pixels {
	unsigned char red, green, blue;

	Pixels() {
		red = 0;
		blue = 0;
		green = 0;
	}

	Pixels(unsigned char r,unsigned char g,unsigned char b) {
		red = r;
		blue = b;
		green = g;
	}
	
	unsigned char RedVal() {
		return red;
	}

	unsigned char GreenVal() {
		return green;
	}

	unsigned char BlueVal() {
		return blue;
	}

};

