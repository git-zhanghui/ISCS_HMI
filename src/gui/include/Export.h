#ifndef EXPORT_H
#define EXPORT_H

#include <QtCore/qglobal.h>

#if defined(EXPORT_LIBRARY)
#  define EXPORT Q_DECL_EXPORT
#else
#  define EXPORT Q_DECL_IMPORT
#endif

#endif // EXPORT_H
