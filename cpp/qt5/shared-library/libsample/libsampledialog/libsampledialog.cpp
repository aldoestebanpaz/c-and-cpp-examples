#include "libsampledialog.h"
#include "ui_libsampledialog.h"
#include "libsampletranslator.h"

#include <QPushButton>
#include <QStringList>


using namespace Sample;

LibSampleDialog::LibSampleDialog(const QString& title, QWidget* parent) :
    QDialog(parent),
    ui(new Ui::LibSampleDialog)
{
    ui->setupUi(this);
    setWindowTitle(title);

    ui->plainTextEdit->appendPlainText(tr("Translation search paths:"));
    for (const QString &d : Translator::translationSearchPaths()) {
        ui->plainTextEdit->appendPlainText(QString::fromLatin1("  ") + d);
    }

    connect(ui->sendSignalButton, &QAbstractButton::clicked, this, &LibSampleDialog::onSendSignalButtonClicked);
}

LibSampleDialog::~LibSampleDialog()
{
    delete ui;
}

void LibSampleDialog::onSendSignalButtonClicked() {
    Q_EMIT clicked();
}
