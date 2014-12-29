#include "MainDialog.h"
#include "ui_MainDialog.h"

#include <QCryptographicHash>
#include <QClipboard>

MainDialog::MainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainDialog)
{
    ui->setupUi(this);
}

MainDialog::~MainDialog()
{
    delete ui;
}

void MainDialog::on_buttonBox_accepted()
{
    // Get the master password (salt)
    QString masterPassword = ui->masterPasswordEdit->text();

    // Get the service
    QString service = ui->serviceEdit->text();

    // Combine the two
    QString combined = masterPassword + "+" + service;

    // Generate hash
    QString hashed = QCryptographicHash::hash(combined.toUtf8(), QCryptographicHash::Sha1).toHex();

    // Truncate to 16 characters
    hashed.truncate(16);

    // Save to clipboard
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(hashed);

    // Make sure it is persisted after application exit
    QEvent event(QEvent::Clipboard);
    QApplication::sendEvent(clipboard, &event);
}
