To compile and run, the following are required (only Windows supported atm)

The lib folder for the VLC SDK in the base directory
The include folder for the VLC SDK in the base directory
QT

The VLC Dlls must be copied into the run (usually debug) directory along with the plugins directory if you
want any sort of media (video/audio) support.

The VideoAudioTest class is provided but not included in the .pro makefile as a means to test the functionality
of the media player.

A Songs directory is also required to be placed in the run directory for any songs to be played.