#include <QApplication>
#include <drivers/tcpsocket.h>
#include <drivers/hmp4040_driver.h>
#include <ui/powersupplypanel.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    auto socket = std::make_shared<TcpSocket>();
    auto driver = std::make_shared<HMP4040Driver>(socket.get());
    auto panel = std::make_shared<PowerSupplyPanel>("HMP4040", driver.get());
    panel->show();
    return a.exec();
}
