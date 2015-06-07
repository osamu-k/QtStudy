#ifndef LINEWIDTHDIALOG_H
#define LINEWIDTHDIALOG_H

#include <QDialog>
#include <QSpinBox>

class LineWidthDialog : public QDialog
{
    Q_OBJECT

public:
    LineWidthDialog(QWidget *parent = 0);
    ~LineWidthDialog();

    void setLineWidth( int width ) { m_sboxWidth->setValue(width); }
    int lineWidth() { return m_sboxWidth->value(); }

private:
    QSpinBox *m_sboxWidth;
};

#endif // LINEWIDTHDIALOG_H
