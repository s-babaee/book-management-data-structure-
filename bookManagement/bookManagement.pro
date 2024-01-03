QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addbook.cpp \
    adminmenu.cpp \
    basket.cpp \
    booklist.cpp \
    edit.cpp \
    main.cpp \
    mainwindow.cpp \
    order.cpp \
    search.cpp \
    usermenu.cpp

HEADERS += \
    addbook.h \
    adminmenu.h \
    basket.h \
    booklist.h \
    edit.h \
    mainwindow.h \
    order.h \
    search.h \
    usermenu.h

FORMS += \
    addbook.ui \
    adminmenu.ui \
    basket.ui \
    booklist.ui \
    edit.ui \
    mainwindow.ui \
    order.ui \
    search.ui \
    usermenu.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
