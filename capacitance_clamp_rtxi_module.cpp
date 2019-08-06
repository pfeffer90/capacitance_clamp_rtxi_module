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

#define DEFAULT_CAPACITANCE 100

extern "C" Plugin::Object*
createRTXIPlugin(void)
{
  return new CapacitanceClampRtxiModule();
}

static DefaultGUIModel::variable_t vars[] = {
  {
    "C_cell (pF)", "Actual capacitance of the cell in pF",
    DefaultGUIModel::PARAMETER | DefaultGUIModel::DOUBLE,
  },
  {
    "C_target (pF)", "Target capacitance in pF", DefaultGUIModel::PARAMETER | DefaultGUIModel::DOUBLE,
  },
};

static size_t num_vars = sizeof(vars) / sizeof(DefaultGUIModel::variable_t);

CapacitanceClampRtxiModule::CapacitanceClampRtxiModule(void)
  : DefaultGUIModel("Capacitance clamp", ::vars, ::num_vars)
{
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

CapacitanceClampRtxiModule::~CapacitanceClampRtxiModule(void)
{
}

void
CapacitanceClampRtxiModule::execute(void)
{
  return;
}

void
CapacitanceClampRtxiModule::initParameters(void)
{
  c_cell = DEFAULT_CAPACITANCE;
  c_target = DEFAULT_CAPACITANCE;
}

void
CapacitanceClampRtxiModule::update(DefaultGUIModel::update_flags_t flag)
{
  switch (flag) {
    case INIT:
      period = RT::System::getInstance()->getPeriod() * 1e-6; // ms
      setParameter("C_cell (pF)", c_cell);
      setParameter("C_target (pF)", c_target);
      break;

    case MODIFY:
        c_cell = getParameter("C_cell (pF)").toDouble();
        c_target = getParameter("C_target (pF)").toDouble();
      break;

    case UNPAUSE:
      break;

    case PAUSE:
      break;

    case PERIOD:
      period = RT::System::getInstance()->getPeriod() * 1e-6; // ms
      break;

    default:
      break;
  }
}

void
CapacitanceClampRtxiModule::customizeGUI(void)
{
    //to add buttons or change the layout, have a look at the original plugin template code
}

