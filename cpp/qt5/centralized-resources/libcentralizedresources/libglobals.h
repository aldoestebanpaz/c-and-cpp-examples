
#ifndef _LIBCENTRES_GLOBALS_H_
#define _LIBCENTRES_GLOBALS_H_

#include <QtGlobal>

#ifdef COMPILE_LIB
#define LIBCENTRES_API Q_DECL_EXPORT
#else
#define LIBCENTRES_API Q_DECL_IMPORT
#endif

#ifndef QL1S
#define QL1S(x) QLatin1String(x)
#endif

#ifndef QL1C
#define QL1C(x) QLatin1Char(x)
#endif

#ifndef QSL
#define QSL(x) QStringLiteral(x)
#endif

#ifndef QBAL
#define QBAL(x) QByteArrayLiteral(x)
#endif

#endif // _LIBCENTRES_GLOBALS_H_
