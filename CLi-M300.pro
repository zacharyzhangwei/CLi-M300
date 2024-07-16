QT       += core gui serialport sql
QT       += core gui printsupport
greaterThan(QT_MAJOR_VERSION, 4):
QT += widgets printsupport

CONFIG += c++11
TARGET = CLi-M300
TEMPLATE = app
CONFIG += resources_big
QT       += network
VERSION = 1.0.231112.1900
# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
LIBS += -Ldll -lws2_32

QT       += sql
INCLUDEPATH += $$PWD/lib \
               $$PWD/lib/libmodbus \
               $$PWD/module \
               $$PWD/module/modbus \
               $$PWD/module/print \
               $$PWD/commom \
               $$PWD/control \
               $$PWD/data \
               $$PWD/ui  \
               $$PWD/lib/libpeak  \
               $$PWD/lib/qcustomplot  \

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    common/cconfigure.cpp \
    common/cglobal.cpp \
    common/clog.cpp \
    control/ccardmanager.cpp \
    control/cconfgmanager.cpp \
    control/cdbmanager.cpp \
    control/chismanager.cpp \
    control/cinitmanager.cpp \
    control/cloginmanager.cpp \
    control/cprintmanager.cpp \
    control/cqcmanager.cpp \
    control/crecordmanger.cpp \
    control/csocketmanager.cpp \
    control/ctestmanager.cpp \
    control/hl7_manage.cpp \
    data/cdbcache.cpp \
    data/cdbmodule.cpp \
    data/cdbsession.cpp \
    data/cdbsqllite.cpp \
    data/cserialport.cpp \
    lib/qcustomplot/qcustomplot.cpp \
    main.cpp \
    mainwindow.cpp \
    module/socket/cscoketpro.cpp \
    module/socket/csmodule.cpp \
    module/socket/sockettool.cpp \
    module/socket/ssession.cpp \
    ui/cinitwidget.cpp \
    ui/cloginwidget.cpp \
    ui/cmsgdialog.cpp \
    ui/ccalibwidget.cpp \
    ui/crecordwidget.cpp \
    ui/calendarwidget.cpp \
    ui/cqcwidget.cpp \
    ui/csetwidget.cpp \
    ui/cpowerwidget.cpp \
    common/ctools.cpp \
    control/csetmanager.cpp \
    module/modbus/cmodule.cpp \
    module/modbus/cmtsession.cpp \
    module/modbus/cpesession.cpp \
    module/modbus/cserialpro.cpp \
    module/modbus/csession.cpp \
    module/modbus/modbustool.cpp \
    module/print/cpmodule.cpp \
    module/print/cpserialpro.cpp \
    module/print/psession.cpp \
    lib/libmodbus/modbus-data.c \
    lib/libmodbus/modbus-rtu.c \
    lib/libmodbus/modbus-tcp.c \
    lib/libmodbus/modbus.c \
    control/cmodbusmanager.cpp \
    control/chlcpeakmanager.cpp \
    ui/cuserwidget.cpp \
    ui/mypaint.cpp \
    module/4g/c4gcache.cpp \
    module/4g/c4gmodule.cpp \
    module/4g/runguard.cpp \
    control/c4gmanager.cpp \
    ui/ctestwidget.cpp \
    control/cmgrmsgrouter.cpp \
    common/piebutton.cpp \
    ui/ccalibwidget.cpp

HEADERS += \
    common/cconfigure.h \
    common/cglobal.h \
    common/clog.h \
    common/globals.h \
    control/ccardmanager.h \
    control/cconfgmanager.h \
    control/cdbmanager.h \
    control/chismanager.h \
    control/cinitmanager.h \
    control/cloginmanager.h \
    control/cprintmanager.h \
    control/cqcmanager.h \
    control/crecordmanger.h \
    control/csocketmanager.h \
    control/ctestmanager.h \
    control/hl7_manage.h \
    control/imhelper.h \
    data/IDBModuleCB.h \
    data/IDBSession.h \
    data/cdbcache.h \
    data/cdbmodule.h \
    data/cdbsession.h \
    data/cdbsqllite.h \
    data/cserialport.h \
    lib/qcustomplot/qcustomplot.h \
    mainwindow.h \
    module/socket/TCPModule.h \
    module/socket/cscoketpro.h \
    module/socket/csmodule.h \
    module/socket/sockettool.h \
    module/socket/ssession.h \
    ui/cinitwidget.h \
    ui/cloginwidget.h \
    ui/cmsgdialog.h \
    ui/ccalibwidget.h \
    ui/crecordwidget.h \
    ui/ccalibwidget.h \
    ui/calendarwidget.h \
    ui/cqcwidget.h \
    ui/csetwidget.h \
    ui/cpowerwidget.h \
    common/ctools.h \
    control/csetmanager.h \
    module/modbus/cmodule.h \
    module/modbus/cserialpro.h \
    module/modbus/csession.h \
    module/modbus/IModule.h \
    module/modbus/modbustool.h \
    module/print/cpmodule.h \
    module/print/cpserialpro.h \
    module/print/IPModule.h \
    module/print/psession.h \
    module/ISession.h \
    lib/libmodbus/config.h \
    lib/libmodbus/modbus-private.h \
    lib/libmodbus/modbus-rtu-private.h \
    lib/libmodbus/modbus-rtu.h \
    lib/libmodbus/modbus-tcp-private.h \
    lib/libmodbus/modbus-tcp.h \
    lib/libmodbus/modbus-version.h \
    lib/libmodbus/modbus.h \
    control/cmodbusmanager.h \
    lib/libpeak/ical.h \
    control/chlcpeakmanager.h \
    ui/cuserwidget.h \
    ui/mypaint.h \
    module/4g/c4gcache.h \
    module/4g/c4gmodule.h \
    module/4g/runguard.h \
    control/c4gmanager.h \
    ui/ctestwidget.h \
    control/cmgrmsgrouter.h \
    common/piebutton.h \
    ui/ccalibwidget.h

FORMS += \
    mainwindow.ui \
    ui/cinitwidget.ui \
    ui/cmsgdialog.ui \
    ui/crecordwidget.ui \
    ui/calendarwidget.ui \
    ui/cqcwidget.ui \
    ui/ccalibwidget.ui \
    ui/csetwidget.ui \
    ui/cpowerwidget.ui \
    ui/cuserwidget.ui \
    ui/mypaint.ui \
    ui/ctestwidget.ui \
    ui/cloginwidget.ui \
    ui/ccalibwidget.ui




#translator

TRANSLATIONS += gtsoft_zh.ts  gtsoft_en.ts
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    generalinstsoft.qrc

RC_ICONS =logo.ico


#生成PDB文件
QMAKE_LFLAGS_RELEASE += /MAP
QMAKE_CFLAGS_RELEASE += /Zi
QMAKE_LFLAGS_RELEASE += /debug /opt:ref

QMAKE_CXXFLAGS_RELEASE += $$QMAKE_CFLAGS_RELEASE_WITH_DEBUGINFO
QMAKE_LFLAGS_RELEASE += $$QMAKE_LFLAGS_RELEASE_WITH_DEBUGINFO

#链接DbgHelp库
LIBS += -lDbgHelp



##添加管理员权限
#QMAKE_LFLAGS += /MANIFESTUAC:\"level=\'requireAdministrator\' uiAccess=\'false\'\"

#INCLUDEPATH += "D:\\Visual  Leak Detector\\include"

#LIBS += "D:\\Visual Leak Detector\\lib\Win32\\vld.lib"

#调用manifest
#win32 {
 #   QMAKE_POST_LINK += mt -manifest $$PWD/manifest.xml -outputresource:$$OUT_PWD/release/$$TARGET".exe" $$escape_expand(\n\t)
#}
