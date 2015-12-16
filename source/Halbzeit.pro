#-------------------------------------------------
#
# Project created by QtCreator 2011-03-04T17:34:20
#
#-------------------------------------------------

QT       += gui core widgets opengl
TARGET = Sonnensystem
TEMPLATE = app

win32 {
    CONFIG += console #Notwendig in 5.5, da sonst qMain gesucht wird und nicht gefunden wird... eher ein Bug in Qt5.5?
    LIBS += -lopengl32
}
macx {
    QMAKE_MAC_SDK = macosx10.11
}

SGFRAMEWORKPATH = "./../SGFrameworkLib"
PRE_TARGETDEPS += $${SGFRAMEWORKPATH}/libSGFramework.a
INCLUDEPATH += $${SGFRAMEWORKPATH}

LIBS += $${SGFRAMEWORKPATH}/libSGFramework.a
DEFINES += SRCDIR=\\\"$${_PRO_FILE_PWD_}\\\"

SOURCES += \
    fussballstadionscene.cpp \
    halbzeitgame.cpp

FORMS +=

HEADERS += \
    fussballstadionscene.h \
    halbzeitgame.h

RESOURCES += \
    resources.qrc
