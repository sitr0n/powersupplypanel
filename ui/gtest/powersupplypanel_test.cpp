#include <gtest/gtest.h>
#include <powersupplypanel.h>
#include <../drivers/gtest/mockpsuinterface.h>

using ::testing::AtLeast;
using ::testing::Return;

TEST(PowerSupplyPanel, testConstruction){
    auto driver = std::make_shared<MockPSUInterface>();
    const float volt = 24.0;
    const float amp = 2.5;
    std::vector<int> channels = {1, 2, 3, 4};
    EXPECT_CALL(*driver, channels())
            .Times(1)
            .WillOnce(Return(channels));
    for (const auto &channel : channels) {
        EXPECT_CALL(*driver, voltage(channel)).Times(AtLeast(1)).WillRepeatedly(Return(volt));
        EXPECT_CALL(*driver, current(channel)).Times(AtLeast(1)).WillRepeatedly(Return(amp));
    }
    auto panel = std::make_shared<PowerSupplyPanel>("Psu test", driver);
    ASSERT_EQ(panel->channels().size(), channels.size());
}
