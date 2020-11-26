#ifndef TESTSETUP_H
#define TESTSETUP_H

#include <QtTest>
#include <QtTestGui>

class TestSetup : public QObject
{
    Q_OBJECT

private slots:
    void case1_memload_loadfromfile();
    void case2_memload_loadfrommemory();

public:
    explicit TestSetup(QObject *parent = nullptr);

    virtual ~TestSetup();
};

#endif // TESTSETUP_H
