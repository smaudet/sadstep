#include "videoaudiotest.h"
#include "MediaPlayer.h"

#include <QtDebug>

QTEST_MAIN(VideoAudioTest)

VideoAudioTest::VideoAudioTest(){
    qDebug() << "Returning";
}

void VideoAudioTest::testAudio() {
    qDebug() << "testing";
    MediaPlayer* mp = new MediaPlayer();
    qDebug() << "player written";
    mp->playFile("Motteke! Sailor Fuku.avi");
    MediaPlayer* mp2 = new MediaPlayer();
    mp2->playFile("Motteke! Sailor Fuku.mp3");
    while(true){};
}
