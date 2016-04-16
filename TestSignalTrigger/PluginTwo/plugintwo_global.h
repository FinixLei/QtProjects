#ifndef PLUGINTWO_GLOBAL_H
#define PLUGINTWO_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(PLUGINTWO_LIBRARY)
#  define PLUGINTWOSHARED_EXPORT Q_DECL_EXPORT
#else
#  define PLUGINTWOSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // PLUGINTWO_GLOBAL_H
