
#include <QApplication>
#include <QMessageBox>

#include <Sample/Dialog>


using namespace Sample;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LibSampleDialog* libSampleDialog = new LibSampleDialog(QObject::tr("Title from Client App"));
    QObject::connect(libSampleDialog, &LibSampleDialog::clicked, [=] () {
        QMessageBox::information(nullptr, QObject::tr("Message"), QObject::tr("Example message"));
    });
    libSampleDialog->show();

    return a.exec();

}
