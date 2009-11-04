CONFIG += uitools
OTHER_FILES += Ok.bmp \
    Cancel.bmp
HEADERS += stepmenu.h \
    songmenu.h \
    startmenu.h \
    basemenuform.h \
    gamemenu.h \
    optionmenu.h
SOURCES += stepmenu.cpp \
    songmenu.cc \
    startmenu.cc \
    menuInit.cpp \
    basemenuform.cpp \
    gamemenu.cc \
    optionmenu.cc
FORMS += songMenuForm.ui \
    MMenuForm.ui \
    basemenuform.ui \
    stepmenu.ui \
    gamemenuform.ui \
    optionmenu.ui
RESOURCES += MenuForms.qrc \
    ButtonsLib.qrc
