# -------------------------------------------------
# Project created by QtCreator 2009-10-26T15:32:27
# -------------------------------------------------
CONFIG += uitools
TARGET = SADStepProgram
TEMPLATE = app
SOURCES += main.cc \
    mainwindow.cc \
    stepmenu.cpp \
    startmenu.cc \
    songmenu.cc \
    optionmenu.cc \
    GraphicsTimer.cc \
    gamemenu.cc \
    GameCanvas.cc \
    basemenuform.cpp \
    ArrowGraphicsSet.cpp \
    Arrow.cc \
    timeline.cpp \
    score.cpp \
    ScoreData.cpp \
    FileIOServer.cc \
    SongCatalogue.cc \
    SMFileReader.cc \
    musicplayer.cpp
HEADERS += mainwindow.h \
    stepmenu.h \
    startmenu.h \
    songmenu.h \
    optionmenu.h \
    GraphicsTimer.h \
    gamemenu.h \
    GameCanvas.h \
    basemenuform.h \
    ArrowGraphicsSet.h \
    Arrow.h \
    timeline.h \
    score.h \
    ScoreData.h \
    FileIOServer.h \
    SongReader.h \
    SongCatalogue.h \
    SMFileReader.h \
    StepReader.h \
    musicplayer.h
FORMS += songMenuForm.ui \
    optionmenu.ui \
    MMenuForm.ui \
    gamemenuform.ui \
    basemenuform.ui \
    stepmenu.ui
RESOURCES += MenuForms.qrc \
    ButtonsLib.qrc \
    Arrow.qrc
OTHER_FILES += bugs.txt
