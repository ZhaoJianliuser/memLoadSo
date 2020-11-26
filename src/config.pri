CONFIG += debug_and_release

CONFIG(debug, debug|release) {
    CONFIG += debug
    CONFIG += qml_debug
    CONFIG += warn_on

    DEFINES += QT_DEBUG
    DEFINES += QT_QML_DEBUG
    DEFINES += QT_MESSAGELOGCONTEXT
} else {
    CONFIG += release
    CONFIG += qml_release
    CONFIG += warn_off

    DEFINES += QT_NO_DEBUG
    DEFINES += QT_NO_QML_DEBUG
    DEFINES += QT_NO_MESSAGELOGCONTEXT
    #DEFINES += QT_NO_DEBUG_OUTPUT
    #DEFINES += QT_NO_WARNING_OUTPUT
    #DEFINES += QT_NO_INFO_OUTPUT
}

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DEFINES += QT_NO_CAST_FROM_ASCII
DEFINES += QT_NO_CAST_TO_ASCII
DEFINES += QT_NO_CAST_FROM_BYTEARRAY
DEFINES += QT_NO_URL_CAST_FROM_STRING
DEFINES += QT_USE_QSTRINGBUILDER

# Disable warning C4819 for msvc
msvc:QMAKE_CXXFLAGS += -execution-charset:utf-8
msvc:QMAKE_CXXFLAGS += -source-charset:utf-8
msvc:QMAKE_CXXFLAGS_WARN_ON += -wd4819

