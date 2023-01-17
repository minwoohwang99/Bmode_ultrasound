#include "dataBuffer.h"
using namespace std;

dataBuffer::dataBuffer()
{
    numElement = 0;    // initialize numElement to 0
    numSample = 0;     // initialize numSample to 0
    scanline = 0;      // initialize scanline to 0
    dataMatrix = NULL; // initialize dataMatrix to NULL
    next = NULL;       // initialize next to NULL
}

dataBuffer::dataBuffer(std::ifstream *imagFile, std::ifstream *realFile, int inputNumElement, int inputNumSample, int inputScanline)
{
    numElement = inputNumElement;               // set numElement to inputNumElement
    numSample = inputNumSample;                 // set numSample to inputNumSample
    scanline = inputScanline;                   // set scanline to inputScanline
    dataMatrix = createDataMatrix();            // set dataMatrix to createDataMatrix()
    loadRFData(dataMatrix, imagFile, realFile); // call loadRFData() function
}

dataBuffer::~dataBuffer()
{
    deleteDataMatrix(); // call deleteDataMatrix() function
}

complex **dataBuffer::createDataMatrix()
{
    complex **RFData;                    // declare new double-pointer variable of complex type
    RFData = new complex *[numElement];  // allocate memory block array of numElement size
    for (int i = 0; i < numElement; i++) // iterate numElement size
    {
        RFData[i] = new complex[numSample]; // allocate memory block array of numSample size
    }
    return RFData;
}

int dataBuffer::loadRFData(complex **RFData, std::ifstream *imagFile, std::ifstream *realFile)
{

    for (int i = 0; i < numElement; i++) // iterate numElement times
    {
        for (int j = 0; j < numSample; j++) // iterate numSample times
        {
            char a[20];               // create char array with size 20
            char b[20];               // create another char array with size 20
            realFile->getline(a, 20); // grab text line
            imagFile->getline(b, 20); // grab text line
            float numa = atof(a);     // convert a from char to float
            float numb = atof(b);     // convert b from char to float
            RFData[i][j].real = numa; // store value in real part of RFData
            RFData[i][j].imag = numb; // store value in imaginary part of RFData
        }
    }
    return 0;
}

float dataBuffer::getRealRFData(int element, int sample)
{
    return dataMatrix[element][sample].real; // return real part of data
}
float dataBuffer::getImagRFData(int element, int sample)
{
    return dataMatrix[element][sample].imag; // return imaginary part of data
}

void dataBuffer::deleteDataMatrix()
{
    for (int i = 0; i < numElement; i++) // iterate numElement times
    {
        delete[] dataMatrix[i]; // delete all elements of dataMatrix
    }
    delete[] dataMatrix; // delete dataMatrix
}
