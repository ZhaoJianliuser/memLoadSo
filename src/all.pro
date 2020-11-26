TEMPLATE  = subdirs
CONFIG   += ordered

SUBDIRS += \
    csdll \
    mldll \
    mldll_qtest

mldll_qtest.depends = mldll csdll

