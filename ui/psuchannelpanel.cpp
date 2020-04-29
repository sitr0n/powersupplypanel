#include "psuchannelpanel.h"
#include <QHBoxLayout>

PsuChannelPanel::PsuChannelPanel(const int &channel, std::shared_ptr<PSUInterface> psu, QWidget *parent)
    : QFrame(parent)
    , m_channel(channel)
    , m_psu(psu)
    , m_editButton(new QPushButton(QString::number(channel), this))
    , m_voltageDisplay(new QLCDNumber(7, this))
    , m_currentDisplay(new QLCDNumber(7, this))
    , m_voltageEdit(new QLineEdit(this))
    , m_currentEdit(new QLineEdit(this))
    , m_ticker(new QTimer(this))
    , m_isEditing(false)
{
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

    auto form = new QHBoxLayout(this);
    form->addWidget(createEditButton());
    form->addItem(createSpacer());
    form->addWidget(createVoltageDisplay());
    form->addWidget(createVoltageEdit());
    form->addWidget(createLabel("V"));
    form->addItem(createSpacer());
    form->addWidget(createCurrentDisplay());
    form->addWidget(createCurrentEdit());
    form->addWidget(createLabel("A"));

    setEditMode(m_isEditing);
    auto refreshDisplay = [&]{
        m_voltageDisplay->display(QString::number(m_psu->voltage(m_channel), 'f', 4));
        m_currentDisplay->display(QString::number(m_psu->current(m_channel), 'f', 4));
    };
    refreshDisplay();
    connect(m_ticker, &QTimer::timeout, refreshDisplay);
    m_ticker->start(SAMPLE_RATE);
}

void PsuChannelPanel::setEditMode(const bool enable)
{
    if (m_isEditing = enable) {
        m_voltageDisplay->setVisible(false);
        m_currentDisplay->setVisible(false);
        m_voltageEdit->setVisible(true);
        m_currentEdit->setVisible(true);
    } else {
        m_voltageEdit->setVisible(false);
        m_currentEdit->setVisible(false);
        m_voltageDisplay->setVisible(true);
        m_currentDisplay->setVisible(true);
    }
}

bool PsuChannelPanel::editMode() const
{
    return m_isEditing;
}

double PsuChannelPanel::getVoltage() const
{
    return m_voltageDisplay->value();
}

double PsuChannelPanel::getCurrent() const
{
    return m_currentDisplay->value();
}

QPushButton *PsuChannelPanel::createEditButton()
{
    auto font = m_editButton->font();
    font.setPointSize(FONT_SIZE);
    m_editButton->setFont(font);
    m_editButton->setMinimumSize(QSize(FIELD_HEIGHT, FIELD_HEIGHT));
    m_editButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    m_editButton->setFocusPolicy(Qt::NoFocus);

    connect(m_editButton, &QPushButton::clicked, [&]{
        setEditMode(!m_isEditing);
    });
    return m_editButton;
}

QSpacerItem *PsuChannelPanel::createSpacer()
{
    return new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Minimum);
}

QLCDNumber *PsuChannelPanel::createVoltageDisplay()
{
    m_voltageDisplay->setMinimumSize(QSize(FIELD_WIDTH, FIELD_HEIGHT));
    m_voltageDisplay->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    return m_voltageDisplay;
}

QLineEdit *PsuChannelPanel::createVoltageEdit()
{
    m_voltageEdit->setMinimumSize(QSize(FIELD_WIDTH, FIELD_HEIGHT));
    m_voltageEdit->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    connect(m_voltageEdit, &QLineEdit::returnPressed, [&]{
        m_voltageDisplay->display(m_voltageEdit->text());
        setEditMode(false);
    });
    return m_voltageEdit;
}

QLabel *PsuChannelPanel::createLabel(const QString &text)
{
    auto label = new QLabel(text, this);
    auto font = label->font();
    font.setPointSize(FONT_SIZE);
    font.setBold(true);
    label->setFont(font);
    label->setMinimumSize(QSize(FIELD_HEIGHT, FIELD_HEIGHT*2));
    label->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    return label;
}

QLCDNumber *PsuChannelPanel::createCurrentDisplay()
{
    m_currentDisplay->setMinimumSize(QSize(FIELD_WIDTH, FIELD_HEIGHT));
    m_currentDisplay->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    return m_currentDisplay;
}

QLineEdit *PsuChannelPanel::createCurrentEdit()
{
    m_currentEdit->setMinimumSize(QSize(FIELD_WIDTH, FIELD_HEIGHT));
    m_currentEdit->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    return m_currentEdit;
}
