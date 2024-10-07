#QT       += core gui serialport

#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#CONFIG += c++17

## 如果要禁用 Qt5 中的过时 API，可以取消下面的注释并设置适当的值
##DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x050000

#SOURCES += \
#    main.cpp \
#    dialog.cpp

#HEADERS += \
#    dialog.h

#FORMS += \
#    dialog.ui

## 默认的部署规则
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target





QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# 去掉与 Qt6 相关的配置
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

SOURCES += \
    main.cpp \
    dialog.cpp

HEADERS += \
    dialog.h

FORMS += \
    dialog.ui

# 默认的部署规则（如不需要，可以省略）
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
