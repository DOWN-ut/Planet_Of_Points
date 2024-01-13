QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

LIBS += -lGLEW -lglfw
LIBS += -lGL -lGLU

SOURCES += \
    cell.cpp \
    gravitymanager.cpp \
    grid.cpp \
    main.cpp \
    mainwindow.cpp \
    point.cpp \
    points.cpp \
    window.cpp \
    glwidget.cpp

HEADERS += \
    cell.h \
    gravitymanager.h \
    grid.h \
    mainwindow.h \
    point.h \
    points.h \
    window.h \
    glwidget.h

FORMS += \
    mainwindow.ui

RESOURCES += \
        shaders.qrc

TRANSLATIONS += \
    POP_en_GB.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
