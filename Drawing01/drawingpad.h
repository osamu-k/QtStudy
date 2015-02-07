/**
drawingpad.h

Copyright (c) Osamu Kobayashi

This software is released under the MIT License.
http://opensource.org/licenses/mit-license.php
*/

#ifndef DRAWINGPAD_H
#define DRAWINGPAD_H

#include <QList>
#include <QPushButton>
#include <QWidget>

#include "bytearraysocket.h"
#include "listener.h"
#include "serversocket.h"

class Canvas;
class ServerSocket;
class WidthSelector;

class QLayout;
class QLineEdit;

class DrawingPad : public QWidget
{
    Q_OBJECT

public:
    DrawingPad(QWidget *parent = 0);
    ~DrawingPad();

    static const int defaultPort;
    static const char * const defaultServer;

private slots:
    void widthSelected(int);
    void newButtonClicked();
    void openButtonClicked();
    void saveButtonClicked();
    void saveAsPNGButtonClicked();
    void listenButtonClicked();
    void connectButtonClicked();
    void newConnection( ServerSocket * );
    void connectedToServer();
    void disconnectedFromServer();

private:
    QLayout *setupFileButtons();

    Canvas *m_canvas;
    QPushButton *m_listenButton;
    QLineEdit *m_listenPortEdit;
    QPushButton *m_connectButton;
    QLineEdit *m_connectAddressEdit;
    QLineEdit *m_connectPortEdit;

    QList<WidthSelector *> m_widthSelectorList;

    Listener m_listener;
    ByteArraySocket m_clientSocket;

    bool m_connected;
};

#endif // DRAWINGPAD_H
