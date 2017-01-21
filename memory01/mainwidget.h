#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QLabel>
#include <QStack>
#include <QWidget>

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();

private slots:
    void allocMemory();
    void freeMemory();
    void refreshDisplay();

private:
    QLabel *m_labelMemSize = nullptr;
    QLabel *m_labelMaxMem = nullptr;
    QLabel *m_labelPageSize = nullptr;
    QLabel *m_labelUsed = nullptr;
    QLabel *m_labelFree = nullptr;
    QLabel *m_labelTotal = nullptr;
    QLabel *m_labelVirtual = nullptr;
    QLabel *m_labelResident = nullptr;

    QStack<char *> m_allocStack;
};

#endif // MAINWIDGET_H
