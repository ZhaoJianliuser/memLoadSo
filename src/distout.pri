######################
# Win平台下配置
######################
win32 {
    # 输出目录
    contains(QT_ARCH, x86_64) {
        #message("system arch type is x64")
        CONFIG(debug, debug|release) {
            DESTDIR = $${_PRO_FILE_PWD_}/../build/win/x64/debug
        } else {
            DESTDIR = $${_PRO_FILE_PWD_}/../build/win/x64/release
        }
    } else {
        #message("system arch type is x86")
        CONFIG(debug, debug|release) {
            DESTDIR = $${_PRO_FILE_PWD_}/../build/win/x86/debug
        } else {
            DESTDIR = $${_PRO_FILE_PWD_}/../build/win/x86/release
        }
    }
    
    QMAKE_LIBDIR += $${DESTDIR}

    UI_DIR += $${DESTDIR}/$${TARGET}_ui
    OBJECTS_DIR += $${DESTDIR}/$${TARGET}_obj
    MOC_DIR += $${DESTDIR}/$${TARGET}_moc
    RCC_DIR += $${DESTDIR}/$${TARGET}_res

    # 程序编译时需要链接的库路径和库名
    LIBS += -L. -L$${DESTDIR} -L$${_PRO_FILE_PWD_}

    # 设置应用程序的图标
    #RC_ICONS += $${_PRO_FILE_PWD_}/res/logo.ico
}

######################
# Mac平台下配置
######################
macos {
    # 输出目录
    CONFIG(debug, debug|release) {
        DESTDIR = $${_PRO_FILE_PWD_}/../build/mac/debug
    } else {
        DESTDIR = $${_PRO_FILE_PWD_}/../build/mac/release
    }

    QMAKE_LIBDIR += $${DESTDIR}

    UI_DIR += $${DESTDIR}/$${TARGET}_ui
    OBJECTS_DIR += $${DESTDIR}/$${TARGET}_obj
    MOC_DIR += $${DESTDIR}/$${TARGET}_moc
    RCC_DIR += $${DESTDIR}/$${TARGET}_res

    # 程序编译时需要链接的库路径和库名
    LIBS += -L. -L$${DESTDIR} -L$${_PRO_FILE_PWD_}

    # 设置应用程序的图标
    #ICON += $${_PRO_FILE_PWD_}/res/logo.icns
}

######################
# Linux平台下配置
######################
linux {
    # 输出目录
    CONFIG(debug, debug|release) {
        DESTDIR = $${_PRO_FILE_PWD_}/../build/linux/debug
    } else {
        DESTDIR = $${_PRO_FILE_PWD_}/../build/linux/release
    }

    QMAKE_LIBDIR += $${DESTDIR}

    UI_DIR += $${DESTDIR}/$${TARGET}_ui
    OBJECTS_DIR += $${DESTDIR}/$${TARGET}_obj
    MOC_DIR += $${DESTDIR}/$${TARGET}_moc
    RCC_DIR += $${DESTDIR}/$${TARGET}_res

    # 程序编译时需要链接的库路径和库名
    LIBS += -L. -L$${DESTDIR} -L$${_PRO_FILE_PWD_}

    # 设置应用程序的图标
    # Linux 平台需要 appname.desktop 描述文件，说明程序的信息
    # 程序运行时的标题设置, 可使用 setWindowTitle 方法设置
    # 程序运行时的图标设置, 可使用 setWindowIcon 方法设置
}
