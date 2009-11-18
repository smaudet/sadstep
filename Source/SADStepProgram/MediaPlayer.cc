#include "MediaPlayer.h"
#include <QFile>

MediaPlayer::MediaPlayer() {
    //preparation of the vlc command
    const char * const vlc_args[] = {
	"-I", "dummy", /* Don't use any interface */
	"--ignore-config", /* Don't use VLC's config */
	/*"--extraintf=logger",*/ //log anything
	"--verbose=2", //be much more verbose then normal for debugging purpose
    };
    _isPlaying=false;

    //Initialize an instance of vlc
    //a structure for the exception is needed for this initalization
    libvlc_exception_init(&_vlcexcep);

    //create a new libvlc instance
    _vlcinstance=libvlc_new(sizeof(vlc_args) / sizeof(vlc_args[0]),vlc_args,
			    &_vlcexcep);
    //raise (&_vlcexcep);

    // Create a media player playing environement
    _mp = libvlc_media_player_new (_vlcinstance, &_vlcexcep);
    //raise (&_vlcexcep);
}

MediaPlayer::~MediaPlayer() {
    /* Stop playing */
    libvlc_media_player_stop (_mp, &_vlcexcep);

    /* Free the media_player */
    libvlc_media_player_release (_mp);

    libvlc_release (_vlcinstance);
    //raise (&_vlcexcep);
}

MediaPlayer::MediaPlayer(QString file) {
    loadFile(file);
}

void MediaPlayer::changeVolume(int newVolume) {
    libvlc_exception_clear(&_vlcexcep);
    libvlc_audio_set_volume (_vlcinstance,newVolume , &_vlcexcep);
    raise(&_vlcexcep);
}

//TODO add support for coupling - this function is not actually intended for use
void MediaPlayer::mute() {
    libvlc_audio_set_mute(this->_vlcinstance,1,&_vlcexcep);
    _isMuted = true;
}

bool MediaPlayer::isMuted() {
    return _isMuted;
}

void MediaPlayer::pause() {
    if(libvlc_media_player_can_pause(_mp, &_vlcexcep)) {
        libvlc_media_player_pause(_mp,&_vlcexcep);
        _isPlaying = false;
    }
}

bool MediaPlayer::isPlaying() {
    return _isPlaying;
}

void MediaPlayer::stop() {
    libvlc_media_player_stop(_mp, &_vlcexcep);
    _isPlaying = false;
}

bool MediaPlayer::seek(float time) {
    if(libvlc_media_player_is_seekable(_mp,&_vlcexcep)) {
        libvlc_media_player_set_position(_mp,time,&_vlcexcep);
        return true;
    }
    return false;
}

float MediaPlayer::getTimePosition() {
    if(_isPlaying){
        return libvlc_media_player_get_position(_mp,&_vlcexcep);
    } else {
        return 0;
    }
}

void MediaPlayer::play() {
    if(libvlc_media_player_will_play(_mp,&_vlcexcep)){
        libvlc_media_player_play(_mp,&_vlcexcep);
        _isPlaying = true;
    }
}

bool MediaPlayer::loadFile(QString file) {
    if(QFile(file).exists()){
        stop();
        this->file = new QString(file);
        // TODO not final behavior
        return true;
    } else {
        return false;
    }
}

bool MediaPlayer::playFile(QString file) {
    if(libvlc_media_player_will_play(_mp, &_vlcexcep)){
    /* Create a new LibVLC media descriptor */
    _m = libvlc_media_new (_vlcinstance, file.toAscii(), &_vlcexcep);
    //raise(&_vlcexcep);
    libvlc_media_player_set_media (_mp, _m, &_vlcexcep);
    //raise(&_vlcexcep);
    /* Play */
    libvlc_media_player_play (_mp, &_vlcexcep );
    //raise(&_vlcexcep);
        _isPlaying=true;

        return true;
    } else {
        return false;
    }
}
void MediaPlayer::raise(libvlc_exception_t * ex)
{
    if (libvlc_exception_raised (ex))
    {
	fprintf (stderr, "error: %s\n", libvlc_exception_get_message(ex));
	exit (-1);

    }
}
