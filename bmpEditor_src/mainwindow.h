#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QMessageBox>
#include <QDesktopWidget>
#include <QColorDialog>
#include <QMouseEvent>
#include <fstream>
#include <cmath>
#include "bmpimage.h"
#include "drawbmpimage.h"
#include "editcontrastbrightwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_openFileAction_triggered();
    void on_contrastAction_triggered();
    void on_extensionAction_triggered();
    void on_lensAction_triggered();
    void on_sphereAction_triggered();
    void on_lineAction_triggered();
    void on_circleAction_triggered();
    void on_dotAction_triggered();
    void on_saveAsAction_triggered();
    void on_extension2Action_triggered();
    void mousePressEvent(QMouseEvent *event);

public slots:
    void reDrawImage();

private:
    Ui::MainWindow *ui;
    bmpImage *image;
    std::ifstream bmpFile;
    std::ofstream saveFile;
    drawBMPImage *drawer;
    int mousePosX;
    int mousePosY;
    bool sucsess;
    int drawMode; // 0 - нет, 1 - точка, 2 - линия, 3 - окружность
    QVector<int> drawPointX;
    QVector<int> drawPointY;
    QColor color;
};
void MichinerCircle (bmpImage *image, int centerX, int centerY, int radius, int r, int g, int b);
void BresenhamAlgorithm(bmpImage *image, int x1, int y1, int x2, int y2, int r, int g, int b);

#endif // MAINWINDOW_H
