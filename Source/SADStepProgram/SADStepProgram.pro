# -------------------------------------------------
# Project created by QtCreator 2009-10-26T15:32:27
# -------------------------------------------------
# QT += testlib
LIBS += -L"lib"
LIBS += -lvlc
LIBS += -lSDL
win32 {
LIBS += -lmingw32 \
    -mwindows
}
unix {
LIBS += -L/usr/lib
}
INCLUDEPATH += "include" \
    "include/SDL"
unix {
    INCLUDEPATH += "/usr/include/SDL"
}

# CONFIG += uitools
TARGET = SADStepProgram
TEMPLATE = app
SOURCES += GraphicsTimer.cc \
    GameCanvas.cc \
    ArrowGraphicsSet.cpp \
    Arrow.cc \
    ScoreData.cpp \
    FileIOServer.cc \
    SongCatalogue.cc \
    SMFileReader.cc \
    MediaPlayer.cc \
    Tests.cc \
    main.cc \
    NotesData.cc \
    Skin.cc \
    MainWindow.cc \
    Timeline.cpp \
    StepMenu.cpp \
    StartMenu.cc \
    SongMenu.cc \
    Score.cpp \
    ProfileMenu.cpp \
    Profile.cpp \
    BaseMenuForm.cpp \
    ScoreEvaluator.cpp \
    GameMenu.cc
HEADERS += GraphicsTimer.h \
    GameCanvas.h \
    ArrowGraphicsSet.h \
    Arrow.h \
    ScoreData.h \
    FileIOServer.h \
    SongReader.h \
    SongCatalogue.h \
    SMFileReader.h \
    StepReader.h \
    MediaPlayer.h \
    Tests.h \
    NotesData.h \
    Skin.h \
    ProjectHeader.h \
    Timeline.h \
    StepMenu.h \
    StartMenu.h \
    SongMenu.h \
    ProfileMenu.h \
    Profile.h \
    BaseMenuForm.h \
    Score.h \
    ScoreEvaluator.h \
    MainWindow.h \
    GameMenu.h
FORMS += songMenuForm.ui \
    optionmenu.ui \
    MMenuForm.ui \
    gamemenuform.ui \
    basemenuform.ui \
    stepmenu.ui \
    profileMenuForm.ui
RESOURCES += MenuForms.qrc \
    ButtonsLib.qrc \
    Arrow.qrc \
    Arrows2.qrc \
    Arrows3.qrc \
    Arrows4.qrc \
    Arrows5.qrc
OTHER_FILES += bugs.txt
