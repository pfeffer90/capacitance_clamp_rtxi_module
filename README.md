###Capacitance clamp

**Requirements:** None  
**Limitations:** None  

![Plugin Template GUI](plugin-template.png)

<!--start-->
Capacitance clamp module for [RTXI](http://rtxi.org)
<!--end-->

####Parameters
1. GUI Label - Example parameter

####States
1. A State - An example state


#### Functionality
1. User sets cell capacitance and target capacitance. (in pF)
2. Module reads in the membrane potential, should be possible to connect it to any voltage like input and returns the capacitance clamp current.
3. optional connecting to a membrane capacitance measurement module that allows to automatically measure capacitance and set the cell capacitance

**Steps, nice to have**
- somehow run part of the code out of RTXI, testing environment (Problem, Clion does not seem to like the plugin code
 and reports a lot of errors, alternative would be to get another source file into the compilation)
- a CMake Project to use the full functionality of CLion
