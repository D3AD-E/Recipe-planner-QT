QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    entrydialog.cpp \
    exceptionhandler.cpp \
    ingredientslistmodel.cpp \
    ingredientssortproxymodel.cpp \
    ingredientstablemodel.cpp \
    jsonrecipehelper.cpp \
    main.cpp \
    mainwindow.cpp \
    menudialog.cpp \
    recipe.cpp \
    recipeslistmodel.cpp \
    recipesservice.cpp \
    recipestablemodel.cpp

HEADERS += \
    entrydialog.h \
    exceptionhandler.h \
    ingredientslistmodel.h \
    ingredientssortproxymodel.h \
    ingredientstablemodel.h \
    jsonrecipehelper.h \
    mainwindow.h \
    menudialog.h \
    recipe.h \
    recipeslistmodel.h \
    recipesservice.h \
    recipestablemodel.h

FORMS += \
    entrydialog.ui \
    mainwindow.ui \
    menudialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
