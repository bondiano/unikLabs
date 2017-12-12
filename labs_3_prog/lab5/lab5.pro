TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    list.cpp\
    sqmatrix.cpp \
    menu.cpp \
    sqmatrixdet.cpp \
    namedmatrix.cpp

HEADERS += \
    list.h\
    sqmatrix.h \
    menu.h \
    sqmatrixdet.h \
    namedmatrix.h
