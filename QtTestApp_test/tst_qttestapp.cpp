#include <QString>
#include <QtTest>

class QtTestAppTest : public QObject
{
    Q_OBJECT

public:
    QtTestAppTest();

private Q_SLOTS:
    void testCase1();
};

QtTestAppTest::QtTestAppTest()
{
}

void QtTestAppTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(QtTestAppTest)

#include "tst_qttestapp.moc"
