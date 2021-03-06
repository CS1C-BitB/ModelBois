#-------------------------------------------------
#
# Project created by QtCreator 2018-10-30T14:05:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ModelBois
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

test: DEFINES += UNITTEST

INCLUDEPATH += $$PWD/src

SOURCES += \
    src/main.cpp \
    src/MainWindow.cpp \
    src/Shape.cpp \
    src/Line.cpp \
    src/PolyLine.cpp \
    src/Rectangle.cpp \
    src/Polygon.cpp \
    src/Ellipse.cpp \
    src/Text.cpp \
    src/Canvas.cpp \
    src/Storage.cpp \
    src/ShapeListModel.cpp \
    src/PropertyDelegate.cpp \
    src/PropertyItem.cpp \
    test/testShapes.cpp \
    src/Sort.cpp \
    src/DetailView.cpp \
    src/fileparser.cpp \
    src/login.cpp \
    src/Serializer.cpp \
    src/About.cpp \
    src/ItemButton.cpp \
    src/FontSizeComboBox.cpp

HEADERS += \
    src/MainWindow.h \
    src/Shape.h \
    src/Line.h \
    src/PolyLine.h \
    src/Rectangle.h \
    src/Polygon.h \
    src/Ellipse.h \
    src/Text.h \
    src/Canvas.h \
    src/Storage.h \
    src/ShapeListModel.h \
    src/PropertyDelegate.h \
    src/PropertyItem.h \
    src/Shapes.h \
    test/Tests.h \
    src/Serializer.h \
    src/LinkedList.h \
    src/VectorNode.h \
    src/vector.h \
    src/Sort.h \
    src/DetailView.h \
    src/fileparser.h \
    src/login.h \
    src/About.h \
    src/ItemButton.h \
    src/FontSizeComboBox.h

FORMS += \
    src/MainWindow.ui \
    src/DetailView.ui \
    src/login.ui \
    src/About.ui \
    src/ItemButton.ui

# Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target

shapefile.files = myShapes.txt
shapefile.path = $$OUT_PWD

INSTALLS += shapefile

RESOURCES += \
    res/icons.qrc

DISTFILES += \
    ModelBois/myShapes.txt
