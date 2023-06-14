
#include <cstdlib>
#include <iostream>

#include <QApplication>

#include "listener.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    std::cout << qPrintable(QString::fromLatin1("Dbus Service")) << "\n";

    Listener listener{};

    if (!listener.ready())
    {
        return EXIT_FAILURE;
    }

    return a.exec();
}
