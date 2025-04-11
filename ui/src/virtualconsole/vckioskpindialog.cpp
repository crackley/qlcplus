#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include "vckioskpindialog.h"

VCKioskPinDialog::VCKioskPinDialog(QWidget* parent, bool verifyMode)
    : QDialog(parent)
    , m_verifyMode(verifyMode)
{
    setupUi();
}

VCKioskPinDialog::~VCKioskPinDialog()
{
}

void VCKioskPinDialog::setupUi()
{
    setWindowTitle(m_verifyMode ? tr("Verify Kiosk PIN") : tr("Set Kiosk PIN"));

    QVBoxLayout* layout = new QVBoxLayout(this);

    QLabel* label = new QLabel(m_verifyMode ? 
        tr("Enter PIN to disable kiosk mode:") : 
        tr("Enter a 4-digit PIN for kiosk mode:"), this);
    layout->addWidget(label);

    m_pinEdit = new QLineEdit(this);
    m_pinEdit->setEchoMode(QLineEdit::Password);
    m_pinEdit->setMaxLength(4);
    m_pinEdit->setPlaceholderText("****");
    connect(m_pinEdit, SIGNAL(textChanged(QString)), this, SLOT(slotTextChanged(QString)));
    layout->addWidget(m_pinEdit);

    QHBoxLayout* btnLayout = new QHBoxLayout();
    
    m_okButton = new QPushButton(tr("OK"), this);
    m_okButton->setEnabled(false);
    connect(m_okButton, SIGNAL(clicked()), this, SLOT(accept()));
    
    QPushButton* cancelButton = new QPushButton(tr("Cancel"), this);
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));

    btnLayout->addWidget(m_okButton);
    btnLayout->addWidget(cancelButton);
    layout->addLayout(btnLayout);

    m_pinEdit->setFocus();
}

void VCKioskPinDialog::updateOkButton()
{
    // Only allow numeric PINs of exactly 4 digits
    QString pin = m_pinEdit->text();
    bool valid = pin.length() == 4 && pin.toInt() > 0;
    m_okButton->setEnabled(valid);
}

void VCKioskPinDialog::slotTextChanged(const QString& text)
{
    // Only allow numeric input
    QString filtered;
    for (QChar c : text)
    {
        if (c.isDigit())
            filtered.append(c);
    }
    if (filtered != text)
    {
        m_pinEdit->setText(filtered);
        return;
    }
    updateOkButton();
}

QString VCKioskPinDialog::pin() const
{
    return m_pinEdit->text();
}

bool VCKioskPinDialog::verifyPin(const QString& correctPin)
{
    if (m_pinEdit->text() == correctPin)
        return true;

    QMessageBox::warning(this, tr("Invalid PIN"),
                        tr("The PIN you entered is incorrect."));
    m_pinEdit->clear();
    m_pinEdit->setFocus();
    return false;
}
