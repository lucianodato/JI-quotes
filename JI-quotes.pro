TEMPLATE = subdirs
CONFIG += ordered
SUBDIRS = \
   app \
   tests

tests.depends = app
