#ifndef VCKIOSKPINDIALOG_H
#define VCKIOSKPINDIALOG_H

#include <QDialog>

class QLineEdit;
class QPushButton;

class VCKioskPinDialog : public QDialog
{
    Q_OBJECT

public:
    VCKioskPinDialog(QWidget* parent = nullptr, bool verifyMode = false);
    ~VCKioskPinDialog();

    QString pin() const;
    bool verifyPin(const QString& correctPin);

private slots:
    void slotTextChanged(const QString& text);

private:
    void setupUi();
    void updateOkButton();

    QLineEdit* m_pinEdit;
    QPushButton* m_okButton;
    bool m_verifyMode;
};

#endif // VCKIOSKPINDIALOG_H
