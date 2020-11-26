TEMPLATE = app

QT_VER = $$[QT_VERSION]
QT_PATH = $$[QT_INSTALL_PREFIX]

#message(Qt version is $${QT_VER})
#message(Qt install prefix is $${QT_PATH})

QT       += core

#QT       += gui

#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#QT       += network

#QT       += xml

QT       += testlib

#QT       += qml quick

#CONFIG += qmltestcase testcase

#CONFIG -= qt

#win32: CONFIG += console
macx: CONFIG -= app_bundle

CONFIG += debug_and_release

TARGET = mldll_qtest
CONFIG(debug, debug|release) {
    unix: TARGET = $$join(TARGET,,,_debug)
    else: TARGET = $$join(TARGET,,,d)
}

# Common config for qmake.
include($${PWD}/../config.pri)

# Default rules for buildoutput.
include($${PWD}/../distout.pri)

# Default rules for deployment.
include($${PWD}/../deploy.pri)


# Custom DEFINES and CONFIG
linux {
    message(Platform is linux: $${TARGET})

    CONFIG(debug, debug|release) {
        DEFINES += _DEBUG
    } else {
        DEFINES += NDEBUG
        DEFINES += NO_DEBUG_OUTPUT
    }
} else {
    error(Platform not supported: $${TARGET})
}


#message(C compiler preprocessor macros: $${DEFINES})
#message(C compiler flags: $${QMAKE_CFLAGS})
#message(C++ compiler flags: $${QMAKE_CXXFLAGS})
#message(linker flags: $${QMAKE_LFLAGS})

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =


# 多语言翻译文件
TRANSLATIONS +=

HEADERS +=

SOURCES += \
    testmain.cpp

FORMS +=

RESOURCES +=

OTHER_FILES +=


# 子工程
#include($${PWD}/subproj/subproj.pri)
include($${PWD}/testsetup/testsetup.pri)


# 程序编译时依赖的相关路径
DEPENDPATH += \
    $${PWD}/../incs \
    $${PWD}/../mldll

# 头文件包含路径
INCLUDEPATH += \
    $${PWD}/../incs \
    $${PWD}/../mldll


LIBS += -ldl -lrt

######################
linux {
    CONFIG(debug, debug|release) {
        #LIBS += $${PWD}/../libs/linux -lmylib_debug
        LIBS += $${DESTDIR}/mldll_debug_obj/memload.o
    } else {
        #LIBS += $${PWD}/../libs/linux -lmylib
        LIBS += $${DESTDIR}/mldll_obj/memload.o
    }
}
######################
