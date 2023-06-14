
#ifndef _LIBSAMPLE_GLOBALS_H_
#define _LIBSAMPLE_GLOBALS_H_

#include <QtGlobal>

#ifdef COMPILE_LIB
#define LIBSAMPLE_API Q_DECL_EXPORT
#else
#define LIBSAMPLE_API Q_DECL_IMPORT
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

#endif // _LIBSAMPLE_GLOBALS_H_
