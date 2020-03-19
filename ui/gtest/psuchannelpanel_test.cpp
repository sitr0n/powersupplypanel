#include <gtest/gtest.h>
#include <psuchannelpanel.h>
#include <../drivers/gtest/mockpsuinterface.h>

const int CHANNEL = 1;
using ::testing::_;
using ::testing::Return;
using ::testing::AtLeast;

TEST(PsuChannelPanel, testDisplay){
    auto driver = std::make_shared<MockPSUInterface>();
    const float volt = 24.0;
    const float amp = 2.5;
    EXPECT_CALL(*driver, voltage(CHANNEL)).Times(AtLeast(1)).WillRepeatedly(Return(volt));
    EXPECT_CALL(*driver, current(CHANNEL)).Times(AtLeast(1)).WillRepeatedly(Return(amp));
    auto panel = std::make_shared<PsuChannelPanel>(CHANNEL, driver.get());

    ASSERT_EQ(panel->getVoltage(), volt);
    ASSERT_EQ(panel->getCurrent(), amp);

}

TEST(PsuChannelPanel, testEditMode){
    auto driver = std::make_shared<MockPSUInterface>();
    const float volt = 24.0;
    const float amp = 2.5;
    EXPECT_CALL(*driver, voltage(CHANNEL)).Times(AtLeast(1)).WillRepeatedly(Return(volt));
    EXPECT_CALL(*driver, current(CHANNEL)).Times(AtLeast(1)).WillRepeatedly(Return(amp));
    auto panel = std::make_shared<PsuChannelPanel>(CHANNEL, driver.get());

    for (const auto& enable : {true, false}) {
        panel->setEditMode(enable);
        ASSERT_EQ(panel->editMode(), enable);
    }

}
