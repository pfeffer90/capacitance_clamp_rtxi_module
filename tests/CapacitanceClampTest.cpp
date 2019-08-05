//
// Created by pfeiffer on 8/5/19.
//

#include "gtest/gtest.h"
#include "capacitance_clamp_lib.h"


TEST(CapacitanceClampTest, ReturnsExpectedParameter) {
    EXPECT_EQ(initialize_my_awesome_parameter(), 1);
}