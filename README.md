Qt AC dimmer module controller
=============================================

Control AC lamp with arduino using Qt GUI application. 

This uses leading edge cutting phase control to reduce the power going to the lamp based on LUX sensor readings and user defined intended LUX. 

Theory of AC phase control:

The AC power (wattage) applied is directly related to the total surface area of an AC waveform. Varying the amount of time that the full voltage is applied to a lamp will thus reduce the average power going to the lamp. 

To acheive this, a TRIAC is used to turn the voltage supply on and off at precise intervals of the AC waveform. At every zero crossing, a detector sends a 5V pulse to the arduino. The arduino then initiates an interrupt (an interrupt essentially makes the arduno stop whatever else it is doing and focus on the task at hand, which is necessary to synchronise with the AC wave), and turns off the TRIAC for a specified amount of time. The longer the time, the less average power reaches the lamp. Once this time has elapsed, the arduino turns on the TRIAC by sending a voltage to the gate. The TRIAC will then remain on (letting voltage to the lamp) even after the gate voltage has been removed until the next zero crossing event and user specified amount of time.

In the UK, the AC current oscillates at 50Hz. There are 1000ms in a second, so 1000ms/50 oscillations equates to 20ms per wave. Since there are 2 peaks in a wave, there are 10ms after each zero crossing event which can be regulated. E.g, turning the TRIAC off for 5ms after each zero crossing (10ms for each wave) would mean the voltage is turned off for 50% of the time. This = half the surface area of the waveform = half of the average power. 

Theory of LUX sensor:

The adafruit LUX sensor converts 


Repository Contents
-------------------
* **/LUX_dimmer_module** - Arduino sketch.
* **/LUXMaster** - Qt Project files.


License Information
-------------------

All code is released under [GNU GPLv3.0](http://www.gnu.org/copyleft/gpl.html).

