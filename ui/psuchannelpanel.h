#pragma once
#include <QWidget>
#include <QFrame>
#include "../drivers/psuinterface.h"
#include <memory>
#include <QPushButton>
#include <QSpacerItem>
#include <QLCDNumber>
#include <QLineEdit>
#include <QLabel>
#include <QTimer>

class PsuChannelPanel : public QFrame
{
    Q_OBJECT
public:
    explicit PsuChannelPanel(const int &channel, std::shared_ptr<PSUInterface> psu, QWidget *parent = nullptr);
    void setEditMode(const bool enable);
    bool editMode() const;
    double getVoltage() const;
    double getCurrent() const;

protected:
    QPushButton *createEditButton();
    QSpacerItem *createSpacer();
    QLCDNumber *createVoltageDisplay();
    QLineEdit *createVoltageEdit();
    QLabel *createLabel(const QString &text);
    QLCDNumber *createCurrentDisplay();
    QLineEdit *createCurrentEdit();

private:
    int m_channel;
    std::shared_ptr<PSUInterface> m_psu;
    QPushButton *m_editButton;
    QLCDNumber *m_voltageDisplay;
    QLCDNumber *m_currentDisplay;
    QLineEdit *m_voltageEdit;
    QLineEdit *m_currentEdit;

    QTimer *m_ticker;
    bool m_isEditing;

    const int FIELD_HEIGHT = 16;
    const int FIELD_WIDTH = 135;
    const int FONT_SIZE = 12;
    const int SAMPLE_RATE = 500;
};
