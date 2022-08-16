QT += core gui sql
QT += widgets
greaterThan(QT_MAJOR_VERSION, 5)
CONFIG += c++11

TARGET = JI-quotes
TEMPLATE = app

SOURCES += \
    main.cpp \
    src/datedelegate.cpp \
    src/mainwindow.cpp \
    src/configurationdialog.cpp \
    src/customsortfilterproxymodel.cpp \
    src/dbmanager.cpp \
    src/exportdialog.cpp \
    src/quotedialog.cpp \
    src/topicsdialog.cpp

HEADERS += \
    src/datedelegate.h \
    src/mainwindow.h \
    src/configurationdialog.h \
    src/customsortfilterproxymodel.h \
    src/dbmanager.h \
    src/exportdialog.h \
    src/quotedialog.h \
    src/topicsdialog.h

FORMS += \
    forms/configurationdialog.ui \
    forms/exportdialog.ui \
    forms/mainwindow.ui \
    forms/quotedialog.ui \
    forms/topicsdialog.ui

RESOURCES += \
    resources/resources.qrc

DISTFILES += \
    ../README.md \
    resources/translations/JI-quotes_es_AR.ts

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

## You can also make your code fail to compile if it uses deprecated APIs.
## In order to do so, uncomment the following line.
## You can also select to disable deprecated APIs only up to a certain version of Qt.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

## Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target
