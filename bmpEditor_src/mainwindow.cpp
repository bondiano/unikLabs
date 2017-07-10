#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QPalette p(palette());
    p.setColor(QPalette::Background, Qt::white);
    setPalette(p);
    ui->setupUi(this);
    image = new bmpImage();
    drawer = new drawBMPImage();
    ui->gridImageLayout->addWidget(drawer);
    sucsess = 0;
    mousePosX = 0;
    mousePosY = 0;
    drawMode = 0;
}

MainWindow::~MainWindow()
{

}

void MainWindow::on_openFileAction_triggered()
{
    QString str = QFileDialog::getOpenFileName(this, QString::fromUtf8("Открыть bmp файл"),
                                               QDir::currentPath(), "Images (*.bmp *.dib *.rle)");
    std::string name = str.toStdString();
    bmpFile.open(name.c_str(),std::ifstream::binary);

    if (!bmpFile.is_open())
        qDebug() << "Cannot to open file!\n";

    if(bmpFile.is_open() && image!=NULL && image->getType()!= 1 && sucsess){
        delete image;
    }

    if(bmpFile.is_open()){
        image = new bmpImage();
        sucsess = image->loadImage(bmpFile);
    }

    if(sucsess){
        reDrawImage();
        //под размер экрана
        QDesktopWidget *mApp = QApplication::desktop();
        if(mApp->width() > image->getWidth()
                && mApp->height() > image->getHeight()){
            setMinimumSize(image->getWidth(),image->getHeight());
        }
        else if(mApp->width() < image->getWidth()
                && mApp->height() > image->getHeight()){
            setMinimumSize(mApp->width(),image->getHeight());
        }
        else if(mApp->height() < image->getHeight()
                && mApp->width() > image->getWidth()){
            setMinimumSize(image->getWidth(),mApp->height());
        }
        else if(mApp->height() < image->getHeight()
                && mApp->width() < image->getWidth()){
            setMinimumSize(mApp->width(),mApp->height());
        }

    }else{
        QMessageBox::critical(this,QObject::tr("Ошибка"),tr("Ошибка при загрузке изображения"));
        qDebug() << "Any problem with image!";
    }
    bmpFile.close();
}

void MainWindow::on_saveAsAction_triggered()
{
    if(sucsess){
        QString fileName = QFileDialog::getSaveFileName(this,
                                    QString::fromUtf8("Сохранить файл"),
                                    "untitled.bmp",
                                    "Images (*.bmp *.dib *.rle)");
        std::string name = fileName.toStdString();
        saveFile.open(name.c_str(),std::ofstream::binary);
        image->saveImage(saveFile);
        saveFile.close();
    }else{
        QMessageBox::warning(this,QObject::tr("Внимание!"),tr("Сначала загрузите изображение!"));
        qDebug() << "Any problem with image!";
    }
}

void MainWindow::on_contrastAction_triggered()
{
    if(sucsess){
        editContrastBrightWidget *editContrastBright = new editContrastBrightWidget(image, this);
        editContrastBright->show();
    }else{
        QMessageBox::warning(this,QObject::tr("Внимание!"),tr("Сначала загрузите изображение!"));
        qDebug() << "Any problem with image!";
    }
}

void MainWindow::on_extensionAction_triggered()
{
        if(sucsess){
        image->extension();
        reDrawImage();
        }else{
            QMessageBox::warning(this,QObject::tr("Внимание!"),tr("Сначала загрузите изображение!"));
            qDebug() << "Any problem with image!";
        }
}


void MainWindow::on_extension2Action_triggered()
{
    if(sucsess){
    image->extension2();
    reDrawImage();
    }else{
        QMessageBox::warning(this,QObject::tr("Внимание!"),tr("Сначала загрузите изображение!"));
        qDebug() << "Any problem with image!";
    }
}

void MainWindow::on_lensAction_triggered()
{
    if(sucsess){
    image->lens();
    reDrawImage();
    }else{
        QMessageBox::warning(this,QObject::tr("Внимание!"),tr("Сначала загрузите изображение!"));
        qDebug() << "Any problem with image!";
    }
}

void MainWindow::on_sphereAction_triggered()
{
    if(sucsess){
    image->sphere();
    reDrawImage();
    }else{
        QMessageBox::warning(this,QObject::tr("Внимание!"),tr("Сначала загрузите изображение!"));
        qDebug() << "Any problem with image!";
    }
}

void MainWindow::on_lineAction_triggered()
{
    if(sucsess){
    color = QColorDialog::getColor(Qt::black, this, "Выберите цвет");
    drawPointX.clear();
    drawPointY.clear();
    drawMode = 2;
    }else{
        QMessageBox::warning(this,QObject::tr("Внимание!"),tr("Сначала загрузите изображение!"));
        qDebug() << "Any problem with image!";
    }
}

void MainWindow::on_circleAction_triggered()
{
    if(sucsess){
    color = QColorDialog::getColor(Qt::black, this, "Выберите цвет");
    drawPointX.clear();
    drawPointY.clear();
    drawMode = 3;
    }else{
        QMessageBox::warning(this,QObject::tr("Внимание!"),tr("Сначала загрузите изображение!"));
        qDebug() << "Any problem with image!";
    }
}

void MainWindow::on_dotAction_triggered()
{
    if(sucsess){
    color = QColorDialog::getColor(Qt::black, this, "Выберите цвет");
    drawPointX.clear();
    drawPointY.clear();
    drawMode = 1;
    }else{
        QMessageBox::warning(this,QObject::tr("Внимание!"),tr("Сначала загрузите изображение!"));
        qDebug() << "Any problem with image!";
    }
}

void MainWindow::reDrawImage()
{
    ui->gridImageLayout->removeWidget(drawer);
    delete drawer;
    drawer = new drawBMPImage(image);
    ui->gridImageLayout->addWidget(drawer);
}

void MainWindow::mousePressEvent(QMouseEvent *event){
    if(drawMode){
        if(event->button() == Qt::LeftButton){
            if(event->x() < image->getWidth() && event->y() < image->getHeight()){
                mousePosX = event->x();
                mousePosY = event->y()-20;
                int R = color.red();
                int G = color.green();
                int B = color.blue();

                if(drawMode == 1){
                    image->setPixel(mousePosX,mousePosY,R,G,B);
                    reDrawImage();
                }

                if(drawMode == 2){
                    if(drawPointX.length()<=2){
                        drawPointX.append(mousePosX);
                        drawPointY.append(mousePosY);
                    }

                    if(drawPointX.length()>=2){
                        BresenhamAlgorithm(image,drawPointX[0],drawPointY[0],drawPointX[1],drawPointY[1],R,G,B);
                        drawPointX.clear();
                        drawPointY.clear();
                        reDrawImage();
                    }
                }

                if(drawMode == 3){
                    if(drawPointX.length()<=2){
                        drawPointX.append(mousePosX);
                        drawPointY.append(mousePosY);
                    }

                    if(drawPointX.length()>=2){
                        int radius = sqrt(abs(drawPointY[0]-drawPointY[1])*abs(drawPointY[0]-drawPointY[1])
                                          +abs(drawPointX[0]-drawPointX[1])*abs(drawPointX[0]-drawPointX[1]));
                        MichinerCircle(image,drawPointX[0],drawPointY[0],radius,R,G,B);
                        drawPointX.clear();
                        drawPointY.clear();
                        reDrawImage();
                    }
                }
            }
        }

        if(event->button() == Qt::RightButton){
            drawMode = 0;
            reDrawImage();
        }
    }
}
