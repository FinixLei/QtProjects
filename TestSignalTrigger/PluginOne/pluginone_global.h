#ifndef PLUGINONE_GLOBAL_H
#define PLUGINONE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(PLUGINONE_LIBRARY)
#  define PLUGINONESHARED_EXPORT Q_DECL_EXPORT
#else
#  define PLUGINONESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // PLUGINONE_GLOBAL_H
