#ifndef DRAWBMPIMAGE_H
#define DRAWBMPIMAGE_H

#include <QWidget>
#include <QPainter>
#include "bmpimage.h"

class drawBMPImage : public QWidget
{
    Q_OBJECT
    bmpImage *image;
public:
    explicit drawBMPImage(QWidget *parent = 0);
    drawBMPImage(bmpImage *image,QWidget *parent = 0);
    ~drawBMPImage();

signals:

protected:
    void paintEvent(QPaintEvent *);
public slots:

};

#endif // DRAWBMPIMAGE_H
