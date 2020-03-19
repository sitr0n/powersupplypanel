#pragma once
#include <QWidget>
#include "../drivers/psuinterface.h"
#include "psuchannelpanel.h"
#include <QLabel>
#include <vector>
#include <memory>

class PowerSupplyPanel : public QWidget
{
    Q_OBJECT
public:
    explicit PowerSupplyPanel(const QString &title, PSUInterface *psu, QWidget *parent = nullptr);
    std::vector<std::shared_ptr<PsuChannelPanel>> channels() const;

protected:
    QLabel *createLabel(const QString &text);

private:
    std::vector<std::shared_ptr<PsuChannelPanel>> m_channels;
    const int TITLE_SIZE = 26;
};
