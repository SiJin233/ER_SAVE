QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    about.cpp \
    main.cpp \
    er_save.cpp \
    notes.cpp \
    set.cpp

HEADERS += \
    about.h \
    er_save.h \
    notes.h \
    set.h

FORMS += \
    about.ui \
    er_save.ui \
    notes.ui \
    set.ui

TRANSLATIONS += \
    ER_SAVE_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

RC_FILE = ICON.rc

