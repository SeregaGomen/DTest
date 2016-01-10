#-------------------------------------------------
#
# Project created by QtCreator 2015-09-15T09:42:18
#
#-------------------------------------------------
#QMAKE_CXXFLAGS += -std=c++0x
#DEFINES += __GXX_EXPERIMENTAL_CXX0X__

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DTest
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    test1dialog.cpp \
    studentdialog.cpp \
    resultdialog.cpp \
    tabledialog.cpp \
    exportdialog.cpp \
    test2dialog.cpp \
    test3dialog.cpp \
    test4dialog.cpp \
    test5dialog.cpp \
    test0dialog.cpp \
    getpatientdialog.cpp

HEADERS  += mainwindow.h \
    test1dialog.h \
    studentdialog.h \
    resultdialog.h \
    tabledialog.h \
    exportdialog.h \
    test2dialog.h \
    test3dialog.h \
    test4dialog.h \
    test5dialog.h \
    test0dialog.h \
    getpatientdialog.h

FORMS    += mainwindow.ui \
    test1dialog.ui \
    studentdialog.ui \
    resultdialog.ui \
    tabledialog.ui \
    exportdialog.ui \
    test2dialog.ui \
    test3dialog.ui \
    test4dialog.ui \
    test5dialog.ui \
    test0dialog.ui \
    getpatientdialog.ui

RESOURCES += \
    DTest.qrc


win32 {

    RC_FILE += DTest.rc
}


