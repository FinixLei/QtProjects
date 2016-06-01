TEMPLATE = subdirs

SUBDIRS += \
    MyExe \
    TestMyExeWithQSystemSemaphore

TestMyExeWithQSystemSemaphore.depends = MyExe
