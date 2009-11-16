#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H

#include <vlc/vlc.h>
#include <QString>

class MediaPlayer
{
public:
    MediaPlayer();
    ~MediaPlayer();
    void playFile(QString file);
    void raise(libvlc_exception_t * ex);
    void stop();
private:
    libvlc_exception_t _vlcexcep;
    libvlc_instance_t *_vlcinstance;
    libvlc_media_player_t *_mp;
    libvlc_media_t *_m;
};

#endif // MEDIAPLAYER_H
