#include "imageParam.h"
using namespace std;

imageParam::imageParam()
{
    numElement = 128;                                                            // initialize numElement to 128
    numSample = 3338;                                                            // initialize numSample to 3338
    numScanline = 127;                                                           // initialize numScanline to 127
    elementPosition = genElementPosition();                                      // initalize elementPosition with genElementPosition()
    scanlinePosition = genScanlinePosition(numScanline, PITCH, elementPosition); // initialize scanlinePosition with genScanlinePosition(numScanline, PITCH, elementPosition)
}

imageParam::~imageParam()
{
    deletePositionArray(); // call deletePositionArray() function
}

// Create an array containing the element location (in x-direction) of the ultrasound transducer
float *imageParam::genElementPosition()
{
    elementPosition = new float[numElement]; // allocate an array memory block of numElement size
    for (int i = 0; i < numElement; i++)     // iterate through all element locations
    {
        elementPosition[i] = (i - (((float)numElement - 1) / 2)) * PITCH; // calculate element location
    }

    return elementPosition;
}

float2 **imageParam::genScanlinePosition(int numScanline, const float PITCH, float *elementLocation)
{
    cout << "Imaging depth: ";                 // prompt user for imaging depth
    cin >> desiredDepth;                       // input depth
    cout << "Number of pixels per scanline: "; // prompt user for number of pixels per scanline
    cin >> numPixel;                           // input number of pixels per scanline

    float add = desiredDepth / (numPixel - 1);    // calculate difference between pixels
    scanlinePosition = new float2 *[numScanline]; // allocate an array memory block of numScanline size
    for (int i = 0; i < numScanline; i++)         // iterate numScanline times
    {
        scanlinePosition[i] = new float2[numPixel]; // allocate an array memory block of numPixel size

        for (int j = 0; j < numPixel; j++) // iterate numPixel times
        {
            scanlinePosition[i][j].x = (i - ((numScanline - 1) / 2)) * PITCH; // calculate x position of pixel
            scanlinePosition[i][j].y = (float)add * j;                        // calculate y position of pixel
        }
    }

    return scanlinePosition;
}

float imageParam::getXPosition(int scanline, int pixel)
{
    return scanlinePosition[scanline][pixel].x; // return x position of pixel
}

float imageParam::getYPosition(int scanline, int pixel)
{
    return scanlinePosition[scanline][pixel].y; // return y position of pixel
}

float imageParam::getElementPosition(int element)
{
    return elementPosition[element]; // return element position
}

int imageParam::getNumElement()
{
    return numElement;
}

int imageParam::getNumSample()
{
    return numSample;
}

int imageParam::getNumScanline()
{
    return numScanline;
}

int imageParam::getNumPixel()
{
    return numPixel;
}

void imageParam::deletePositionArray()
{
    for (int i = 0; i < numScanline; i++) // iterate numScanline times
        delete[] scanlinePosition[i];     // delete each element of scanlinePosition
    delete[] scanlinePosition;            // delete scanlinePosition
    delete[] elementPosition;             // delete elementPosition
}
