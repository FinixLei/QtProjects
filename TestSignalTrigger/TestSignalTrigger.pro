TEMPLATE = subdirs

SUBDIRS += \
    TestQtService \
    PluginOne \
    PluginTwo \
    TestPluginOnePluginTwo

TestPluginOnePluginTwo.depends = \
    PluginOne \
    PluginTwo

TestQtService.depends = \
    PluginOne \
    PluginTwo
