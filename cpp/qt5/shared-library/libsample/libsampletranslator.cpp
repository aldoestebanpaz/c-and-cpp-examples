
#include "libsampletranslator.h"
#include <QTranslator>
#include <QLocale>
#include <QDebug>
#include <QCoreApplication>
#include <QLibraryInfo>
#include <QStringList>
#include <QStringBuilder>
#include <QFileInfo>


using namespace Sample;


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


bool translate(const QString &name, const QString &owner = QString());

/************************************************

 ************************************************/
QStringList *getSearchPaths()
{
    static QStringList *searchPath = nullptr;

    if (searchPath == nullptr)
    {
        searchPath = new QStringList();
        *searchPath << dataDirs(QL1C('/') + QL1S(LIBSAMPLE_RELATIVE_TRANSLATIONS_DIR));
        *searchPath << QL1S(LIBSAMPLE_TRANSLATIONS_DIR);
        searchPath->removeDuplicates();
    }

    return searchPath;
}


/************************************************

 ************************************************/
QStringList Translator::translationSearchPaths()
{
    return *(getSearchPaths());
}


/************************************************

 ************************************************/
void Translator::setTranslationSearchPaths(const QStringList &paths)
{
    QStringList *p = getSearchPaths();
    p->clear();
    *p << paths;
}


/************************************************

 ************************************************/
bool translate(const QString &name, const QString &owner)
{
    const QString locale = QLocale::system().name();
    QTranslator *appTranslator = new QTranslator(qApp);

    QStringList *paths = getSearchPaths();
    for(const QString &path : qAsConst(*paths))
    {
        QStringList subPaths;

        if (!owner.isEmpty())
        {
            subPaths << path + QL1C('/') + owner + QL1C('/') + name;
        }
        else
        {
            subPaths << path + QL1C('/') + name;
            subPaths << path;
        }

        for(const QString &p : qAsConst(subPaths))
        {
            if (appTranslator->load(name + QL1C('_') + locale, p))
            {
                QCoreApplication::installTranslator(appTranslator);
                return true;
            }
            else if (appTranslator->load(name + QL1C('_') + locale.left(2), p))
            {
                QCoreApplication::installTranslator(appTranslator);
                return true;
            }
            else if (locale == QLatin1String("C") ||
                        locale.startsWith(QLatin1String("en")))
            {
                // English is the default. Even if there isn't an translation
                // file, we return true. It's translated anyway.
                delete appTranslator;
                return true;
            }
        }
    }

    // If we got here, no translation was loaded. appTranslator has no use.
    delete appTranslator;
    return false;
}


/************************************************

 ************************************************/
bool Translator::translateApplication(const QString &applicationName)
{
    const QString locale = QLocale::system().name();
    QTranslator *qtTranslator = new QTranslator(qApp);

    if (qtTranslator->load(QL1S("qt_") + locale, QLibraryInfo::location(QLibraryInfo::TranslationsPath)))
    {
        qApp->installTranslator(qtTranslator);
    }
    else
    {
        delete qtTranslator;
    }

    if (!applicationName.isEmpty())
        return translate(applicationName);
    else
        return translate(QFileInfo(QCoreApplication::applicationFilePath()).baseName());
}


/************************************************

 ************************************************/
bool Translator::translateLibrary(const QString &libraryName)
{
    static QSet<QString> loadedLibs;

    if (loadedLibs.contains(libraryName))
        return true;

    loadedLibs.insert(libraryName);

    return translate(libraryName);
}
