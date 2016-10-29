#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

#include <QTextEdit>

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();

private slots:
    void clearClicked();
    void sendClicked();

private:
    QTextEdit *m_textLog;
    QTextEdit *m_textInput;
};

#endif // MAINWIDGET_H
