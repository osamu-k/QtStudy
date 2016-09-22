#include "standardpaths.h"
#include <QStandardPaths>
#include <QDebug>

StandardPaths::StandardPaths(QObject *parent) : QObject(parent)
{

}

QString StandardPaths::documentPath()
{
    QStringList pathList = QStandardPaths::standardLocations( QStandardPaths::DocumentsLocation );
    if( pathList.count() > 0 ){
        qDebug() << "Document Path: " << pathList.first();
        return pathList.first();
    }
    else{
        return QString();
    }
}
