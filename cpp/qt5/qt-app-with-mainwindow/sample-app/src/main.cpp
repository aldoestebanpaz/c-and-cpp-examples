#include <QApplication>
#include <QCommandLineParser>
#include <QDir>

#include "mainwindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCommandLineParser parser;
    parser.setApplicationDescription(QStringLiteral("Sample App"));
    const QString VERINFO = QStringLiteral(APP_VERSION
                                           "\nQt        " QT_VERSION_STR);
    a.setApplicationVersion(VERINFO);
    parser.addVersionOption();
    parser.addHelpOption();
    parser.process(a);

    // default icon
    // a.setWindowIcon(QIcon(QFile::decodeName(APP_GRAPHICS_DIR) + QLatin1String("/logo.png")));
    QIcon appIcon{QIcon::fromTheme(QStringLiteral("sample-app"))};
    if (appIcon.isNull())
        appIcon = QIcon(QStringLiteral(":/res/img/logo.png"));
    a.setWindowIcon(appIcon);

    MainWindow mainWindow;
    mainWindow.show();

    return a.exec();
}
