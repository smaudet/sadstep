#ifndef SONGCATALOGUE_H
#define SONGCATALOGUE_H

#include <QList>
#include <QDir>
#include <QString>

class SongCatalogue
{
public:
    //TODO Replace with Macro or Datatype
    const QList<QString>* const getFileNames() const;
    //TODO Needs to be deprecated
    QString getFileName(int index) const;
    static SongCatalogue* const getInstance();
private:
    SongCatalogue();
    static SongCatalogue* singInst;
    static bool singleton;
    char* baseDir;
    QDir* QbaseDir;
    QList<QString>* list;
};

#endif // SONGCATALOGUE_H
