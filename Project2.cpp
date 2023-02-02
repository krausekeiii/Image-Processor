#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "TGA_Header.h"
#include "Pixels.h"
#include "Image.h"
using namespace std;

void Subtract(Image bottom, Image top, vector<Pixels> newPixVector) {
    for (unsigned int i = 0; i < top.imagePix.size(); i++) {
        unsigned char newRed;
        if (bottom.imagePix.at(i).RedVal() - top.imagePix.at(i).RedVal() < 0)
            newRed = 0;

        else
            newRed = bottom.imagePix.at(i).RedVal() - top.imagePix.at(i).RedVal();

        unsigned char newGreen;
        if (bottom.imagePix.at(i).GreenVal() - top.imagePix.at(i).GreenVal() < 0)
            newGreen = 0;
        else
            newGreen = bottom.imagePix.at(i).GreenVal() - top.imagePix.at(i).GreenVal();
        unsigned char newBlue;
        if (bottom.imagePix.at(i).BlueVal() - top.imagePix.at(i).BlueVal() < 0)
            newBlue = 0;
        else
            newBlue = bottom.imagePix.at(i).BlueVal() - top.imagePix.at(i).BlueVal();

        Pixels newPix(newRed, newGreen, newBlue);
        newPixVector.push_back(newPix);
    }
}

void Multiply(Image image1, Image image2, vector<Pixels> multipliedPix) {
    for (unsigned int i = 0; i < image1.imagePix.size(); i++) {
        float newRed = (image1.imagePix.at(i).RedVal() / 255) * (image2.imagePix.at(i).RedVal() / 255);			//scaling to val 0-1
        newRed *= 255;															                                //rescaling to val 0-255
        newRed += 0.5f;															                                //for truncating issues when converting back to char

        float newGreen = (image1.imagePix.at(i).GreenVal() / 255) * (image2.imagePix.at(i).GreenVal() / 255);
        newGreen *= 255;
        newGreen += 0.5f;

        float newBlue = (image1.imagePix.at(i).BlueVal() / 255) * (image2.imagePix.at(i).BlueVal() / 255);
        newBlue *= 255;
        newBlue += 0.5f;

        Pixels newPix(newRed, newGreen, newBlue);
        multipliedPix.push_back(newPix);
    }
}

void Overlay(Image top, Image bottom, vector<Pixels>overlayedPix) {
    for (unsigned int i = 0; i < top.imagePix.size(); i++) {
        float redTop = (float)top.imagePix.at(i).RedVal() / 255;
        float redBottom = (float)bottom.imagePix.at(i).RedVal() / 255;
        float newRed;
        if (redBottom < 0.5f) {
            newRed = 2 * redTop * redBottom;
            newRed *= 255;
            newRed += 0.5f;
        }
        else {
            newRed = 1 - (2 * ((1 - redTop) * (1 - redBottom)));
            newRed *= 255;
            newRed += 0.5f;
        }

        float greenTop = (float)top.imagePix.at(i).GreenVal() / 255;
        float greenBottom = (float)bottom.imagePix.at(i).GreenVal() / 255;
        float newGreen;
        if (greenBottom < 0.5f) {
            newGreen = 2 * greenTop * greenBottom;
            newGreen *= 255;
            newGreen += 0.5f;
        }
        else {
            newGreen = 1 - (2 * ((1 - greenTop) * (1 - greenBottom)));
            newGreen *= 255;
            newGreen += 0.5f;
        }

        float blueTop = (float)top.imagePix.at(i).BlueVal() / 255;
        float blueBottom = (float)bottom.imagePix.at(i).BlueVal() / 255;
        float newBlue;
        if (blueBottom < 0.5f) {
            newBlue = 2 * blueTop * blueBottom;
            newBlue *= 255;
            newBlue += 0.5f;
        }
        else {
            newBlue = 1 - (2 * ((1 - blueTop) * (1 - blueBottom)));
            newBlue *= 255;
            newBlue += 0.5f;
        }

        Pixels newPix((unsigned char)newRed, (unsigned char)newGreen, (unsigned char)newBlue);
        overlayedPix.push_back(newPix);
    }
}

void Screen(Image image1, Image image2, vector<Pixels> screenedPix) {
    for (unsigned int i = 0; i < image1.imagePix.size(); i++) {
        float red1 = image1.imagePix.at(i).RedVal() / 255;
        float red2 = image2.imagePix.at(i) / 255;
        float newRed = 1 - ((1 - red1) * (1 - red2));
        newRed *= 255;
        newRed += 0.5f;

        float blue1 = image1.imagePix.at(i).BlueVal() / 255;
        float blue2 = image2.imagePix.at(i).BlueVal() / 255;
        float newBlue = 1 - ((1 - blue1) * (1 - blue2));
        newBlue *= 255;
        newBlue += 0.5f;

        float green1 = image1.imagePix.at(i).GreenVal() / 255;
        float green2 = image2.imagePix.at(i).GreenVal() / 255;
        float newGreen = 1 - ((1 - green1) * (1 - green2));
        newGreen *= 255;
        newGrenn += 0.5f;

        Pixels newPix((unsigned char)newRed, (unsigned char)newGreen, (unsigned char)newBlue);
        screenedPix.push_back(newPix);
    }
}

void Add(Image image, vector<Pixels> newColor) {
    for (unsigned int i = 0; i < image.imagePix.size(); i++) {
        unsigned char newRed = image.imagePix.at(i).RedVal();
        unsigned char newGreen = image.imagePix.at(i).GreenVal();
        unsigned char newBlue = image.imagePix.at(i).BlueVal();

        if (newGreen > 50) {
            newGreen = 250;
        }
        else {
            newGreen += 200;
        }

        Pixels newPix(newRed, newGreen, newBlue);
        newColor.push_back(newPix);
    }
}

void Scale(Image image, vector<Pixels> newColor) {
    for (unsigned int i = 0; i < image.imagePix.size(); i++) {
        float red = (float)image.imagePix.at(i).RedVal() / 255;
        float green = (float)image.imagePix.at(i).GreenVal() / 255;
        unsigned char blue = image.imagePix.at(i).BlueVal();

        float newRed = red * 4;
        newRed *= 255;
        newRed += 0.5f;
        float newGreen = green * 0;

        Pixels newPix((unsigned char)newRed, (unsigned char)newGreen, blue);
        newColor.push_back(newPix);
    }
}

int main()
{
    /*==================Part ONE============================================================================================================*/
    Header layer1Head;                  //top
    vector<Pixels> layer1Pix;           //layer1 pixel vector
    Image layer1I;                       
    Header pattern1Head;                //bottom
    vector<Pixels> pattern1Pix;         //pattern1 pixel vector
    Image pattern1I;                     

    fstream layer1("input/layer1.tga", ios_base::binary);
    
    //READING HEADER FOR LAYER 1
    layer1.read(&layer1Head.idLength, sizeof(layer1Head.idLength));
    layer1.read(&layer1Head.colorMapType, sizeof(layer1Head.colorMapType));
    layer1.read(&layer1Head.dataTypeCode, sizeof(layer1Head.dataTypeCode));
    layer1.read((char*)&layer1Head.colorMapOrigin, sizeof(layer1Head.colorMapOrigin)); 
    layer1.read((char*)&layer1Head.colorMapDepth, sizeof(layer1Head.colorMapDepth));   
    layer1.read(&layer1Head.colorMapLength, sizeof(layer1Head.colorMapLength));
    layer1.read((char*)&layer1Head.xOrigin, sizeof(layer1Head.xOrigin));               
    layer1.read((char*)&layer1Head.yOrigin, sizeof(layer1Head.yOrigin));               
    layer1.read((char*)&layer1Head.width, sizeof(layer1Head.width));                   
    layer1.read((char*)&layer1Head.height, sizeof(layer1Head.height));                 
    layer1.read(&layer1Head.bitsPerPixel, sizeof(layer1Head.bitsPerPixel));
    layer1.read(&layer1Head.imageDescriptor, sizeof(layer1Head.imageDescriptor));

    //READING PIXEL INFO FOR LAYER 1
    unsigned int pixelCount1 = layer1Head.width * layer1Head.height;

    for (unsigned int i = 0; i < pixelCount1; i++) {
        unsigned char tempRed;
        unsigned char tempBlue;
        unsigned char tempGreen;

        layer1.read(&tempBlue, 8);
        layer1.read(&tempGreen, 8);
        layer1.read(&tempRed, 8);

        Pixels newPix(tempRed, tempGreen, tempBlue);
        layer1Pix.push_back(newPix);
    }

    layer1I(layer1Head, layer1Pix);

    layer1.close();

    fstream pattern1("input/pattern1.tga", ios_base::binary);

    //READING HEADER FOR PATTERN 1
    pattern1.read(&pattern1Head.idLength, sizeof(pattern1Head.idLength));
    pattern1.read(&pattern1Head.colorMapType, sizeof(pattern1Head.colorMapType));
    pattern1.read(&pattern1Head.dataTypeCode, sizeof(pattern1Head.dataTypeCode));
    pattern1.read((char*)&pattern1Head.colorMapOrigin, sizeof(pattern1Head.colorMapOrigin)); 
    pattern1.read((char*)&pattern1Head.colorMapDepth, sizeof(pattern1Head.colorMapDepth));   
    pattern1.read(&pattern1Head.colorMapLength, sizeof(pattern1Head.colorMapLength));
    pattern1.read((char*)&pattern1Head.xOrigin, sizeof(pattern1Head.xOrigin));               
    pattern1.read(char*)(&pattern1Head.yOrigin, sizeof(pattern1Head.yOrigin));               
    pattern1.read((char*)&pattern1Head.width, sizeof(pattern1Head.width));                   
    pattern1.read((char*)&pattern1Head.height, sizeof(pattern1Head.height));                 
    pattern1.read(&pattern1Head.bitsPerPixel, sizeof(pattern1Head.bitsPerPixel));
    pattern1.read(&pattern1Head.imageDescriptor, sizeof(pattern1Head.imageDescriptor));

    //READING PIXEL INFO FOR PATTERN 1
    unsigned int pixelCount2 = pattern1Head.width * pattern1Head.height;

    for (unsigned int i = 0; i < pixelCount2; i++) {
        unsigned char tempRed;
        unsigned char tempGreen;
        unsigned char tempBlue;

        pattern1.read(&tempBlue, 8);
        pattern1.read(&tempGreen, 8);
        pattern1.read(&tempRed, 8);

        Pixels newPix(tempRed, tempGreen, tempBlue);
        pattern1Pix.push_back(newPix);
    }

    pattern1I(pattern1Head, pattern1Pix);

    pattern1.close();
    vector<Pixels> part1Pix;                        //vector to store new pixels
    Multiply(layer1I, pattern1I, part1Pix);
                                                     
    Header part1Header = layer1Head;

    //WRITING NEW DATA TO NEW FILE
    ofstream part1("output/part1.tga", ios_base::binary);

        //writing header
    part1.write(&part1Header.idLength, sizeof(char));
    part1.write(&part1Header.colorMapType, sizeof(char));
    part1.write(&part1Header.dataTypeCode, sizeof(char));
    part1.write((char*)&part1Header.colorMapOrigin, sizeof(short));
    part1.write((char*)&part1Header.colorMapLength, sizeof(short));
    part1.write(&part1Header.colorMapDepth, sizeof(char));
    part1.write((char*)&part1Header.xOrigin, sizeof(short));
    part1.write((char*)&part1Header.yOrigin, sizeof(short));
    part1.write((char*)&part1Header.width, sizeof(short));
    part1.write((char*)&part1Header.height, sizeof(short));
    part1.write(&part1Header.bitsPerPixel, sizeof(char));
    part1.write(&part1Header.imageDescriptor, sizeof(char));



        //writing PIXEL info
    Pixels task1;
    for (unsigned int i = 0; i < part1Pix.size(); i++) {
        part1.write(&part1Pix.at(i).BlueVal(), 8);
        part1.write(&part1Pix.at(i).GreenVal(), 8);
        part1.write(&part1Pix.at(i).RedVal(), 8);
    }
    part1.close();

    /*====================PART 2=============================================================================================================*/
    Header layer2Head;
    vector<Pixels> layer2Pix;
    Image layer2I;
    Header carHead;
    vector<Pixels> carPix;
    Image carI;

    ifstream layer2("input/layer2.tga", ios_base::binary);

    //READING HEADER FROM LAYER 2
    layer2.read(&layer2Head.idLength, sizeof(layer2Head.idLength));
    layer2.read(&layer2Head.colorMapType, sizeof(layer2Head.colorMapType));
    layer2.read(&layer2Head.dataTypeCode, sizeof(layer2Head.dataTypeCode));
    layer2.read((char*)&layer2Head.colorMapOrigin, sizeof(layer2Head.colorMapOrigin));     
    layer2.read((char*)&layer2Head.colorMapLength, sizeof(layer2Head.colorMapLength));     
    layer2.read(&layer2Head..colorMapDepth, sizeof(layer2Head.colorMapDepth));
    layer2.read((char*)&layer2Head.xOrigin, sizeof(layer2Head.xOrigin));                   
    layer2.read((char*)&layer2Head.yOrigin, sizeof(layer2Head.yOrigin));                   
    layer2.read((char*)&layer2Head.width, sizeof(layer2Head.width));                       
    layer2.read((char*)&layer2Head.height, sizeof(layer2Head.height));                     
    layer2.read(&layer2Head.bitsPerPixel, sizeof(layer2Head.bitsPerPixel));
    layer2.read(&layer2Head.imageDescriptor, sizeof(layer2Head.imageDescriptor));

    //READING PIXEL INFO FOR LAYER 2
    pixelCount1 = layer2Head.width * layer2Head.height;

    for (unsigned int i = 0, i < pixelCount1; i++) {
        unsigned char tempRed;
        unsigned char tempGreen;
        unsigned char tempBlue;

        layer2.read(&tempBlue, 8);
        layer2.read(&tempGreen, 8);
        layer2.read(&tempRed, 8);

        Pixels newPix(tempRed, tempGreen, tempBlue);
        layer2Pix.push_back(newPix);
    }

    layer2I(layer2Head, layer2Pix);

    layer2.close();
    
    ifstream car("input/car.tga", ios_base::binary);

    //READING HEADER FROM CAR
    car.read(&carHead.idLength, sizeof(carHead.idLength));
    car.read(&carHead.colorMapType, sizeof(carHead.colorMapType));
    car.read(&carHead.dataTypeCode, sizeof(carHead.dataTypeCode));
    car.read((char*)&carHead.colorMapOrigin, sizeof(carHead.colorMapOrigin));              
    car.read((char*)&carHead.colorMapLength, sizeof(carHead.colorMapLength));              
    car.read(&carHead.colorMapDepth, sizeof(carHead.colorMapDepth));
    car.read((char*)&carHead.xOrigin, sizeof(carHead.xOrigin));                            
    car.read((char*)&carHead.yOrigin, sizeof(carHead.yOrigin));                            
    car.read((char*)&carHead.width, sizeof(carHead.width));                                
    car.read((char*)&carHead.height, sizeof(carHead.height));                              
    car.read(&carHead.bitsPerPixel, sizeof(carHead.bitsPerPixel));
    car.read(&carHead.imageDescriptor, sizeof(carHead.imageDescriptor));

    //READING PIXEL INFO FOR CAR
    pixelCount2 = carHead.width * carHead.height;

    for (unsigned int i = 0; i < pixelCount2; i++) {
        unsigned char tempRed;
        unsigned char tempGreen;
        unsigned char tempBlue;

        car.read(&tempBlue, 8);
        car.read(&tempGreen, 8);
        car.read(&tempRed, 8);

        Pixels newPix(tempRed, tempGreen, tempBlue);
        carPix.push_back(newPix);
    }

    carI(carHead, carPix);
    car.close();

    //SUBTRACTING CAR - LAYER2
    vector<Pixels> part2Pix;
    Subtract(carI, layer2I, part2Pix);

    ofstream part2("output/part2.tga", ios_base::binary);
    
    //Writing new file header
    Header part2Header = layer2Head;
    part2.write(&part2Header.idLength, sizeof(char));
    part2.write(&part2Header.colorMapType, sizeof(char));
    part2.write(&part2Header.dataTypeCode, sizeof(char));
    part2.write((char*)&part2Header.colorMapOrigin, sizeof(short));
    part2.write((char*)&part2Header.colorMapLength, sizeof(short));
    part2.write(&part2Header.colorMapDepth, sizeof(char));
    part2.write((char*)&part2Header.xOrigin, sizeof(short));
    part2.write((char*)&part2Header.yOrigin, sizeof(short));
    part2.write((char*)&part2Header.width, sizeof(short));
    part2.write((char*)&part2Header.height, sizeof(short));
    part2.write(&part2Header.bitsPerPixel, sizeof(char));
    part2.write(&part2Header.imageDescriptor, sizeof(char));

    //Writing new file pixel info
    for (unsigned int i = 0; i < part2Pix.size(); i++) {
        part2.write(&part2Pix.at(i).BlueVal(), 8);
        part2.write(&part2Pix.at(i).GreenVal(), 8);
        part2.write(&part2Pix.at(i).RedVal(), 8);
    }

    part2.close();

    /*===========PART 3=====================================================================================================================*/
    Header pattern2Head;
    vector<Pixels> pattern2Pix;

    fstream pattern2("input/pattern2.tga", ios_base::binary);

    //READING HEADER FOR PATTERN 2
    pattern2.read(&pattern2Head.idLength, sizeof(pattern2Head.idLength));
    pattern2.read(&pattern2Head.colorMapType, sizeof(pattern2Head.colorMapType));
    pattern2.read(&pattern2Head.dataTypeCode, sizeof(pattern2Head.dataTypeCode));
    pattern2.read((char*)&pattern2Head.colorMapOrigin, sizeof(pattern2Head.colorMapOrigin));   
    pattern2.read((char*)&pattern2Head.colorMapDepth, sizeof(pattern2Head.colorMapDepth));     
    pattern2.read(&pattern2Head.colorMapLength, sizeof(pattern2Head.colorMapLength));
    pattern2.read((char*)&pattern2Head.xOrigin, sizeof(pattern2Head.xOrigin));                 
    pattern2.read((char*)&pattern2Head.yOrigin, sizeof(pattern2Head.yOrigin));                 
    pattern2.read((char*)&pattern2Head.width, sizeof(pattern2Head.width));                     
    pattern2.read((char*)&pattern2Head.height, sizeof(pattern2Head.height));                   
    pattern2.read(&pattern2Head.bitsPerPixel, sizeof(pattern2Head.bitsPerPixel));
    pattern2.read(&pattern2Head.imageDescriptor, sizeof(pattern2Head.imageDescriptor));

    //READING PIXEL INFO FOR PATTERN 2
    pixelCount2 = pattern2Head.width * pattern2Head.height;

    for (unsigned int i = 0; i < pixelCount2; i++) {
        unsigned char tempRed;
        unsigned char tempBlue;
        unsigned char tempGreen;

        pattern2.read(*tempBlue, 8);
        pattern2.read(&tempGreen, 8);
        pattern2.read(&tempRed, 8);

        Pixels newPix(tempRed, tempGreen, tempBlue);
        pattern2Pix.push_back(newPix);
    }

    Image pattern2I(pattern2Head, pattern2Pix);
    pattern2.close();

    //Storing image1*image2 in vector "part3Pix"
    vector<Pixels> part3Pix_p1;
    Multiply(layer1I, pattern2I, part3Pix_p1);
    Image part3_p1I(pattern2Head, part3Pix_p1);

    ifstream text("input/text.tga", ios_base::binary);
    Header textHead;
    vector<Pixels> textPix;

    //Reading header for text
    text.read(&textHead.idLength, sizeof(textHead.idLength);
    text.read(&textHead.colorMapType, sizeof(textHead.colorMapType);
    text.read(&textHead.dataTypeCode, sizeof(textHead.dataTypeCode));
    text.read((char*)&textHead.colorMapOrigin, sizeof(textHead.colorMapOrigin));           
    text.read((char*)&textHead.colorMapLength, sizeof(textHead.colorMapLength));           
    text.read(&textHead.colorMapDepth, sizeof(textHead.colorMapDepth));
    text.read((char*)&textHead.xOrigin, sizeof(textHead.xOrigin));                         
    text.read((char*)&textHead.yOrigin, sizeof(textHead.yOrigin));                         
    text.read((char*)&textHead.width, sizeof(textHead.width));                             
    text.read((char*)&textHead.height, sizeof(textHead.height));                           
    text.read(&textHead.bitsPerPixel, sizeof(textHead.bitsPerPixel));
    text.read(&textHead.imageDescriptor, sizeof(textHead.imageDescriptor));

    unsigned int textSize = textHead.width * textHead.height;

    //Reading Pixels for text
    for (unsigned int i = 0; i < textSize; i++) {
        unsigned char tempRed;
        unsigned char tempGreen;
        unsigned char tempBlue;

        text.read(&tempBlue, 8);
        text.read(&tempGreen, 8);
        text.read(&tempRed, 8);

        Pixels newPix(tempRed, tempGreen, tempBlue);
        textPix.push_back(newPix);
    }

    Image textI(textHead, textPix);

    text.close();

    //Screening textColors and image1*image2, storing in task3Final Pixels vector

    vector<Pixels> task3Final;
    Screen(part3_p1I, textI, task3Final);

    ofstream part3("output/part3.tga", ios_base::binary);
    Header part3Header = textHead;

    //Writing Header out to part3
    part3.write(&part3Header.idLength, sizeof(char));
    part3.write(&part3Header.colorMapType, sizeof(char));
    part3.write(&part3Header.dataTypeCode, sizeof(char));
    part3.write((char*)&part3Header.colorMapOrigin, sizeof(short));
    part3.write((char*)&part3Header.colorMapLength, sizeof(short));
    part3.write(&part3Header.colorMapDepth, sizeof(char));
    part3.write((char*)&part3Header.xOrigin, sizeof(short));
    part3.write((char*)&part3Header.yOrigin, sizeof(short));
    part3.write((char*)&part3Header.width, sizeof(short));
    part3.write((char*)&part3Header.height, sizeof(short));
    part3.write(&part3Header.bitsPerPixel, sizeof(char));
    part3.write(&part3Header.imageDescriptor, sizeof(char));

    //Writing pixels out to part3
    for (unsigned int i = 0; i < task3Final.size(); i++) {
        part3.write(&task3Final.at(i).BlueVal(), 8);
        part3.write(&task3Final.at(i).GreenVal(), 8);
        part3.write(&task3Final.at(i).RedVal(), 8);
    }

    part3.close();
    

    /*===================PART 4============================================================================================================*/ 
    ifstream circles("input/circles.tga", ios_base::binary);
    Header circlesHead;
    vector<Pixels> circlesPix;

    //READING HEADER FROM CIRCLES
    circles.read(&circlesHead.idLength, sizeof(circlesHead.idLength));
    circles.read(&circlesHead.colorMapType, sizeof(circlesHead.colorMapType));
    circles.read(&circlesHead.dataTypeCode, sizeof(circlesHead.dataTypeCode));
    circles.read((char*)&circlesHead.colorMapOrigin, sizeof(circlesHead.colorMapOrigin));
    circles.read((char*)&circlesHead.colorMapLength, sizeof(circlesHead.colorMapLength));
    circles.read(&circlesHead..colorMapDepth, sizeof(circlesHead.colorMapDepth));
    circles.read((char*)&circlesHead.xOrigin, sizeof(circlesHead.xOrigin));
    circles.read((char*)&circlesHead.yOrigin, sizeof(circlesHead.yOrigin));
    circles.read((char*)&circlesHead.width, sizeof(circlesHead.width));
    circles.read((char*)&circlesHead.height, sizeof(circlesHead.height));
    circles.read(&circlesHead.bitsPerPixel, sizeof(circlesHead.bitsPerPixel));
    circles.read(&circlesHead.imageDescriptor, sizeof(circlesHead.imageDescriptor));

    //READING PIXEL INFO FOR CIRCLES
    pixelCount2 = circlesHead.width * circlesHead.height;

    for (unsigned int i = 0, i < pixelCount2; i++) {
        unsigned char tempRed;
        unsigned char tempGreen;
        unsigned char tempBlue;

        circles.read(&tempBlue, 8);
        circles.read(&tempGreen, 8);
        circles.read(&tempRed, 8);

        Pixels newPix(tempRed, tempGreen, tempBlue);
        circlesPix.push_back(newPix);
    }

    Image circlesI(circlesHead, circlesPix);
    circles.close();

    //Storing image1*image2 in vector "part4_p1"
    vector<Pixels> part4_p1;
    Multiply(layer2I, circlesI, part4_p1);

    //CREATING IMAGE FOR circles*layer2
    Header part4_p1Head = layer2Head;
    Image part4_p1I(part4_p1Head, part4_p1);
   
    //Subtracting pattern2  - layer2*circles
    vector<Pixels> part4Pix;
    Subtract(part4_p1I, circlesI, part4Pix);


    ofstream part4("output/part4.tga", ios_base::binary);

    Header part4Header = part4_p1Head;
    //Writing out header
    part4.write(&part4Header.idLength, sizeof(char));
    part4.write(&part4Header.colorMapType, sizeof(char));
    part4.write(&part4Header.dataTypeCode, sizeof(char));
    part4.write((char*)&part4Header.colorMapOrigin, sizeof(short));
    part4.write((char*)&part4Header.colorMapLength, sizeof(short));
    part4.write(&part4Header.colorMapDepth, sizeof(char));
    part4.write((char*)&part4Header.xOrigin, sizeof(short));
    part4.write((char*)&part4Header.yOrigin, sizeof(short));
    part4.write((char*)&part4Header.width, sizeof(short));
    part4.write((char*)&part4Header.height, sizeof(short));
    part4.write(&part4Header.bitsPerPixel, sizeof(char));
    part4.write(&part4Header.imageDescriptor, sizeof(char));

    //Writing out PIX info
    for (unsigned int i = 0; i < part4Pix.size() ; i++) {
        part4.write(&part4Pix.at(i).BlueVal(), 8);
        part4.write(&part4Pix.at(i).GreenVal(), 8);
        part4.write(&part4Pix.at(i).RedVal(), 8);
    }

    part4.close();

    /*=================PART 5=============================================================================================================*/
    vector<Pixels> part5Pix;
    Header part5Header = layer1Head;

    Overlay(layer1I, pattern1I, part5Pix);

    //writing out part5 to new file
    ofstream part5("output / part5.tga", ios_base::binary);

    part5.write(&part5Header.idLength, sizeof(char));
    part5.write(&part5Header.colorMapType, sizeof(char));
    part5.write(&part5Header.dataTypeCode, sizeof(char));
    part5.write((char*)&part5Header.colorMapOrigin, sizeof(short));
    part5.write((char*)&part5Header.colorMapLength, sizeof(short));
    part5.write(&part5Header.colorMapDepth, sizeof(char));
    part5.write((char*)&part5Header.xOrigin, sizeof(short));
    part5.write((char*)&part5Header.yOrigin, sizeof(short));
    part5.write((char*)&part5Header.width, sizeof(short));
    part5.write((char*)&part5Header.height, sizeof(short));
    part5.write(&part5Header.bitsPerPixel, sizeof(char));
    part5.write(&part5Header.imageDescriptor, sizeof(char));

    //Writing out PIX info
    for (unsigned int i = 0; i < part5Pix.size(); i++) {
        part5.write(&part5Pix.at(i).BlueVal(), 8);
        part5.write(&part5Pix.at(i).GreenVal(), 8);
        part5.write(&part5Pix.at(i).RedVal(), 8);
    }

    part5.close();

    /*====================PART 6==============================================================================================================*/
    
    vector<Pixels> part6Pix;
    Add(carI, part6Pix);

    ofstream part6("output/part6", ios_base::binary);
    Header part6Header = carHead;

    part6.write(&part6Header.idLength, sizeof(char));
    part6.write(&part6Header.colorMapType, sizeof(char));
    part6.write(&part6Header.dataTypeCode, sizeof(char));
    part6.write((char*)&part6Header.colorMapOrigin, sizeof(short));
    part6.write((char*)&part6Header.colorMapLength, sizeof(short));
    part6.write(&part6Header.colorMapDepth, sizeof(char));
    part6.write((char*)&part6Header.xOrigin, sizeof(short));
    part6.write((char*)&part6Header.yOrigin, sizeof(short));
    part6.write((char*)&part6Header.width, sizeof(short));
    part6.write((char*)&part6Header.height, sizeof(short));
    part6.write(&part6Header.bitsPerPixel, sizeof(char));
    part6.write(&part6Header.imageDescriptor, sizeof(char));

    //Writing out PIX info
    for (unsigned int i = 0; i < part6Pix.size(); i++) {
        part6.write(&part6Pix.at(i).BlueVal(), 8);
        part6.write(&part6Pix.at(i).GreenVal(), 8);
        part6.write(&part6Pix.at(i).RedVal(), 8);
    }

    part6.close();

    /*=====================PART 7=================================================================================================================*/

    vector<Pixels> part7Pix;
    Header part7Header = carHead;
    Scale(carI, part7Pix);

    ofstream part7("output/part7.tga", ios_base::binary);

    part7.write(&part7Header.idLength, sizeof(char));
    part7.write(&part7Header.colorMapType, sizeof(char));
    part7.write(&part7Header.dataTypeCode, sizeof(char));
    part7.write((char*)&part7Header.colorMapOrigin, sizeof(short));
    part7.write((char*)&part7Header.colorMapLength, sizeof(short));
    part7.write(&part7Header.colorMapDepth, sizeof(char));
    part7.write((char*)&part7Header.xOrigin, sizeof(short));
    part7.write((char*)&part7Header.yOrigin, sizeof(short));
    part7.write((char*)&part7Header.width, sizeof(short));
    part7.write((char*)&part7Header.height, sizeof(short));
    part7.write(&part7Header.bitsPerPixel, sizeof(char));
    part7.write(&part7Header.imageDescriptor, sizeof(char));

    //Writing out PIX info
    for (unsigned int i = 0; i < part7Pix.size(); i++) {
        part7.write(&part7Pix.at(i).BlueVal(), 8);
        part7.write(&part7Pix.at(i).GreenVal(), 8);
        part7.write(&part7Pix.at(i).RedVal(), 8);
    }

    part7.close();

    /*=======================PART 8====================================================================================================================*/

    //RED
    ofstream part8_r("output/part8_r.tga", ios_base::binary);
    Header part8_rHeader = carHead;
    
    part8_r.write(&part8_rHeader.idLength, sizeof(char));
    part8_r.write(&part8_rHeader.colorMapType, sizeof(char));
    part8_r.write(&part8_rHeader.dataTypeCode, sizeof(char));
    part8_r.write((char*)&part8_rHeader.colorMapOrigin, sizeof(short));
    part8_r.write((char*)&part8_rHeader.colorMapLength, sizeof(short));
    part8_r.write(&part8_rHeader.colorMapDepth, sizeof(char));
    part8_r.write((char*)&part8_rHeader.xOrigin, sizeof(short));
    part8_r.write((char*)&part8_rHeader.yOrigin, sizeof(short));
    part8_r.write((char*)&part8_rHeader.width, sizeof(short));
    part8_r.write((char*)&part8_rHeader.height, sizeof(short));
    part8_r.write(&part8_rHeader.bitsPerPixel, sizeof(char));
    part8_r.write(&part8_rHeader.imageDescriptor, sizeof(char));

    //Writing out PIX info
    unsigned char blueVal = 0;
    unsigned char greenVal = 0;
    for (unsigned int i = 0; i < carPix.size(); i++) {
        part8_r.write(&blueVal, 8);
        part8_r.write(&greenVal, 8);
        part8_r.write(&carPix.at(i).RedVal(), 8);
    }

    part8_r.close();

    //GREEN
    Header part8_gHeader = carHead;
    ofstream part8_g("output/part8_g.tga", ios_base::binary);

    part8_g.write(&part8_gHeader.idLength, sizeof(char));
    part8_g.write(&part8_gHeader.colorMapType, sizeof(char));
    part8_g.write(&part8_gHeader.dataTypeCode, sizeof(char));
    part8_g.write((char*)&part8_gHeader.colorMapOrigin, sizeof(short));
    part8_g.write((char*)&part8_gHeader.colorMapLength, sizeof(short));
    part8_g.write(&part8_gHeader.colorMapDepth, sizeof(char));
    part8_g.write((char*)&part8_gHeader.xOrigin, sizeof(short));
    part8_g.write((char*)&part8_gHeader.yOrigin, sizeof(short));
    part8_g.write((char*)&part8_gHeader.width, sizeof(short));
    part8_g.write((char*)&part8_gHeader.height, sizeof(short));
    part8_g.write(&part8_gHeader.bitsPerPixel, sizeof(char));
    part8_g.write(&part8_gHeader.imageDescriptor, sizeof(char));

    //Writing out PIX info
    unsigned char blueVal = 0;
    unsigned char redVal = 0;
    for (unsigned int i = 0; i < carPix.size(); i++) {
        part8_g.write(&blueVal, 8);
        part8_g.write(&carPix.at(i).GreenVal(), 8);
        part8_g.write(&redVal, 8);
    }
    part8_g.close();

    //BLUE
    Header part8_bHeader = carHead;
    ofstream part8_b("output/part8_b.tga", ios_base::binary);

    part8_b.write(&part8_bHeader.idLength, sizeof(char));
    part8_b.write(&part8_bHeader.colorMapType, sizeof(char));
    part8_b.write(&part8_bHeader.dataTypeCode, sizeof(char));
    part8_b.write((char*)&part8_bHeader.colorMapOrigin, sizeof(short));
    part8_b.write((char*)&part8_bHeader.colorMapLength, sizeof(short));
    part8_b.write(&part8_bHeader.colorMapDepth, sizeof(char));
    part8_b.write((char*)&part8_bHeader.xOrigin, sizeof(short));
    part8_b.write((char*)&part8_bHeader.yOrigin, sizeof(short));
    part8_b.write((char*)&part8_bHeader.width, sizeof(short));
    part8_b.write((char*)&part8_bHeader.height, sizeof(short));
    part8_b.write(&part8_bHeader.bitsPerPixel, sizeof(char));
    part8_b.write(&part8_bHeader.imageDescriptor, sizeof(char));

    //Writing out PIX info
    unsigned char greenVal = 0;
    unsigned char redVal = 0;
    for (unsigned int i = 0; i < carPix.size(); i++) {
        part8_g.write(&carPix.at(i).BlueVal(), 8);
        part8_g.write(&greenVal, 8);
        part8_g.write(&redVal, 8);
    }
    part8_b.close();

    /*===================PART 9========================================================================================================*/

    //LAYER_RED
    Header layer_redHead;
    vector<Pixels> layer_redPix;

    ifstream layer_red("input/layer_red.tga", ios_base::binary);

    //READING HEADER FOR LAYER_RED
    layer_red.read(&layer_redHead.idLength, sizeof(char));
    layer_red.read(&layer_redHead.colorMapType, sizeof(char));
    layer_red.read(&layer_redHead.dataTypeCode, sizeof(char));
    layer_red.read((char*)&layer_redHead.colorMapOrigin, sizeof(short));
    layer_red.read((char*)&layer_redHead.colorMapDepth, sizeof(short));
    layer_red.read(&layer_redHead.colorMapLength, sizeof(char));
    layer_red.read((char*)&layer_redHead.xOrigin, sizeof(short));
    layer_red.read((char*)&layer_redHead.yOrigin, sizeof(short));
    layer_red.read((char*)&layer_redHead.width, sizeof(short));
    layer_red.read((char*)&layer_redHead.height, sizeof(short));
    layer_red.read(&layer_redHead.bitsPerPixel, sizeof(char));
    layer_red.read(&layer_redHead.imageDescriptor, sizeof(char));

    //READING PIXEL INFO FOR LAYER_RED
    unsigned int pixelCountRed = layer_redHead.width * layer_redHead.height;

    for (unsigned int i = 0; i < pixelCountRed; i++) {
        unsigned char tempRed;
        unsigned char tempBlue;
        unsigned char tempGreen;

        layer_red.read(&tempBlue, 8);
        layer_red.read(&tempGreen, 8);
        layer_red.read(&tempRed, 8);

        Pixels newPix(tempRed, tempGreen, tempBlue);
        layer_redPix.push_back(newPix);
    }

    layer_red.close();

    //LAYER_BLUE
    Header layer_blueHead;
    vector<Pixels> layer_bluePix;

    ifstream layer_blue("input/layer_blue.tga", ios_base::binary);

    //READING HEADER FOR LAYER_BLUE
    layer_blue.read(&layer_blueHead.idLength, sizeof(char));
    layer_blue.read(&layer_blueHead.colorMapType, sizeof(char));
    layer_blue.read(&layer_blueHead.dataTypeCode, sizeof(char));
    layer_blue.read((char*)&layer_blueHead.colorMapOrigin, sizeof(short));
    layer_blue.read((char*)&layer_blueHead.colorMapDepth, sizeof(short));
    layer_blue.read(&layer_blueHead.colorMapLength, sizeof(char));
    layer_blue.read((char*)&layer_blueHead.xOrigin, sizeof(short));
    layer_blue.read((char*)&layer_blueHead.yOrigin, sizeof(short));
    layer_blue.read((char*)&layer_blueHead.width, sizeof(short));
    layer_blue.read((char*)&layer_blueHead.height, sizeof(short));
    layer_blue.read(&layer_blueHead.bitsPerPixel, sizeof(char));
    layer_blue.read(&layer_blueHead.imageDescriptor, sizeof(char));

    //READING PIXEL INFO FOR LAYER_BLUE
    unsigned int pixelCountBlue = layer_blueHead.width * layer_blueHead.height;

    for (unsigned int i = 0; i < pixelCountBlue; i++) {
        unsigned char tempRed;
        unsigned char tempBlue;
        unsigned char tempGreen;

        layer_blue.read(&tempBlue, 8);
        layer_blue.read(&tempGreen, 8);
        layer_blue.read(&tempRed, 8);

        Pixels newPix(tempRed, tempGreen, tempBlue);
        layer_bluePix.push_back(newPix);
    }

    layer_blue.close();

    //LAYER_GREEN
    Header layer_greenHead;
    vector<Pixels> layer_greenPix;

    ifstream layer_green("input/layer_green.tga", ios_base::binary);

    //READING HEADER FOR LAYER_BLUE
    layer_green.read(&layer_greenHead.idLength, sizeof(char));
    layer_green.read(&layer_greenHead.colorMapType, sizeof(char));
    layer_green.read(&layer_greenHead.dataTypeCode, sizeof(char));
    layer_green.read((char*)&layer_greenHead.colorMapOrigin, sizeof(short));
    layer_green.read((char*)&layer_greenHead.colorMapDepth, sizeof(short));
    layer_green.read(&layer_greenHead.colorMapLength, sizeof(char));
    layer_green.read((char*)&layer_greenHead.xOrigin, sizeof(short));
    layer_green.read((char*)&layer_greenHead.yOrigin, sizeof(short));
    layer_green.read((char*)&layer_greenHead.width, sizeof(short));
    layer_green.read((char*)&layer_greenHead.height, sizeof(short));
    layer_green.read(&layer_greenHead.bitsPerPixel, sizeof(char));
    layer_green.read(&layer_greenHead.imageDescriptor, sizeof(char));

    //READING PIXEL INFO FOR LAYER_BLUE
    unsigned int pixelCountGreen = layer_greenHead.width * layer_greenHead.height;

    for (unsigned int i = 0; i < pixelCountGreen; i++) {
        unsigned char tempRed;
        unsigned char tempBlue;
        unsigned char tempGreen;

        layer_green.read(&tempBlue, 8);
        layer_green.read(&tempGreen, 8);
        layer_green.read(&tempRed, 8);

        Pixels newPix(tempRed, tempGreen, tempBlue);
        layer_greenPix.push_back(newPix);
    }

    layer_green.close();

    //WRITING OUT COMBINED FILE
    ofstream part9("output/part9.tga", ios_base::binary);
    Header part9Header = layer_redHead;

    part9.write(&part9Header.idLength, sizeof(char));
    part9.write(&part9Header.colorMapType, sizeof(char));
    part9.write(&part9Header.dataTypeCode, sizeof(char));
    part9.write((char*)&part9Header.colorMapOrigin, sizeof(short));
    part9.write((char*)&part9Header.colorMapLength, sizeof(short));
    part9.write(&part9Header.colorMapDepth, sizeof(char));
    part9.write((char*)&part9Header.xOrigin, sizeof(short));
    part9.write((char*)&part9Header.yOrigin, sizeof(short));
    part9.write((char*)&part9Header.width, sizeof(short));
    part9.write((char*)&part9Header.height, sizeof(short));
    part9.write(&part9Header.bitsPerPixel, sizeof(char));
    part9.write(&part9Header.imageDescriptor, sizeof(char));

    //Writing out PIX info
    for (unsigned int i = 0; i < layer_redPix.size(); i++) {
        part9.write(&layer_bluePix.at(i).BlueVal(), 8);
        part9.write(&layer_greenPix.at(i).GreenVal(), 8);
        part9.write(&layer_redPix.at(i).RedVal(), 8);
    }
    part9.close();

    /*====================PART 10(woohoo)==================================================================================================*/

    ifstream text2("input/text2.tga", ios_base::binary);
    Header text2Head;
    vector<Pixels> text2Pix;

    //Reading header for text2
    text2.read(&text2Head.idLength, sizeof(text2Head.idLength);
    text2.read(&text2Head.colorMapType, sizeof(text2Head.colorMapType);
    text2.read(&text2Head.dataTypeCode, sizeof(text2Head.dataTypeCode));
    text2.read((char*)&text2Head.colorMapOrigin, sizeof(text2Head.colorMapOrigin));
    text2.read((char*)&text2Head.colorMapLength, sizeof(text2Head.colorMapLength));
    text2.read(&text2Head.colorMapDepth, sizeof(text2Head.colorMapDepth));
    text2.read((char*)&text2Head.xOrigin, sizeof(text2Head.xOrigin));
    text2.read((char*)&text2Head.yOrigin, sizeof(text2Head.yOrigin));
    text2.read((char*)&text2Head.width, sizeof(text2Head.width));
    text2.read((char*)&text2Head.height, sizeof(text2Head.height));
    text2.read(&text2Head.bitsPerPixel, sizeof(text2Head.bitsPerPixel));
    text2.read(&text2Head.imageDescriptor, sizeof(text2Head.imageDescriptor));

    unsigned int text2Size = text2Head.width * text2Head.height;

    //Reading Pixels for text2
    for (unsigned int i = 0; i < text2Size; i++) {
        unsigned char tempRed;
        unsigned char tempGreen;
        unsigned char tempBlue;

        text2.read(&tempBlue, 8);
        text2.read(&tempGreen, 8);
        text2.read(&tempRed, 8);

        Pixels newPix(tempRed, tempGreen, tempBlue);
        text2Pix.push_back(newPix);
    }

    Image text2I(text2Head, text2Pix);

    vector<Pixels> part10Pix;

    for (unsigned int i = text2Pix.size() - 1; i >= 0; i++) {
        part10Pix.push_back(text2Pix.at(i));
    }

    ofstream part10("output/part10.tga", ios_base::binary);
    Header part10Header = text2Head;

    part10.write(&part10Header.idLength, sizeof(char));
    part10.write(&part10Header.colorMapType, sizeof(char));
    part10.write(&part10Header.dataTypeCode, sizeof(char));
    part10.write((char*)&part10Header.colorMapOrigin, sizeof(short));
    part10.write((char*)&part10Header.colorMapLength, sizeof(short));
    part10.write(&part10Header.colorMapDepth, sizeof(char));
    part10.write((char*)&part10Header.xOrigin, sizeof(short));
    part10.write((char*)&part10Header.yOrigin, sizeof(short));
    part10.write((char*)&part10Header.width, sizeof(short));
    part10.write((char*)&part10Header.height, sizeof(short));
    part10.write(&part10Header.bitsPerPixel, sizeof(char));
    part10.write(&part10Header.imageDescriptor, sizeof(char));

    //Writing out PIX info
    for (unsigned int i = 0; i < part10Pix.size(); i++) {
        part10.write(&part10Pix.at(i).BlueVal(), 8);
        part10.write(&part10Pix.at(i).GreenVal(), 8);
        part10.write(&part10Pix.at(i).RedVal(), 8);
    }

    part10.close();
}
