#include <iostream>
#include <QGuiApplication>

#include "menu.cpp"

using namespace std;

int main(int argc, char *argv[])
{
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    QList<QObject*> window = engine.rootObjects();
    if (window.isEmpty())
        return -1;

    QObject *mainForm = window[0]->findChild<QObject*>("mainForm");
    menu::initMenu(mainForm);
    return app.exec();
}
