#include "BmodeClass.h"

BmodeClass::BmodeClass()
{
    imparams = NULL; // initialize imparams to NULL
    RFData = NULL;   // initialize RFData to NULL
    next = NULL;     // initialize next to NULL
    line = 0;        // initialize line to 0
}

BmodeClass::BmodeClass(imageParam *params, dataBuffer *data, int numline)
{
    imparams = params;                                  // set imparams to params
    RFData = data;                                      // set RFData to data
    line = numline;                                     // set line to numline
    scanline = createScanline(imparams->getNumPixel()); // set scanline to createScanline(imparams->getNumPixel)
    beamform();                                         // call beamform() function
}

BmodeClass::~BmodeClass()
{
    deleteScanline(); // call deleteScanline() function
}

float *BmodeClass::createScanline(int numPixel)
{
    float *mem;                // create new float pointer
    mem = new float[numPixel]; // allocate memory block array of numPixel size

    return mem;
}

void BmodeClass::beamform()
{
    float tForward;  // create float for tForward
    float tBackward; // create float for tBackward
    float tTotal;    // create float for tTotal
    int s;           // create int for s
    float PReal;     // create float for PReal
    float PImag;     // create float for PImag

    for (int i = 0; i < imparams->getNumPixel(); i++) // iterate numPixel times
    {
        PReal = 0; // set PReal to 0
        PImag = 0; // set PImag to 0

        tForward = imparams->getYPosition(line, i) / imparams->SOS; // calculate tForward

        for (int j = 0; j < imparams->getNumElement(); j++) // iterate numElement times
        {
            tBackward = (sqrt(pow(imparams->getYPosition(line, i), 2) + pow(imparams->getXPosition(line, i) - imparams->getElementPosition(j), 2))) / imparams->SOS; // calculate tBackward

            tTotal = tForward + tBackward; // calculate tTotal

            s = floor(tTotal * imparams->FS); // calculate s

            if (s <= imparams->getNumSample()) // if s is less than numSample
            {
                PReal += RFData->getRealRFData(j, s); //add to PReal
                PImag += RFData->getImagRFData(j, s); //add to PIMag
            }
        }

        scanline[i] = sqrt(pow(PReal, 2) + pow(PImag, 2)); // calculate magnitude
    }
}

void BmodeClass::getScanline(float *data)
{
    for (int i = 0; i < imparams->getNumPixel(); i++) //iterate numPixel times
    {
        data[i] = scanline[i]; //copy scanline element to data element
    }
}

void BmodeClass::deleteScanline()
{
    delete[] scanline; //delete scanline
}