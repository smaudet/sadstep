#ifndef VIDEOAUDIOTEST_H
#define VIDEOAUDIOTEST_H

#include <QObject>
#include <QtTest/QtTest>

class VideoAudioTest: public QObject
{
    Q_OBJECT
public:
    VideoAudioTest();
private slots:
    void testAudio();
};

#endif // VIDEOAUDIOTEST_H
