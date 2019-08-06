//
// Created by pfeiffer on 8/5/19.
//

#ifndef CAPACITANCE_CLAMP_CAPACITANCE_CLAMP_LIB_H
#define CAPACITANCE_CLAMP_CAPACITANCE_CLAMP_LIB_H

class CapacitanceClamp
{
public:
    CapacitanceClamp (double, double, double);
    void set_cell_capacitance(double);
    double get_cell_capacitance();

    void set_target_capacitance(double);
    double get_target_capacitance();

    void set_period(double period);
    double get_period();

    double get_clamping_current(double voltage);

private:
    double c_cell; //pF
    double c_target; //pF
    double dynamic_clamp_period; //ms

    int number_of_voltage_measurements{};

    double v_previous{};
    double v_curr{};

    double i_previous{};

    void update_voltage(double voltage);

    double estimate_current();

    void reset_states();

    void update_current_state(double current);
};
#endif //CAPACITANCE_CLAMP_CAPACITANCE_CLAMP_LIB_H
