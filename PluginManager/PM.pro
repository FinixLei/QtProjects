TEMPLATE = subdirs

SUBDIRS += \
    MyPluginOne \
    PluginManager

PluginManager.depends = \
    MyPluginOne
