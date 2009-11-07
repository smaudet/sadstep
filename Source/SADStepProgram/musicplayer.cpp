#include "musicplayer.h"
#include <QSound>

MusicPlayer::MusicPlayer()
{
}


void MusicPlayer::playFile(QString file) {
    QSound::play(file);
}
