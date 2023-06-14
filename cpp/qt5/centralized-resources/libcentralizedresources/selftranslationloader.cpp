#include <QCoreApplication>

#include "libtranslator.h"


// using namespace CentRes;

static void loadSelfTranslation()
{
    CentRes::Translator::translateLibrary(QLatin1String(LIBCENTRALIZEDRESOURCES_DIR_NAME));
}

Q_COREAPP_STARTUP_FUNCTION(loadSelfTranslation)
