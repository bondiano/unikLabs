#include <ctime>
#include <QDebug>
#include <iostream>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "menu.h"
#include "indexfile.h"
#include "valuefile.h"

using namespace std;

int main(int argc, char *argv[])
{
    ofstream ("base.bin");
    ofstream ("idx_base.bin");
    srand(time(0));
    qDebug() << "-- Start app --";
    int n = 0;
    cout << "Item in block\n";
    cin >> n;
    IndexFile myIndex("idx.bin", n);
    ValueFile myFile("data.bin");
//    QGuiApplication app(argc, argv);

//    QQmlApplicationEngine engine;
//    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
//    QList<QObject*> window = engine.rootObjects();
//    if (window.isEmpty())
//        return -1;

//    QObject *mainForm = window[0]->findChild<QObject*>("mainForm");
//    return app.exec();
}
