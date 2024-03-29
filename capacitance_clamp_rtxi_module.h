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
 * This is a template header file for a user modules derived from
 * DefaultGUIModel with a custom GUI.
 */

#include <default_gui_model.h>
#include "capacitance_clamp_lib.h"

#define DEFAULT_CAPACITANCE 100
#define DEFAULT_PERIOD 1


class CapacitanceClampRtxiModule : public DefaultGUIModel
{

  Q_OBJECT

public:
  CapacitanceClampRtxiModule(void);
  virtual ~CapacitanceClampRtxiModule(void);

  void execute(void);
  void createGUI(DefaultGUIModel::variable_t*, int);
  void customizeGUI(void);

protected:
  virtual void update(DefaultGUIModel::update_flags_t);

private:
  CapacitanceClamp capacitanceClamp = CapacitanceClamp(DEFAULT_CAPACITANCE, DEFAULT_CAPACITANCE, DEFAULT_PERIOD);

  void initParameters();

private slots:
  // these are custom functions that can also be connected to events
  // through the Qt API. they must be implemented in plugin_template.cpp
};

double get_period_from_RTXI_in_ms();
