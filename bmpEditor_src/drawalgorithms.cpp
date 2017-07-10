#include "mainwindow.h"
#include <QtDebug>

int sign(float a){
    if(a > 0.) return 1;
    if(a < 0.) return -1;
    return 0;
}

//пикселы окружности по часовой стрелке для алгортима Минчера
void pixelCircleM(bmpImage *image, int centerX, int centerY, int x, int y, int r, int g, int b){
    image->setPixel(centerX+x, centerY+y, r, g, b);
    image->setPixel(centerX+y, centerY+x, r, g, b);
    image->setPixel(centerX+y, centerY-x, r, g, b);
    image->setPixel(centerX+x, centerY-y, r, g, b);
    image->setPixel(centerX-x, centerY-y, r, g, b);
    image->setPixel(centerX-y, centerY-x, r, g, b);
    image->setPixel(centerX-y, centerY+x, r, g, b);
    image->setPixel(centerX-x, centerY+y, r, g, b);
}

void BresenhamAlgorithm(bmpImage *image, int x1, int y1, int x2, int y2, int r, int g, int b){
    //Генерация отрезка алгоритмом Брезенхейма
    int x = x1;
    int y = y1;
    int Dx = abs(x2-x1);
    int Dy = abs(y2-y1);
    int s1 = sign(x2-x1);
    int s2 = sign(y2-y1);
    int swaped = false;

    if(Dy>Dx){
        int t =Dx;
        Dx = Dy;
        Dy = t;
        swaped = true;
    } else{
        swaped = false;
    }

    int e = Dy*2 - Dx;
    image->setPixel(x, y, r, g, b);
    for(int i = 0; i<Dx;++i){
        while(e>=0){
            if(swaped){
                x+=s1;
            } else {
                y+=s2;
            }
            e-=2*Dx;
        }
        if(!swaped){
            x+=s1;
        } else {
            y+=s2;
        }
        e+=2*Dy;
        image->setPixel(x, y, r, g, b);
    }
}

void MichinerCircle (bmpImage *image, int centerX, int centerY, int radius, int r, int g, int b){
    //Генерация окружности алгоритмом Минчера
   int  x = 0;
   int y = radius;
   int d = 3 - 2 * radius;
   while (x < y) {
      pixelCircleM(image, centerX, centerY, x, y, r, g, b);
      if (d < 0){
          d = d + 4*x + 6;
      }
      else {
         d = d + 4*(x-y) + 10;
         --y;
      }
      ++x;
   }
   if (x == y) pixelCircleM(image, centerX, centerY, x, y, r, g, b);
}
