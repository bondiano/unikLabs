#ifndef BMPIMAGE_H
#define BMPIMAGE_H
#include <fstream>
#include <QDebug>
#include <cmath>

using namespace std;

class bmpImage
{
    // CIEXYZTRIPLE stuff
    typedef int FXPT2DOT30;

    typedef struct {
        FXPT2DOT30 ciexyzX;
        FXPT2DOT30 ciexyzY;
        FXPT2DOT30 ciexyzZ;
    } CIEXYZ;

    typedef struct {
        CIEXYZ  ciexyzRed;
        CIEXYZ  ciexyzGreen;
        CIEXYZ  ciexyzBlue;
    } CIEXYZTRIPLE;

    // bitmap file header
    typedef struct
    {
        unsigned short fType;
        unsigned int fSize;
        unsigned short fReserved1;
        unsigned short fReserved2;
        unsigned int fOffBits;
    }FILEHEADER;

    FILEHEADER *fileHeader;

    // bitmap info header
    typedef struct
    {
        unsigned int infSize;
        unsigned int infWidth;
        unsigned int infHeight;
        unsigned short infPlanes;
        unsigned short infBitCount;
        unsigned int infCompression;
        unsigned int infSizeImage;
        unsigned int infXPelsPerMeter;
        unsigned int infYPelsPerMeter;
        unsigned int infClrUsed;
        unsigned int infClrImportant;
        unsigned int infRedMask;
        unsigned int infGreenMask;
        unsigned int infBlueMask;
        unsigned int infAlphaMask;
        unsigned int infCSType;
        CIEXYZTRIPLE infEndpoints;
        unsigned int infGammaRed;
        unsigned int infGammaGreen;
        unsigned int infGammaBlue;
        unsigned int infIntent;
        unsigned int infProfileData;
        unsigned int infProfileSize;
        unsigned int infReserved;
    }INFOHEADER;

    INFOHEADER *infoHeader;

    typedef struct
    {
        short Blue;
        short Green;
        short Red;
        char Reserved;
    }RGB;

    RGB **rgb;

public:
    bmpImage();
    bmpImage(bmpImage &image);
    ~bmpImage();
    bool loadImage(ifstream &stream);
    bool saveImage(ofstream &stream);
    //геттеры
    int getWidth();
    int getHeight();
    int getRed(int x, int y);
    int getGreen(int x, int y);
    int getBlue(int x, int y);
    int getType();
    //сеттеры
    void setPixel(unsigned int x,unsigned int y,int red, int green, int blue);
    //прочее
    void editContrast(float n);
    void editBright(int n);
    void extension();
    void extension2();
    void lens();
    void sphere();
};

#endif // BMPIMAGE_H
