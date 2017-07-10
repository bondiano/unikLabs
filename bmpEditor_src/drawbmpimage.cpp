#include "drawbmpimage.h"

drawBMPImage::drawBMPImage(bmpImage *image,QWidget *parent) : QWidget(parent)
{
    this->image = image;
}

drawBMPImage::drawBMPImage(QWidget *parent) : QWidget(parent)
{
    this->image = NULL;
}

drawBMPImage::~drawBMPImage()
{

}

void drawBMPImage::paintEvent(QPaintEvent *)
{
    if(image!=NULL && image->getType()!= 1){
        QPainter painter(this);
        QImage img(image->getWidth(),image->getHeight(),QImage::Format_RGB32);
        for(int x = image->getWidth()-1; ; x--){
            for(int y = image->getHeight()-1, j = 0; j < image->getHeight(); y--,j++){
                img.setPixel(x,j,qRgb(image->getRed(x,y),image->getGreen(x,y),image->getBlue(x,y)));
            }
            if(x == 0) break;
        }
        painter.drawImage(0,0,img);
    }
}
