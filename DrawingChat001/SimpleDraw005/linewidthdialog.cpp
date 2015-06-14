#include "linewidthdialog.h"

#include <QDialogButtonBox>
#include <QSpinBox>
#include <QVBoxLayout>

LineWidthDialog::LineWidthDialog(QWidget *parent)
    :QDialog(parent)
{
    setWindowTitle(tr("Select line width"));

    m_sboxWidth = new QSpinBox();
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    QVBoxLayout  *layout = new QVBoxLayout;
    layout->addWidget(m_sboxWidth);
    layout->addWidget(buttonBox);
    setLayout(layout);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

LineWidthDialog::~LineWidthDialog()
{
}
