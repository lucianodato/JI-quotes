TEMPLATE = subdirs
CONFIG += ordered
SUBDIRS = \
   app \
   tests

tests.depends = app

OTHER_FILES += \
    defaults.pri
