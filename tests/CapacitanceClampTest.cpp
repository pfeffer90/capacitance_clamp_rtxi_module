//
// Created by pfeiffer on 8/5/19.
//

#include "gtest/gtest.h"
#include "capacitance_clamp_lib.h"

class CapacitanceClampTest : public :: testing :: Test {
protected:
    void SetUp() {

    }
    double cell_capacitance = 100;
    double target_capacitance = 100;
    double period = 0.05;
};

TEST_F(CapacitanceClampTest, RequiresAtLeastCellAndTargetCapacitancePlusDynamicClampPeriod) {
    CapacitanceClamp(cell_capacitance, target_capacitance, period);
}
TEST_F(CapacitanceClampTest, AllowsSettingAndGettingCapacitancesAndPeriods) {
    CapacitanceClamp capacitance_clamp = CapacitanceClamp(cell_capacitance, target_capacitance, period);
    double test_capacitance = 150;
    double test_period = 0.02;
    capacitance_clamp.set_cell_capacitance(test_capacitance);
    capacitance_clamp.set_target_capacitance(test_capacitance);
    capacitance_clamp.set_period(test_period);
    EXPECT_EQ(capacitance_clamp.get_cell_capacitance(), test_capacitance);
    EXPECT_EQ(capacitance_clamp.get_target_capacitance(), test_capacitance);
    EXPECT_EQ(capacitance_clamp.get_period(), test_period);
}

TEST_F(CapacitanceClampTest, ProvidesNoCurrentUntilTwoVoltageMeasurementsHaveBeenGiven) {
    CapacitanceClamp capacitance_clamp = CapacitanceClamp(cell_capacitance, target_capacitance, period);
    capacitance_clamp.set_target_capacitance(cell_capacitance+20);
    double v1 = -70;
    double v2 = -69.5;

    EXPECT_EQ(capacitance_clamp.get_clamping_current(v1), 0);
    EXPECT_NE(capacitance_clamp.get_clamping_current(v2), 0);
}

TEST_F(CapacitanceClampTest, ProvidesNoCurrentIfCellAndTargetCapacitanceCoincide) {

    CapacitanceClamp capacitance_clamp = CapacitanceClamp(cell_capacitance, target_capacitance, period);

    double v1 = -70;
    double v2 = -69.5;
    double v3 = -69.3;

    ASSERT_EQ(capacitance_clamp.get_cell_capacitance(), capacitance_clamp.get_target_capacitance());

    double i1 = capacitance_clamp.get_clamping_current(v1);
    double i2 = capacitance_clamp.get_clamping_current(v2);
    double i3 = capacitance_clamp.get_clamping_current(v3);

    EXPECT_EQ(i1, 0);
    EXPECT_EQ(i2, 0);
    EXPECT_EQ(i3, 0);
}

TEST_F(CapacitanceClampTest, ProvidesCorrectCurrentIfCellAndTargetCapacitanceCoincide) {

    CapacitanceClamp capacitance_clamp = CapacitanceClamp(cell_capacitance, target_capacitance, period);
    double test_target_capacitance = 150;
    capacitance_clamp.set_target_capacitance(test_target_capacitance);

    double v1 = -70;
    double v2 = -69.5;
    double v3 = -69.3;

    ASSERT_NE(capacitance_clamp.get_cell_capacitance(), capacitance_clamp.get_target_capacitance());

    double i1 = capacitance_clamp.get_clamping_current(v1);
    double i2 = capacitance_clamp.get_clamping_current(v2);
    double i3 = capacitance_clamp.get_clamping_current(v3);

    EXPECT_EQ(i1, 0);
    EXPECT_EQ(i2, (cell_capacitance-test_target_capacitance)/test_target_capacitance*(1e-3*cell_capacitance*(v2-v1)
    /period));
    EXPECT_EQ(i3, (cell_capacitance-test_target_capacitance)/test_target_capacitance*(1e-3*cell_capacitance*(v3-v2)
    /period-i2));
}
