#include <QCoreApplication>

#include "libsampletranslator.h"


// using namespace Sample;

static void loadSelfTranslation()
{
    Sample::Translator::translateLibrary(QLatin1String(LIBSAMPLE_DIR_NAME));
}

Q_COREAPP_STARTUP_FUNCTION(loadSelfTranslation)
