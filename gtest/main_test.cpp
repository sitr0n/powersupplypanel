#include <gtest/gtest.h>
#include <QApplication>
#include <drivers/gtest/hmp4040driver_test.cpp>
#include <ui/gtest/psuchannelpanel_test.cpp>
#include <ui/gtest/powersupplypanel_test.cpp>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
