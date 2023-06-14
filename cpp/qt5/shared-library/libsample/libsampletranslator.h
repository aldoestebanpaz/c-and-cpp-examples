
#ifndef SAMPLELIBTRANSLATOR_H
#define SAMPLELIBTRANSLATOR_H

#include <QStringList>
#include "libsampleglobals.h"

namespace Sample
{
/**
  The Translator class provides internationalization support for application and libraries.
 **/
class LIBSAMPLE_API Translator
{
public:
    /**
      Returns a list of paths that the application will search translations files.
     **/
    static QStringList translationSearchPaths();

    /**
      Sets the list of directories to search translations. All existing paths
      will be deleted and the path list will consist of the paths given in paths.
     **/
    static void setTranslationSearchPaths(const QStringList &paths);

    /**
      Loads translations for application. If applicationName is not specified,
      then basename of QCoreApplication::applicationFilePath() is used.
      Returns true if the translation is successfully loaded; otherwise returns false.
    **/
    static bool translateApplication(const QString &applicationName = QString());

    /**
      Loads translations for application. If applicationName is not specified,
      then basename of QCoreApplication::applicationFilePath() is used.
      Returns true if the translation is successfully loaded; otherwise returns false.
    **/
    static bool translateLibrary(const QString &libraryName = QString());
};

} // namespace Sample
#endif // SAMPLELIBTRANSLATOR_H
