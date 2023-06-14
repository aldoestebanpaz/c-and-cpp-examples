
#include <QApplication>
#include <QMessageBox>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QMessageBox box;
    // box.setIcon(QMessageBox::Warning);
    box.setIconPixmap(QPixmap(QLatin1String(CENTRALIZED_GRAPHICS_DIR"/meme.svg")));
    box.setWindowTitle(QObject::tr("Sample app 01"));
    box.setText(QObject::tr("Hello World!"));
    box.show();

    return a.exec();
}
