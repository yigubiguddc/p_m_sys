QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# solve the problem of Chinese Garbled and Compilation error
msvc {
      QMAKE_CFLAGS += /utf-8
      QMAKE_CXXFLAGS += /utf-8
}


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    feecalculate.cpp \
    fileoperation.cpp \
    header.cpp \
    main.cpp \
    showvehicle.cpp \
    tips.cpp \
    vehicle.cpp \
    vehicleduty.cpp \
    widget.cpp

HEADERS += \
    feecalculate.h \
    fileoperation.h \
    header.h \
    showvehicle.h \
    tips.h \
    vehicle.h \
    vehicleduty.h \
    widget.h

FORMS += \
    feecalculate.ui \
    fileoperation.ui \
    showvehicle.ui \
    tips.ui \
    vehicleduty.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

DISTFILES +=

