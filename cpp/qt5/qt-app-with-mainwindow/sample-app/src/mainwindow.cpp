#include <QDebug>
#include <QDir>
#include <QIcon>
#include <QLibraryInfo>
#include <QLocale>

#include "mainwindow.h"
#include "ui_mainwindow.h"


QStringList configDirs(const QString &postfix = QString());
QString configHome(bool createDir = true);
QString createDirectory(const QString &dir);
QStringList dataDirs(const QString &postfix = QString());
void fixBashShortcuts(QString &s);
void removeEndingSlash(QString &s);

void cleanAndAddPostfix(QStringList &dirs, const QString& postfix)
{
    const int N = dirs.count();
    for(int i = 0; i < N; ++i)
    {
        fixBashShortcuts(dirs[i]);
        removeEndingSlash(dirs[i]);
        dirs[i].append(postfix);
    }
}

QStringList configDirs(const QString &postfix)
{
    QStringList dirs;
    const QString env = QString::fromLocal8Bit(qgetenv("XDG_CONFIG_DIRS"));
    if (env.isEmpty())
        dirs.append(QString::fromLatin1("/etc/xdg"));
    else
        dirs = env.split(QLatin1Char(':'), Qt::SkipEmptyParts);

    cleanAndAddPostfix(dirs, postfix);
    return dirs;
}

QString configHome(bool createDir)
{
    QString configDir = QString::fromLocal8Bit(qgetenv("XDG_CONFIG_HOME"));
    if(configDir.isEmpty())
        configDir = QString::fromLocal8Bit(qgetenv("HOME")) + QStringLiteral("/.config");
    fixBashShortcuts(configDir);
    if (createDir)
        return createDirectory(configDir);

   removeEndingSlash(configDir);
   return configDir;
}

QString createDirectory(const QString &dir)
{
    QDir d(dir);
    if (!d.exists())
    {
        if (!d.mkpath(QLatin1String(".")))
        {
            qWarning() << QString::fromLatin1("Can't create %1 directory.").arg(d.absolutePath());
        }
    }
    QString r = d.absolutePath();
    removeEndingSlash(r);
    return r;
}

QStringList dataDirs(const QString &postfix)
{
    QString env = QString::fromLocal8Bit(qgetenv("XDG_DATA_DIRS"));
    QStringList dirs = env.split(QLatin1Char(':'), Qt::SkipEmptyParts);

    if (dirs.isEmpty()) {
        dirs.append(QString::fromLatin1("/usr/local/share"));
        dirs.append(QString::fromLatin1("/usr/share"));
    } else {
        QMutableListIterator<QString> it(dirs);
        while (it.hasNext()) {
            const QString dir = it.next();
            if (!dir.startsWith(QLatin1Char('/')))
                it.remove();
        }
    }

    dirs.removeDuplicates();
    cleanAndAddPostfix(dirs, postfix);
    return dirs;

}

void fixBashShortcuts(QString &s)
{
    if (s.startsWith(QLatin1Char('~')))
        s = QString::fromLocal8Bit(qgetenv("HOME")) + (s).mid(1);
}

void removeEndingSlash(QString &s)
{
    // We don't check for empty strings. Caller must check it.

    // Remove the ending slash, except for root dirs.
    if (s.length() > 1 && s.endsWith(QLatin1Char('/')))
        s.chop(1);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    // save config into: ~/.config/qt-samples/sample-app.conf
    mSettings(new QSettings(QStringLiteral("qt-samples"), QStringLiteral("sample-app"), this))
{
    ui->setupUi(this);

    setWindowTitle(QStringLiteral("Sample App"));

    connect(ui->actionQuit, &QAction::triggered, [&] {
        close();
    });

    resize(mSettings->value(QStringLiteral("MainWindow/width"), 400).toInt(),
        mSettings->value(QStringLiteral("dialog/height"), 400).toInt());

    ui->plainTextEdit->appendPlainText(tr("Hello World."));
    ui->plainTextEdit->appendPlainText(tr("Application name") + ": " + QCoreApplication::applicationName());
    ui->plainTextEdit->appendPlainText(tr("Application version") + ": " + QCoreApplication::applicationVersion());
    ui->plainTextEdit->appendPlainText(tr("System locale") + ": " + QLocale::system().name());
    ui->plainTextEdit->appendPlainText(tr("Translation information for Qt strings") + ": " + QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    ui->plainTextEdit->appendPlainText(tr("Icon theme search paths") + ": " + QIcon::themeSearchPaths().join(","));
    ui->plainTextEdit->appendPlainText(tr("Current icon theme") + ": " + QIcon::themeName());

    ui->plainTextEdit->appendPlainText(tr("Settings file location") + ": " + mSettings->fileName());
    ui->plainTextEdit->appendPlainText("$XDG_CONFIG_HOME: " + configHome());
    ui->plainTextEdit->appendPlainText("$XDG_CONFIG_DIRS:");
    for (const QString &d : configDirs()) {
        ui->plainTextEdit->appendPlainText("  " + d);
    }

    ui->plainTextEdit->appendPlainText("$XDG_DATA_DIRS: ");
    for (const QString &d : dataDirs()) {
        ui->plainTextEdit->appendPlainText("  " + d);
    }

    ui->plainTextEdit->appendPlainText(tr("Desktop entries are located in") + ":");
    for (const QString &d : dataDirs(QLatin1String("/applications"))) {
        ui->plainTextEdit->appendPlainText("  " + d);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent * /*event*/)
{
    mSettings->setValue(QStringLiteral("MainWindow/width"), size().width());
    mSettings->setValue(QStringLiteral("MainWindow/height"), size().height());
}
