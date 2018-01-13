#include "editcontrastbrightwidget.h"

editContrastBrightWidget::editContrastBrightWidget(bmpImage *image, QWidget *parent) : QWidget(parent)
{
    this->image = image;
    //параметры окна
    setWindowFlags(Qt::Window);
    setWindowTitle("Редактирование контраста и яркости");
    setMinimumSize(400,50);
    QPalette p(palette());
    p.setColor(QPalette::Background, Qt::white);
    setPalette(p);
    QHBoxLayout *verticalLayout = new QHBoxLayout(this);

    //параметры контрастности
    contrastSlider= new QSlider(Qt::Horizontal,this);
    contrastSlider->setRange(-100,100);
    contrastSlider->setPageStep(1);
    contrastSlider->setValue(0);
    contrastSlider->setToolTip("Контраст");
    contrastSlider->setTickInterval(1);
    contrastLabel = new QLabel("Контраст:",this);
    QObject::connect(contrastSlider, SIGNAL(valueChanged(int)), contrastLabel, SLOT(setNum(int)));

    contrastEnableButton= new QPushButton("Применить",this);
    verticalLayout->addWidget(contrastLabel);
    verticalLayout->addWidget(contrastSlider);
    verticalLayout->addWidget(contrastEnableButton);

    //параметры яркости
    brightLabel = new QLabel("Яркость:",this);
    brightSlider= new QSlider(Qt::Horizontal,this);
    brightSlider->setRange(-255,255);
    brightSlider->setPageStep(1);
    brightSlider->setValue(0);
    brightSlider->setToolTip("Яркость");
    brightSlider->setTickInterval(1);
    QObject::connect(brightSlider, SIGNAL(valueChanged(int)), brightLabel, SLOT(setNum(int)));

    brightEnableButton= new QPushButton("Применить",this);
    verticalLayout->addWidget(brightLabel);
    verticalLayout->addWidget(brightSlider);
    verticalLayout->addWidget(brightEnableButton);

    QObject::connect(brightEnableButton, SIGNAL(clicked()), this, SLOT(editBright()));
    QObject::connect(brightEnableButton, SIGNAL(clicked()), parent, SLOT(reDrawImage()));

    QObject::connect(contrastEnableButton, SIGNAL(clicked()), this, SLOT(editContrast()));
    QObject::connect(contrastEnableButton, SIGNAL(clicked()), parent, SLOT(reDrawImage()));
}

editContrastBrightWidget::~editContrastBrightWidget()
{
    delete contrastLabel;
    delete brightLabel;
    delete contrastSlider;
    delete brightSlider;
    delete contrastEnableButton;
    delete brightEnableButton;
}

void editContrastBrightWidget::editBright(){
    if(image!=NULL && image->getType()!=-1){
        image->editBright(brightSlider->value());
        brightSlider->setValue(0);
    }else{
        qDebug() << "Sthm with your image!";
    }
}

void editContrastBrightWidget::editContrast(){
    if(image!=NULL && image->getType()!= 1){
        image->editContrast((1.00 + contrastSlider->value()*0.01));
        contrastSlider->setValue(0);
    }else{
        qDebug() << "Sthm with your image!";
    }
}
