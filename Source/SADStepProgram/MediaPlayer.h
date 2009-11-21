#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H

#include <vlc/vlc.h>
#include <QString>
#include <QWidget>

class MediaPlayer
{
public:
    MediaPlayer();
    MediaPlayer(QString file);
    ~MediaPlayer();
    //Won't accept Unicode file names due to limitations in VLC
    bool playFile(QString file);
    
    bool playFileInWindow(QString& file, QWidget* window);
	void changeVolume(int newVolume);
    void stop();
    void play();
    void pause();
    bool loadFile(QString file);
    bool isPlaying();
    bool isMuted();
    void mute();
    bool seek(float time);
    float getTimePosition();
private:
    QString* file;
    void raise(libvlc_exception_t * ex);
    bool _isPlaying;
    bool _isMuted;
    libvlc_exception_t _vlcexcep;
    libvlc_instance_t *_vlcinstance;
    libvlc_media_player_t *_mp;
    libvlc_media_t *_m;
};

#endif // MEDIAPLAYER_H
