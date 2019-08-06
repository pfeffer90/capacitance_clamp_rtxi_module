//
// Created by pfeiffer on 8/5/19.
//

#include "capacitance_clamp_lib.h"

#define DEFAULT_CAPACITANCE 100 //pF

CapacitanceClamp::CapacitanceClamp(double cell_capacitance, double target_capacitance, double period) {
    c_cell = cell_capacitance;
    c_target = target_capacitance;
    dynamic_clamp_period = period;

    reset_states();
}

void CapacitanceClamp::set_cell_capacitance(double cell_capacitance) {
    c_cell = cell_capacitance;
}

void CapacitanceClamp::set_target_capacitance(double target_capacitance) {
    c_target = target_capacitance;
}

double CapacitanceClamp::get_cell_capacitance() {
    return c_cell;
}

double CapacitanceClamp::get_target_capacitance() {
    return c_target;
}

void CapacitanceClamp::set_period(double period) {
    dynamic_clamp_period = period;

}

double CapacitanceClamp::get_period() {
    return dynamic_clamp_period;
}

double CapacitanceClamp::get_clamping_current(double voltage){
    update_voltage(voltage);

    double estimated_flowing_current = estimate_current();
    double clamping_current = (c_cell-c_target)/c_target *estimated_flowing_current;
    if (number_of_voltage_measurements < 2) {
        clamping_current = 0;
    }
    update_current_state(clamping_current);
    return clamping_current;
}

void CapacitanceClamp::update_voltage(double voltage) {
    v_previous = v_curr;
    v_curr = voltage;
    number_of_voltage_measurements += 1;
}

double CapacitanceClamp::estimate_current() {
    return 1e-3*c_cell*(v_curr-v_previous)/dynamic_clamp_period - i_previous;
}

void CapacitanceClamp::reset_states() {
    v_curr = 0;
    v_previous = 0;
    i_previous = 0;
    number_of_voltage_measurements = 0;
}

void CapacitanceClamp::update_current_state(double current) {
    i_previous = current;
}
