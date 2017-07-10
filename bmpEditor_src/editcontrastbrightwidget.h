#ifndef EDITCONTRASTANDBRIGHTWIDGET_H
#define EDITCONTRASTANDBRIGHTWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QSlider>
#include <QPushButton>
#include <QLayout>
#include "bmpimage.h"

class editContrastBrightWidget : public QWidget
{
    Q_OBJECT
    QLabel *contrastLabel;
    QLabel *brightLabel;
    QSlider *contrastSlider;
    QSlider *brightSlider;
    QPushButton *contrastEnableButton;
    QPushButton *brightEnableButton;
    bmpImage *image;

public:
    explicit editContrastBrightWidget(bmpImage *image, QWidget *parent = 0);
    ~editContrastBrightWidget();

signals:

public slots:
    void editContrast();
    void editBright();
};

#endif // EDITCONTRASTANDBRIGHTWIDGET_H
