RC5-preamp
==========
_Because remote controlled audio is free and for the people._

RC5-preamp is an Arduino-based remote control processor designed to make it
easy to integrate basic remote control functionality into audio preamplifier
projects.

Requirements
------------
You will need an [Arduino UNO](http://www.arduino.cc/en/Main/arduinoBoardUno), 
Guy Carpenter's [RC5 library](https://github.com/guyc/RC5), an IR remote 
control that can send RC5 preamplifier commands (I used an [RCA RCRN08GR](http://www.rcaaudiovideo.com/remotes/6-8-devices/?sku=RCRN08GR) 
during development), and supporting hardware that will be 
documented below.

This project was built using Arduino 1.6.1. Other versions may work but are
not supported.

Use
---
### Hardware interface
Consult TODO for i/o pin mappings. Descriptions of each are given below.

### Behavior
RC5-preamp does not remember the state of the system when power cycled or 
reset. It was designed to be continuously powered, even when the system is
"off". Doing otherwise would make turning on power via remote control a little 
tricky.

RC5-preamp does not handle power on/off muting. This functionality should be 
built into the muting hardware if needed.

On powerup/reset, TODO will be LOW (power off), and TODO will be in a LOW (umnuted) state.

A power button press or remote control signal enables and disabled RC5-preamp from
processing other commands; it also sets TODO high (on) or low (off). This
can be used to control the power delivered to the preamplifier's other circuits.

Volume up/down button presses or remote control signals pulse the TODO lines on
each press for 100 msec. If you hold down one of these, the appropriate line
will be pulsed every 100 msec until the button is released. If the system is
muted when a volume up/down even happens, it will be unmuted.

A mute button press or remote control signals will toggle the mute state of the
system.

Source up/down button presses or source up remote control signals pulse the 
TODO lines on each press for 500 msec. Hold down one of these will pulse the 
appropriate line every 500 msec. Note that there is no remote control source 
down signal. I have not found an instance of an RC5 remote that provides 
this  functionality, nor does there appear to be a standard for it, so it is
unimplemented.

### Software 
Compile and upload this project onto your UNO using your favorite method, making sure the 
RC5 library is in `../libraries`.

License
-------
The RC5-preamp source code is licensed under the GPLv3. Details are in 
the file COPYING. Guy Carpenter's [RC5 library](https://github.com/guyc/RC5) 
carries its own license (BSD at the time of this writing) as does the Arduino
platform (GPL/LGPL for software, Creative Commons Attribution Share-Alike 
license for hardware at the time of this writing).

Be sure you know what freedoms and obligations this brings you.

Copyright (C) 2015 Mithat Konar.
