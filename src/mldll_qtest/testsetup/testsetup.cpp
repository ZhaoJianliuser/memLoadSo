#include "testsetup.h"

#include "testmemload.h"

#include <QDateTime>
#include <QDebug>

void TestSetup::case1_memload_loadfromfile()
{
    QCOMPARE(LoadFromFile(), 0);
}

void TestSetup::case2_memload_loadfrommemory()
{
    QCOMPARE(LoadFromMemory(), 0);
}

TestSetup::TestSetup(QObject *parent) :
    QObject(parent)
{

}

TestSetup::~TestSetup()
{

}
