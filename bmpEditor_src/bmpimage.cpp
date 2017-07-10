#include "bmpimage.h"
/*Программа «вручную» читает растровый файл изображения (bmp), выполняя заданные преобразования изображения*/

template <typename Type>
void read(ifstream &fp, Type &result, size_t size) {
    fp.read(reinterpret_cast<char*>(&result), size);
}

template <typename Type>
void write(ofstream &fp, Type &result, size_t size) {
    fp.write(reinterpret_cast<char*>(&result), size);
}

template <typename Type>
Type Truncate(Type value){
   if(value < 0) value = 0;
   if(value > 255) value = 255;
   return value;
}

unsigned char bitextract(const unsigned int byte, const unsigned int mask) {
    if (mask == 0) {
        return 0;
    }

    // определение количества нулевых бит справа от маски
    int maskBufer = mask;
    int maskPadding = 0;

    while (!(maskBufer & 1)) {
        maskBufer >>= 1;
        maskPadding++;
    }

    // применение маски и смещение
    return (byte & mask) >> maskPadding;
}

bmpImage::bmpImage()
{
    fileHeader = new FILEHEADER;
    infoHeader = new INFOHEADER;
    rgb = new RGB*;
    fileHeader->fType = 1;
}

bmpImage::bmpImage(bmpImage &image)
{
    //конструктор копирования
    fileHeader = new FILEHEADER;
    infoHeader = new INFOHEADER;
    fileHeader->fType = image.fileHeader->fType;
    fileHeader->fSize =  image.fileHeader->fSize;
    fileHeader->fReserved1 = image.fileHeader->fReserved1;
    fileHeader->fReserved2 = image.fileHeader->fReserved2;
    fileHeader->fOffBits = image.fileHeader->fOffBits;

    infoHeader->infSize = image.infoHeader->infSize;
    infoHeader->infWidth = image.infoHeader->infWidth;
    infoHeader->infHeight = image.infoHeader->infHeight;
    infoHeader->infPlanes  = image.infoHeader->infPlanes;
    infoHeader->infBitCount = image.infoHeader->infBitCount;
    infoHeader->infCompression = image.infoHeader->infCompression;
    infoHeader->infSizeImage = image.infoHeader->infSizeImage;
    infoHeader->infXPelsPerMeter = image.infoHeader->infXPelsPerMeter;
    infoHeader->infYPelsPerMeter = image.infoHeader->infYPelsPerMeter;
    infoHeader->infClrUsed = image.infoHeader->infClrUsed;
    infoHeader->infClrImportant = image.infoHeader->infClrImportant;
    infoHeader->infRedMask = image.infoHeader->infRedMask;
    infoHeader->infGreenMask = image.infoHeader->infGreenMask;
    infoHeader->infBlueMask = image.infoHeader->infBlueMask;
    infoHeader->infAlphaMask = image.infoHeader->infAlphaMask;
    infoHeader->infCSType = image.infoHeader->infCSType;
    infoHeader->infEndpoints = image.infoHeader->infEndpoints;
    infoHeader->infGammaRed = image.infoHeader->infGammaRed;
    infoHeader->infGammaGreen = image.infoHeader->infGammaGreen;
    infoHeader->infGammaBlue = image.infoHeader->infGammaBlue;
    infoHeader->infIntent = image.infoHeader->infIntent;
    infoHeader->infProfileData = image.infoHeader->infProfileData;
    infoHeader->infProfileSize = image.infoHeader->infProfileSize;
    infoHeader->infReserved = image.infoHeader->infReserved;

    rgb = new RGB*[infoHeader->infHeight];
    for (unsigned int i = 0; i < infoHeader->infHeight; i++) {
        rgb[i] = new RGB[infoHeader->infWidth];
    }

    for (unsigned int i = 0; i < infoHeader->infHeight; i++) {
        for (unsigned int j = 0; j < infoHeader->infWidth; j++) {
            rgb[i][j].Blue = image.rgb[i][j].Blue;
            rgb[i][j].Green= image.rgb[i][j].Green;
            rgb[i][j].Red = image.rgb[i][j].Red;
        }
    }
}

bmpImage::~bmpImage()
{
    for (unsigned int i = 0; i < infoHeader->infHeight; i++) {
        delete[] rgb[i];
    }
    delete[] rgb;
    delete fileHeader;
    delete infoHeader;
}

bool bmpImage::loadImage(ifstream &stream){
    qDebug() << "At reading file.\n";

    //считываем заголовок изображения
    read(stream, fileHeader->fType, sizeof(fileHeader->fType));
    read(stream, fileHeader->fSize, sizeof(fileHeader->fSize));
    read(stream, fileHeader->fReserved1, sizeof(fileHeader->fReserved1));
    read(stream, fileHeader->fReserved2, sizeof(fileHeader->fReserved2));
    read(stream, fileHeader->fOffBits, sizeof(fileHeader->fOffBits));

    if(fileHeader->fType != 0x4D42){
        qDebug() << "Error: It's not BMP image.\n";
        return 0;
    }

    //информация изображения
    read(stream, infoHeader->infSize, sizeof(infoHeader->infSize));

    // bmp core
    if (infoHeader->infSize >= 12) {
        read(stream, infoHeader->infWidth, sizeof(infoHeader->infWidth));
        read(stream, infoHeader->infHeight, sizeof(infoHeader->infHeight));
        read(stream, infoHeader->infPlanes, sizeof(infoHeader->infPlanes));
        read(stream, infoHeader->infBitCount, sizeof(infoHeader->infBitCount));
    }

    // получаем информацию о битности
    int colorsCount = infoHeader->infBitCount >> 3;
    if (colorsCount < 3) {
        colorsCount = 3;
    }

    int bitsOnColor = infoHeader->infBitCount / colorsCount;
    int maskValue = (1 << bitsOnColor) - 1;

    // bmp v1
    if (infoHeader->infSize >= 40) {
        read(stream, infoHeader->infCompression, sizeof(infoHeader->infCompression));
        read(stream, infoHeader->infSizeImage, sizeof(infoHeader->infSizeImage));
        read(stream, infoHeader->infXPelsPerMeter, sizeof(infoHeader->infXPelsPerMeter));
        read(stream, infoHeader->infYPelsPerMeter, sizeof(infoHeader->infYPelsPerMeter));
        read(stream, infoHeader->infClrUsed, sizeof(infoHeader->infClrUsed));
        read(stream, infoHeader->infClrImportant, sizeof(infoHeader->infClrImportant));
    }

    // bmp v2
    infoHeader->infRedMask = 0;
    infoHeader->infGreenMask = 0;
    infoHeader->infBlueMask = 0;

    if (infoHeader->infSize >= 52) {
        read(stream, infoHeader->infRedMask, sizeof(infoHeader->infRedMask));
        read(stream, infoHeader->infGreenMask, sizeof(infoHeader->infGreenMask));
        read(stream, infoHeader->infBlueMask, sizeof(infoHeader->infBlueMask));
    }

    // если маска не задана, то ставим маску по умолчанию
    if (infoHeader->infRedMask == 0 || infoHeader->infGreenMask == 0 || infoHeader->infBlueMask == 0) {
        infoHeader->infRedMask = maskValue << (bitsOnColor * 2);
        infoHeader->infGreenMask = maskValue << bitsOnColor;
        infoHeader->infBlueMask = maskValue;
    }

    // bmp v3
    if (infoHeader->infSize >= 56) {
        read(stream, infoHeader->infAlphaMask, sizeof(infoHeader->infAlphaMask));
    } else {
        infoHeader->infAlphaMask = maskValue << (bitsOnColor * 3);
    }

    // bmp v4
    if (infoHeader->infSize >= 108) {
        read(stream, infoHeader->infCSType, sizeof(infoHeader->infCSType));
        read(stream, infoHeader->infEndpoints, sizeof(infoHeader->infEndpoints));
        read(stream, infoHeader->infGammaRed, sizeof(infoHeader->infGammaRed));
        read(stream, infoHeader->infGammaGreen, sizeof(infoHeader->infGammaGreen));
        read(stream, infoHeader->infGammaBlue, sizeof(infoHeader->infGammaBlue));
    }

    // bmp v5
    if (infoHeader->infSize >= 124) {
        read(stream, infoHeader->infIntent, sizeof(infoHeader->infIntent));
        read(stream, infoHeader->infProfileData, sizeof(infoHeader->infProfileData));
        read(stream, infoHeader->infProfileSize, sizeof(infoHeader->infProfileSize));
        read(stream, infoHeader->infReserved, sizeof(infoHeader->infReserved));
    }

    // проверка на поддерку этой версии формата
    if (infoHeader->infSize != 12 && infoHeader->infSize != 40 && infoHeader->infSize != 52 &&
        infoHeader->infSize != 56 && infoHeader->infSize != 108 && infoHeader->infSize != 124) {
        qDebug() << "Error: Unsupported BMP format.\n";
        return 0;
    }

    if (infoHeader->infBitCount != 16 && infoHeader->infBitCount != 24 && infoHeader->infBitCount != 32) {
        qDebug() << "Error: Unsupported BMP bit count.\n";
        return 0;
    }

    if (infoHeader->infCompression != 0 && infoHeader->infCompression != 3) {
        qDebug() << "Error: Unsupported BMP compression.\n";
        return 0;
    }
    qDebug() << "Width:" << infoHeader->infWidth << "Height" << infoHeader->infHeight;
    rgb = new RGB*[infoHeader->infHeight];
    for (unsigned int i = 0; i < infoHeader->infHeight; i++) {
        rgb[i] = new RGB[infoHeader->infWidth];
    }
   int linePadding = ((infoHeader->infWidth * (infoHeader->infBitCount / 8)) % 4) & 3; //отсуп в конце каждой строки

    // чтение цвета
     unsigned int bufer;
    for (unsigned int i = 0; i < infoHeader->infHeight; i++) {
        for (unsigned int j = 0; j < infoHeader->infWidth; j++) {
            read(stream, bufer, infoHeader->infBitCount / 8);

            rgb[i][j].Red = bitextract(bufer, infoHeader->infRedMask);
            rgb[i][j].Green = bitextract(bufer, infoHeader->infGreenMask);
            rgb[i][j].Blue = bitextract(bufer, infoHeader->infBlueMask);
            rgb[i][j].Reserved = bitextract(bufer, infoHeader->infAlphaMask);
        }
        stream.seekg(linePadding, std::ios_base::cur);
    }
    qDebug() << "Image Done!\n";
    return 1;
}

bool bmpImage::saveImage(ofstream &stream){
    qDebug() << "At writing file.\n";
    // записываем заголовок файла
    write(stream, fileHeader->fType, sizeof(fileHeader->fType));
    write(stream, fileHeader->fSize, sizeof(fileHeader->fSize));
    write(stream, fileHeader->fReserved1, sizeof(fileHeader->fReserved1));
    write(stream, fileHeader->fReserved2, sizeof(fileHeader->fReserved2));
    write(stream, fileHeader->fOffBits, sizeof(fileHeader->fOffBits));

    // записываем заголовок изображения
    write(stream, infoHeader->infSize, sizeof(infoHeader->infSize));

    // bmp core
    if (infoHeader->infSize >= 12) {
        write(stream, infoHeader->infWidth, sizeof(infoHeader->infWidth));
        write(stream, infoHeader->infHeight, sizeof(infoHeader->infHeight));
        write(stream, infoHeader->infPlanes, sizeof(infoHeader->infPlanes));
        write(stream, infoHeader->infBitCount, sizeof(infoHeader->infBitCount));
    }

    // bmp v1
    if (infoHeader->infSize >= 40) {
        write(stream, infoHeader->infCompression, sizeof(infoHeader->infCompression));
        write(stream, infoHeader->infSizeImage, sizeof(infoHeader->infSizeImage));
        write(stream, infoHeader->infXPelsPerMeter, sizeof(infoHeader->infXPelsPerMeter));
        write(stream, infoHeader->infYPelsPerMeter, sizeof(infoHeader->infYPelsPerMeter));
        write(stream, infoHeader->infClrUsed, sizeof(infoHeader->infClrUsed));
        write(stream, infoHeader->infClrImportant, sizeof(infoHeader->infClrImportant));
    }

    // bmp v2
    if (infoHeader->infSize >= 52) {
        write(stream, infoHeader->infRedMask, sizeof(infoHeader->infRedMask));
        write(stream, infoHeader->infGreenMask, sizeof(infoHeader->infGreenMask));
        write(stream, infoHeader->infBlueMask, sizeof(infoHeader->infBlueMask));
    }

    // bmp v3
    if (infoHeader->infSize >= 56) {
        write(stream, infoHeader->infAlphaMask, sizeof(infoHeader->infAlphaMask));
    }

    // bmp v4
    if (infoHeader->infSize >= 108) {
        write(stream, infoHeader->infCSType, sizeof(infoHeader->infCSType));
        write(stream, infoHeader->infEndpoints, sizeof(infoHeader->infEndpoints));
        write(stream, infoHeader->infGammaRed, sizeof(infoHeader->infGammaRed));
        write(stream, infoHeader->infGammaGreen, sizeof(infoHeader->infGammaGreen));
        write(stream, infoHeader->infGammaBlue, sizeof(infoHeader->infGammaBlue));
    }

    // bmp v5
    if (infoHeader->infSize >= 124) {
        write(stream, infoHeader->infIntent, sizeof(infoHeader->infIntent));
        write(stream, infoHeader->infProfileData, sizeof(infoHeader->infProfileData));
        write(stream, infoHeader->infProfileSize, sizeof(infoHeader->infProfileSize));
        write(stream, infoHeader->infReserved, sizeof(infoHeader->infReserved));
    }

   for (unsigned int i = 0; i < infoHeader->infHeight; i++) {
       for (unsigned int j = 0; j < infoHeader->infWidth; j++) {
           write(stream, rgb[i][j].Blue, sizeof(unsigned char));
           write(stream, rgb[i][j].Green, sizeof(unsigned char));
           write(stream, rgb[i][j].Red, sizeof(unsigned char));
       }
   }
   qDebug() << "Image Done!\n";
   return 1;
}

int bmpImage::getHeight()
{
    return infoHeader->infHeight;
}

int bmpImage::getWidth()
{
    return infoHeader->infWidth;
}

int bmpImage::getGreen(int x, int y)
{
    return rgb[y][x].Green;
}

int bmpImage::getRed(int x, int y)
{
    return rgb[y][x].Red;
}

int bmpImage::getBlue(int x, int y)
{
    return rgb[y][x].Blue;
}

int bmpImage::getType()
{
    return fileHeader->fType;
}

void bmpImage::setPixel(unsigned int x,unsigned int y,int red, int green, int blue){
    if(x < infoHeader->infWidth && y < infoHeader->infHeight && int(infoHeader->infHeight-y) < infoHeader->infHeight){
        y = abs(int(infoHeader->infHeight-y));
        rgb[y][x].Red = Truncate(red);
        rgb[y][x].Green = Truncate(green);
        rgb[y][x].Blue = Truncate(blue);
    }
}

void bmpImage::editBright(int factor){
    if(fileHeader->fType != 1 && infoHeader->infHeight != NULL){
        for(unsigned int y = 0; y < infoHeader->infHeight; y++){
            for(unsigned int x = 0; x < infoHeader->infWidth; x++){
                rgb[y][x].Red = Truncate(factor + rgb[y][x].Red);
                rgb[y][x].Green = Truncate(factor + rgb[y][x].Green);
                rgb[y][x].Blue = Truncate(factor + rgb[y][x].Blue);
            }
        }
    }else{
        qDebug() << "Any problem with image!";
    }
}

void bmpImage::editContrast(float factor){
    if(fileHeader->fType != 1 && infoHeader->infHeight != NULL){
        float midBright = 0, midBright1 = 0, midBright2 = 0;
        for(unsigned int y = 0; y < infoHeader->infHeight; y++){
            for(unsigned int x = 0; x < infoHeader->infWidth; x++){
                midBright += rgb[y][x].Red;
                midBright1 += rgb[y][x].Green;
                midBright2 += rgb[y][x].Blue;
            }
        }

        midBright = (midBright2 * 0.114 + midBright1 * 0.587 + midBright * 0.299)/(infoHeader->infHeight*infoHeader->infWidth);

        for(unsigned int y = 0; y < infoHeader->infHeight; y++){
            for(unsigned int x = 0; x < infoHeader->infWidth; x++){
                double newRed = Truncate(midBright + floor(factor * (rgb[y][x].Red-midBright)));
                double newGreen = Truncate(midBright + floor(factor * (rgb[y][x].Green-midBright)));
                double newBlue = Truncate(midBright + floor(factor * (rgb[y][x].Blue-midBright)));
                rgb[y][x].Red = newRed;
                rgb[y][x].Green = newGreen;
                rgb[y][x].Blue = newBlue;
                }
        }
    }else{
        qDebug() << "Any problem with image!";
    }
}

void bmpImage::extension(){
    //создаем массив ргб цветов
    RGB **tempRgb = new RGB*[infoHeader->infHeight];
    for (unsigned int i = 0; i < infoHeader->infHeight; i++) {
        tempRgb[i] = new RGB[infoHeader->infWidth];
    }

    //заполняем массив значением -1, как флаг того, что цвет пикселей в этом квадрате 3х3 не был изменен
    for(unsigned int y = 0; y < infoHeader->infHeight; y++){
        for(unsigned int x = 0; x < infoHeader->infWidth; x++){
            tempRgb[y][x].Red = -1;
            tempRgb[y][x].Green = -1;
            tempRgb[y][x].Blue = -1;
        }
    }
    //средние цвета
    int middleR = 0, middleG = 0, middleB = 0;
    //заполняем массив средними значениями по квадрату, если какой-то стороны не хватает для обработки 3х3, заполняем сколько можем
    unsigned int maxHeight = infoHeader->infHeight - ((infoHeader->infHeight - 1) % 3);
    unsigned int maxWidth = infoHeader->infWidth - ((infoHeader->infWidth - 1) % 3);
    for(unsigned int y = 1; y < maxHeight - maxHeight % 3; y++){
        for(unsigned int x = 1; x < maxWidth - maxHeight % 3; x++){
            if(tempRgb[y][x].Red == -1){
                middleR = (rgb[y-1][x-1].Red+rgb[y-1][x].Red+rgb[y-1][x+1].Red
                        +rgb[y][x-1].Red+rgb[y][x].Red+rgb[y][x+1].Red
                        +rgb[y+1][x-1].Red+rgb[y+1][x].Red+rgb[y+1][x+1].Red)/9;
                middleG = (rgb[y-1][x-1].Green+rgb[y-1][x].Green+rgb[y-1][x+1].Green
                        +rgb[y][x-1].Green+rgb[y][x].Green+rgb[y][x+1].Green
                        +rgb[y+1][x-1].Green+rgb[y+1][x].Green+rgb[y+1][x+1].Green)/9;
                middleB = (rgb[y-1][x-1].Blue+rgb[y-1][x].Blue+rgb[y-1][x+1].Blue
                        +rgb[y][x-1].Blue+rgb[y][x].Blue+rgb[y][x+1].Blue
                        +rgb[y+1][x-1].Blue+rgb[y+1][x].Blue+rgb[y+1][x+1].Blue)/9;

                tempRgb[y-1][x-1].Red = middleR; tempRgb[y-1][x].Red = middleR; tempRgb[y-1][x+1].Red = middleR;
                tempRgb[y][x-1].Red = middleR; tempRgb[y][x].Red = middleR; tempRgb[y][x+1].Red = middleR;
                tempRgb[y+1][x-1].Red = middleR; tempRgb[y+1][x].Red = middleR; tempRgb[y+1][x+1].Red = middleR;

                tempRgb[y-1][x-1].Green = middleG; tempRgb[y-1][x].Green = middleG; tempRgb[y-1][x+1].Green = middleG;
                tempRgb[y][x-1].Green = middleG; tempRgb[y][x].Green = middleG; tempRgb[y][x+1].Green = middleG;
                tempRgb[y+1][x-1].Green = middleG; tempRgb[y+1][x].Green = middleG; tempRgb[y+1][x+1].Green = middleG;

                tempRgb[y-1][x-1].Blue = middleB; tempRgb[y-1][x].Blue = middleB; tempRgb[y-1][x+1].Blue = middleB;
                tempRgb[y][x-1].Blue = middleB; tempRgb[y][x].Blue = middleB; tempRgb[y][x+1].Blue = middleB;
                tempRgb[y+1][x-1].Blue = middleB; tempRgb[y+1][x].Blue = middleB; tempRgb[y+1][x+1].Blue = middleB;
            }
        }
    }

    //переносим массив в основное изображение
    for(unsigned int y = 0; y < maxHeight - maxHeight%3; y++){
        for(unsigned int x = 0; x < maxWidth- maxHeight%3; x++){
            rgb[y][x].Red = Truncate(tempRgb[y][x].Red);
            rgb[y][x].Green = Truncate(tempRgb[y][x].Green);
            rgb[y][x].Blue = Truncate(tempRgb[y][x].Blue);
        }
    }
    for (unsigned int i = 0; i < infoHeader->infHeight; i++) {
        delete[] tempRgb[i];
    }
    delete[] tempRgb;
}

void bmpImage::extension2(){
    //создаем массив ргб цветов
    RGB **tempRgb = new RGB*[infoHeader->infHeight];
    for (unsigned int i = 0; i < infoHeader->infHeight; i++) {
        tempRgb[i] = new RGB[infoHeader->infWidth];
    }
    //заполняем массив значением -1, как флаг того, что цвет пикселей в этом квадрате 3х3 не был изменен
    for(unsigned int y = 0; y < infoHeader->infHeight; y++){
        for(unsigned int x = 0; x < infoHeader->infWidth; x++){
            tempRgb[y][x].Red = -1;
            tempRgb[y][x].Green = -1;
            tempRgb[y][x].Blue = -1;
        }
    }
    //средние цвета
    int middleR = 0, middleG = 0, middleB = 0;

    //заполняем массив средними значениями по квадрату, если какой-то стороны не хватает для обработки 3х3, заполняем сколько можем
    unsigned int maxHeight = infoHeader->infHeight - ((infoHeader->infHeight - 1) %2);
    unsigned int maxWidth = infoHeader->infWidth - ((infoHeader->infWidth - 1) % 2);
    for(unsigned int y = 0; y < maxHeight - maxHeight % 2; y++){
        for(unsigned int x = 0; x < maxWidth - maxHeight % 2; x++){
            if(tempRgb[y][x].Red == -1){
                middleR = (rgb[y][x].Red+rgb[y][x+1].Red
                        +rgb[y+1][x].Red+rgb[y+1][x+1].Red)/4;
                middleG = (rgb[y][x].Green+rgb[y][x+1].Green
                        +rgb[y+1][x].Green+rgb[y+1][x+1].Green)/4;
                middleB = (rgb[y][x].Blue+rgb[y][x+1].Blue
                        +rgb[y+1][x].Blue+rgb[y+1][x+1].Blue)/4;

                tempRgb[y][x].Red = middleR; tempRgb[y][x+1].Red = middleR;
                tempRgb[y+1][x].Red = middleR; tempRgb[y+1][x+1].Red = middleR;

                tempRgb[y][x].Green = middleG; tempRgb[y][x+1].Green = middleG;
                tempRgb[y+1][x].Green = middleG; tempRgb[y+1][x+1].Green = middleG;

                tempRgb[y][x].Blue = middleB; tempRgb[y][x+1].Blue = middleB;
                tempRgb[y+1][x].Blue = middleB; tempRgb[y+1][x+1].Blue = middleB;
            }
        }
    }

    //переносим массив в основное изображение
    for(unsigned int y = 0; y < maxHeight - maxHeight%2; y++){
        for(unsigned int x = 0; x < maxWidth- maxHeight%2; x++){
            rgb[y][x].Red = Truncate(tempRgb[y][x].Red);
            rgb[y][x].Green = Truncate(tempRgb[y][x].Green);
            rgb[y][x].Blue = Truncate(tempRgb[y][x].Blue);
        }
    }

    for (unsigned int i = 0; i < infoHeader->infHeight; i++) {
        delete[] tempRgb[i];
    }
    delete[] tempRgb;
}

void bmpImage::lens(){
    int x = infoHeader->infWidth/2;
    int y = infoHeader->infHeight/2;
    int LensDiam = 0;
    if(infoHeader->infHeight > infoHeader->infWidth){
        LensDiam = infoHeader->infWidth/3.14;
    }else{
        LensDiam = infoHeader->infHeight/3.14;
    }

    int k = LensDiam/10; //коэф искажения

    RGB **tempRgb = new RGB*[infoHeader->infHeight];
    for (unsigned int i = 0; i < infoHeader->infHeight; i++) {
        tempRgb[i] = new RGB[infoHeader->infWidth];
    }

    for(unsigned int y = 0; y < infoHeader->infHeight; y++){
        for(unsigned int x = 0; x < infoHeader->infWidth; x++){
            tempRgb[y][x].Red = rgb[y][x].Red;
            tempRgb[y][x].Green = rgb[y][x].Green;
            tempRgb[y][x].Blue = rgb[y][x].Blue;
        }
    }

    for(int i = -LensDiam; i <= LensDiam; i++)
    {
        int len = sqrt((float)(LensDiam*LensDiam - i*i));
        for(int j = -len; j <= len; j++)
        {
            int dy = -k*sin(3.14*i/(2*LensDiam));
            int dx = -k*sin(3.14*j/(2*abs(len)));
            if(abs(len) == abs(j)){
                dx = -k*sin(3.14*i);
                dy = -k*sin(3.14*j);
            }
            if(abs(i + dy) < LensDiam && abs(j + dx) < abs(len))
            {
                rgb[y + i + dy][x + j + dx].Red = Truncate(tempRgb[y+i][x+j].Red);
                rgb[y + i + dy][x + j + dx].Green = Truncate(tempRgb[y+i][x+j].Green);
                rgb[y + i + dy][x + j + dx].Blue = Truncate(tempRgb[y+i][x+j].Blue);
            }
        }
    }

    for (unsigned int i = 0; i < infoHeader->infHeight; i++) {
        delete[] tempRgb[i];
    }
    delete[] tempRgb;
}

void bmpImage::sphere(){
    int halfWidth = infoHeader->infWidth/2;
    int halfHeight = infoHeader->infHeight/2;

    RGB **tempRgb = new RGB*[infoHeader->infHeight];
    for (unsigned int i = 0; i < infoHeader->infHeight; i++) {
        tempRgb[i] = new RGB[infoHeader->infWidth];
    }
    for(unsigned int y = 0; y < infoHeader->infHeight; y++){
        for(unsigned int x = 0; x < infoHeader->infWidth; x++){
            tempRgb[y][x].Red = 0;
            tempRgb[y][x].Green = 0;
            tempRgb[y][x].Blue = 0;
        }
    }
    int radius = 0;
    if(infoHeader->infHeight > infoHeader->infWidth){
        radius = infoHeader->infWidth/3.1415;
    }else{
        radius = infoHeader->infHeight/3.1415;
    }
    for(unsigned int y = 0; y < infoHeader->infHeight; y++){
        for(unsigned int x = 0; x < infoHeader->infWidth; x++){
            int distX = x-halfWidth;
            int distY = y-halfHeight;

            float distanceSource = hypot(distX,distY);
            float distanceNew = 2*radius*asin(distanceSource/radius)/2;

            float factor = distanceNew/distanceSource;

            if(distanceSource<=radius){
                unsigned int newX = abs(distX * factor + halfWidth);
                unsigned int newY = abs(distY * factor + halfHeight);

                if(distanceNew == 0){
                    newX = distX;
                    newY = distY;
                }

                if(newX >= infoHeader->infWidth) newX = infoHeader->infWidth - 1;
                if(newY >= infoHeader->infHeight) newY = infoHeader->infHeight - 1;

                tempRgb[y][x].Red = rgb[newY][newX].Red;
                tempRgb[y][x].Green = rgb[newY][newX].Green;
                tempRgb[y][x].Blue = rgb[newY][newX].Blue;
            }
        }
    }

    //переносим массив в основное изображение
    for(unsigned int y = 0; y < infoHeader->infHeight; y++){
        for(unsigned int x = 0; x < infoHeader->infWidth; x++){
            rgb[y][x].Red = Truncate(tempRgb[y][x].Red);
            rgb[y][x].Green = Truncate(tempRgb[y][x].Green);
            rgb[y][x].Blue = Truncate(tempRgb[y][x].Blue);
        }
    }

    for (unsigned int i = 0; i < infoHeader->infHeight; i++) {
        delete[] tempRgb[i];
    }
    delete[] tempRgb;
}
