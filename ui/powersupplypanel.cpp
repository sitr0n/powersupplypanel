#include "powersupplypanel.h"
#include <QVBoxLayout>

PowerSupplyPanel::PowerSupplyPanel(const QString &title, PSUInterface *psu, QWidget *parent)
    : QWidget(parent)
{
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);

    auto form = new QVBoxLayout(this);
    form->addWidget(createLabel(title));
    for (const auto& channel : psu->channels()) {
        auto display = std::make_shared<PsuChannelPanel>(channel, psu, this);
        m_channels.push_back(display);
        form->addWidget(display.get());
    }
}

std::vector<std::shared_ptr<PsuChannelPanel> > PowerSupplyPanel::channels() const
{
    return m_channels;
}

QLabel *PowerSupplyPanel::createLabel(const QString &text)
{
    auto label = new QLabel(text, this);
    auto font = label->font();
    font.setBold(true);
    font.setPointSize(TITLE_SIZE);
    label->setFont(font);
    return label;
}
