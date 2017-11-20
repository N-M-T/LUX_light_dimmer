Qt AC lamp dimmer
=============================================

Control AC powered lamp with Arduino using Qt GUI application based on LUX sensor readings. 

Theory of AC phase control:

The AC power applied to the lamp is directly related to the total surface area of an AC waveform. Varying the amount of time that the full voltage is applied to a lamp will thus reduce the average power. 

To achieve this, a TRIAC is used to turn the voltage supply on and off at precise intervals. E.g. at every zero crossing, a detector sends a pulse to the Arduino. The Arduino then initiates an interrupt (an interrupt essentially makes the ardiuno stop whatever else it is doing and focus on the task at hand, which is necessary to synchronise with the AC wave), and turns off the TRIAC for a specified amount of time. The longer the time, the less average power reaches the lamp. Once this time has elapsed, the arduino turns on the TRIAC by sending a voltage to the gate. The TRIAC will then remain on, even after the gate voltage has been removed, until the next zero crossing event.

In the UK, the AC current oscillates at 50Hz. There are 1000ms in a second, so 1000ms/50 oscillations equates to 20ms per wave. Since there are 2 peaks in a wave, there are 10ms after each zero crossing event which can be regulated. E.g, turning the TRIAC off for 5ms after each zero crossing (10ms for each wave) would mean the voltage is turned off for 50% of the time. This = half the surface area of the waveform = half of the average power.


Requirements
-------------------
An Arduino Uno microcontroller, a circuit with a zero cross detector and a TRIAC (available from Krida electronics), an AC powered light bulb, and a computer. If you want to build your own version on Linux, follow the instructions below. There are also instructions for building a static Windows version, although I've arlready included a pre-build example in the Release folder.  


Build instructions
-------------------
Build on Ubuntu (need Qt5 and git):

sudo git clone https://github.com/N-M-T/LUX_light_dimmer

cd ~/LUX_light_dimmer/Serial_LUX_Qt

sudo qmake && sudo make



Build version for Windows on Ubuntu

1) build mxe with required modules (if you haven't already done so), this can take a while 

sudo git clone https://github.com/mxe/mxe

cd ~/mxe

sudo make qtbase qtserialport 


2) get to project directory (this might not work from ~/. In which case make a copy of the git repo and save somewhere else) and run the Qt Makefile generator tool (from the mxe build) 

export PATH=~/mxe/usr/bin:$PATH

~/mxe/usr/bin/i686-w64-mingw32.static-qmake-qt5

make


License Information
-------------------

All code is released under [GNU GPLv3.0](http://www.gnu.org/copyleft/gpl.html).

