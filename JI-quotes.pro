TEMPLATE = subdirs
CONFIG += ordered c++11
SUBDIRS = \
   app \
   tests

tests.depends = app
