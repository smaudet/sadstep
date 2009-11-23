# -------------------------------------------------
# Project created by QtCreator 2009-10-26T15:32:27
# -------------------------------------------------
# QT += testlib
LIBS += -L"lib" \
    -lvlc
INCLUDEPATH += "include"
CONFIG += uitools
TARGET = SADStepProgram
TEMPLATE = app
SOURCES += Arrow.cc \
    ArrowGraphicsSet.cpp \
    FileIOServer.cc \
    GameCanvas.cc \
    GraphicsTimer.cc \
    MediaPlayer.cc \
    NotesData.cc \
    SMFileReader.cc \
    ScoreData.cpp \
    SongCatalogue.cc \
    Tests.cc \
    basemenuform.cpp \
    gamemenu.cc \
    main.cc \
    optionmenu.cc \
    profilemenu.cpp \
    score.cpp \
    songmenu.cc \
    startmenu.cc \
    stepmenu.cpp \
    timeline.cpp \
    mainwindow.cc \
    testtimer.cpp
HEADERS += Arrow.h \
    ArrowGraphicsSet.h \
    FileIOServer.h \
    GameCanvas.h \
    GraphicsTimer.h \
    MediaPlayer.h \
    NotesData.h \
    SMFileReader.h \
    ScoreData.h \
    SongCatalogue.h \
    SongReader.h \
    StepReader.h \
    Tests.h \
    basemenuform.h \
    gamemenu.h \
    optionmenu.h \
    profilemenu.h \
    score.h \
    songmenu.h \
    startmenu.h \
    stepmenu.h \
    timeline.h \
    mainwindow.h \
    testtimer.h
FORMS += MMenuForm.ui \
    basemenuform.ui \
    gamemenuform.ui \
    optionmenu.ui \
    profileMenuForm.ui \
    stepmenu.ui \
    songMenuForm.ui
RESOURCES += Arrow.qrc \
    ButtonsLib.qrc \
    MenuForms.qrc
OTHER_FILES += bugs.txt
