#ifndef STANDARDPATHS_H
#define STANDARDPATHS_H

#include <QObject>

class StandardPaths : public QObject
{
    Q_OBJECT
public:
    explicit StandardPaths(QObject *parent = 0);

signals:

public slots:
    QString documentPath();
};

#endif // STANDARDPATHS_H
