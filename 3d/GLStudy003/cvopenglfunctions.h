#ifndef CVOPENGLFUNCTIONS_H
#define CVOPENGLFUNCTIONS_H

#include <QOpenGLFunctions>

class CVOpenGLFunctions : public QOpenGLFunctions
{
public:
    static CVOpenGLFunctions *instance();

private:
    CVOpenGLFunctions();

    static CVOpenGLFunctions *m_instance;
};

#endif // CVOPENGLFUNCTIONS_H
