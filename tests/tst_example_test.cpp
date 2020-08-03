#include <QtTest>

// add necessary includes here

class example_test : public QObject
{
    Q_OBJECT

public:
    example_test();
    ~example_test();

private slots:
    void test_case1();

};

example_test::example_test()
{

}

example_test::~example_test()
{

}

void example_test::test_case1()
{

}

QTEST_APPLESS_MAIN(example_test)

#include "tst_example_test.moc"
