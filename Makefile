PLUGIN_NAME = capacitance_clamp_rtxi_module

HEADERS = capacitance_clamp_lib.h\
           capacitance_clamp_rtxi_module.h\

SOURCES = capacitance_clamp_lib.cpp\
          capacitance_clamp_rtxi_module.cpp\
          moc_capacitance_clamp_rtxi_module.cpp\

LIBS = 

### Do not edit below this line ###

include $(shell rtxi_plugin_config --pkgdata-dir)/Makefile.plugin_compile
