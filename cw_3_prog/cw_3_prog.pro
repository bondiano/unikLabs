QT += gui qml core
TEMPLATE = app
CONFIG += c++11 console

SOURCES += main.cpp \
    indexfile.cpp \
    valuefile.cpp \
    adt_spareindex.cpp \
    menu.cpp

DISTFILES += \
    README.md \
    MenuForm.ui.qml \
    Menu.qml \
    main.qml \
    Button.qml

HEADERS += \
    indexfile.h \
    valuefile.h \
    fileinterfaсe.h \
    adt_spareindex.h \
    item.h \
    menu.h

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
