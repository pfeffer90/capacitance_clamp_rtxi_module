/*
 * Copyright (C) 2011 Georgia Institute of Technology, University of Utah,
 * Weill Cornell Medical College
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * This is an implementation of a capacitance clamp.
 */

#include "capacitance_clamp_rtxi_module.h"
#include "capacitance_clamp_lib.h"
#include <iostream>
#include <main_window.h>


extern "C" Plugin::Object *
createRTXIPlugin(void) {
    return new CapacitanceClampRtxiModule();
}

static DefaultGUIModel::variable_t vars[] = {
        {
                "Vm",
                "Membrane potential in mV",
                DefaultGUIModel::INPUT | DefaultGUIModel::DOUBLE,
        },
        {
                "I_clamp",
                "Capacitance clamp current in nA",
                DefaultGUIModel::OUTPUT | DefaultGUIModel::DOUBLE,
        },
        {
                "C_cell (pF)",
                "Actual capacitance of the cell in pF",
                DefaultGUIModel::PARAMETER | DefaultGUIModel::DOUBLE,
        },
        {
                "C_target (pF)",
                "Target capacitance in pF",
                DefaultGUIModel::PARAMETER | DefaultGUIModel::DOUBLE,
        },
};

static size_t num_vars = sizeof(vars) / sizeof(DefaultGUIModel::variable_t);

CapacitanceClampRtxiModule::CapacitanceClampRtxiModule(void)
        : DefaultGUIModel("Capacitance clamp", ::vars, ::num_vars) {
    setWhatsThis("<p><b>CapacitanceClampRtxiModule:</b><br>QWhatsThis description.</p>");
    DefaultGUIModel::createGUI(vars,
                               num_vars); // this is required to create the GUI
    customizeGUI();
    initParameters();
    update(INIT); // this is optional, you may place initialization code directly
    // into the constructor
    refresh();    // this is required to update the GUI with parameter and state
    // values
    QTimer::singleShot(0, this, SLOT(resizeMe()));
}

CapacitanceClampRtxiModule::~CapacitanceClampRtxiModule(void) {
}

void
CapacitanceClampRtxiModule::execute(void) {
    output(0) = capacitanceClamp.get_clamping_current(input(0));
    return;
}

void
CapacitanceClampRtxiModule::initParameters(void) {
    double c_cell = DEFAULT_CAPACITANCE;
    double c_target = DEFAULT_CAPACITANCE;
    double period = get_period_from_RTXI_in_ms();
    capacitanceClamp.set_cell_capacitance(DEFAULT_CAPACITANCE);
    capacitanceClamp.set_target_capacitance(DEFAULT_CAPACITANCE);
    capacitanceClamp.set_period(period);
}

void
CapacitanceClampRtxiModule::update(DefaultGUIModel::update_flags_t flag) {
    switch (flag) {
        case INIT:
            setParameter("C_cell (pF)", capacitanceClamp.get_cell_capacitance());
            setParameter("C_target (pF)", capacitanceClamp.get_target_capacitance());
            break;

        case MODIFY:
            capacitanceClamp.set_cell_capacitance(getParameter("C_cell (pF)").toDouble());
            capacitanceClamp.set_target_capacitance(getParameter("C_target (pF)").toDouble());
            output(0) = 0;
            capacitanceClamp.reset_states();
            break;

        case UNPAUSE:

            break;

        case PAUSE:
            output(0) = 0;
            capacitanceClamp.reset_states();
            break;

        case PERIOD:
            capacitanceClamp.set_period(get_period_from_RTXI_in_ms());
            break;

        default:
            break;
    }
}

void
CapacitanceClampRtxiModule::customizeGUI(void) {
    //to add buttons or change the layout, have a look at the original plugin template code
}

double get_period_from_RTXI_in_ms() {
    return RT::System::getInstance()->getPeriod() * 1e-6; // ms
}
