#-------------------------------------------------
#
# Project created by QtCreator 2012-03-27T13:57:13
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = DCT
TEMPLATE = app


SOURCES += main.cpp\
    libs.cpp \
    fundamental.cpp \
    1DDCT.cpp \
    2DDCT.cpp \
    report.cpp \
    1Dui.cpp \
    2Dui.cpp \
    2Dblocks_ui.cpp \
    Quantilization.cpp \
    Quantilize_ui.cpp

HEADERS  += \
    fundamental.h \
    libs.h \
    1DDCT.h \
    2DDCT.h \
    report.h \
    Quantilization.h

FORMS    += mainwindow.ui \
    report.ui
win32 {
            INCLUDEPATH+="D:/Program Files/opencv/include/opencv"
            LFLAGS = -static-libgcc
            LIBS+="D:\Program Files\opencv\build\x86\vc10\lib\opencv_core231d.lib"
            LIBS+="D:\Program Files\opencv\build\x86\vc10\lib\opencv_highgui231d.lib"
            DEPENDPATH+="D:\Program Files\opencv\build\x86\vc10\bin"
}

unix {
            LIBS+= -lGLU -lopencv_core -lopencv_highgui -lopencv_imgproc -lqwt
}

RESOURCES += \
    icon.qrc

