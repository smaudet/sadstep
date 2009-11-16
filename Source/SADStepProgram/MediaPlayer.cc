#include "MediaPlayer.h"

MediaPlayer::MediaPlayer() {
    //preparation of the vlc command
    const char * const vlc_args[] = {
              "-I", "dummy", /* Don't use any interface */
              "--ignore-config", /* Don't use VLC's config */
              /*"--extraintf=logger",*/ //log anything
              "--verbose=2", //be much more verbose then normal for debugging purpose
              };
    //Initialize an instance of vlc
    //a structure for the exception is needed for this initalization
    libvlc_exception_init(&_vlcexcep);

    //create a new libvlc instance
    _vlcinstance=libvlc_new(sizeof(vlc_args) / sizeof(vlc_args[0]), vlc_args,&_vlcexcep);  //tricky calculation of the char space used
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

void MediaPlayer::raise(libvlc_exception_t * ex)
{
    if (libvlc_exception_raised (ex))
    {
         fprintf (stderr, "error: %s\n", libvlc_exception_get_message(ex));
         exit (-1);
    }
}

void MediaPlayer::playFile(QString file) {
    /* Create a new LibVLC media descriptor */
    _m = libvlc_media_new (_vlcinstance, file.toAscii(), &_vlcexcep);
    //raise(&_vlcexcep);   
    libvlc_media_player_set_media (_mp, _m, &_vlcexcep);
    //raise(&_vlcexcep);
    /* Play */
    libvlc_media_player_play (_mp, &_vlcexcep );
    //raise(&_vlcexcep);
}

void MediaPlayer::stop() {
    libvlc_media_player_stop(_mp, &_vlcexcep);
}
