#ifndef SONGREADER_H
#define SONGREADER_H

class SongReader
{
public:
    SongReader();
    virtual QString getSongFile() = 0;
private:
};

#endif // SONGREADER_H
