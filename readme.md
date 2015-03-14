RC5-preamp
==========
_Because remote controlled audio is free and for the people.™_

RC5-preamp is an [Arduino](http://www.arduino.cc) sketch that tries to make integrating basic remote control functionality into audio preamplifier projects fun and 
painless.

Requirements
------------
You will need an [Arduino Uno](http://www.arduino.cc/en/Main/arduinoBoardUno), 
Guy Carpenter's [RC5 library](https://github.com/guyc/RC5), an IR remote 
control that can send RC5 preamplifier commands, and supporting hardware as 
documented below. (I used an 
[RCA RCRN08GR](http://www.rcaaudiovideo.com/remotes/6-8-devices/?sku=RCRN08GR) 
universal remote during development.)

RC5-preamp was built using the Arduino 1.6.1 framework. Other Arduino framework versions may work but are not supported.

Features
--------
TODO: Feature description

Use
-----
Descriptions of each I/O pin are given below. Consult `config.h` for pin
mappings. 

All inputs and outputs are, in Arduino parlance, 'digital'.

### User interface

**The input switches listed here are not yet implemented!**

Pin name           | Type         | Function
------------------ | ------------ | -------------------------------
`VOL_UP_SWITCH`    | input switch | When pressed, pulses `VOL_UP_PIN`
`VOL_DN_SWITCH`    | input switch | When pressed, pulses `VOL_DN_PIN`
`SOURCE_UP_SWITCH` | input switch | When pressed, pulses `SOURCE_UP_PIN`
`SOURCE_DN_SWITCH` | input switch | When pressed, pulses `SOURCE_DN_PIN`
`MUTE_SWITCH`      | input switch | Toggles mute state of the system. Sets `MUTE_PIN` `HIGH` or `LOW` as needed.
`PWR_SWITCH`       | input switch | Toggles power state of the system. Sets `PWR_PIN` `HIGH` or `LOW` as needed.
`RC_CMD_PIN`       | output       | Toggles state when a valid command is received.

All switches are normally open momentary types (i.e., LOW when not not pressed) 
and _need to be electronically (i.e., hardware) debounced_.

Note that if you want to use `RC_CMD_PIN` to flash an LED when a remote control 
command is received, you must trigger the LED on both rising and falling edges.

### H/W

Pin name           | Type   | Function
------------------ | ------ | -------------------------------
`IR_PIN 2`         | input  | Pin to which the IR decoder module connects.
`VOL_UP_PIN`       | output | Pulses high when volume should increase.
`VOL_DN_PIN`       | output | Pulses high when volume should decrease.
`SOURCE_UP_PIN`    | output | Pulses high when input should cycle to the next input source.
`SOURCE_DN_PIN`    | output | Pulses high when input should cycle to the previous source.
`MUTE_PIN`         | output | High when system should mute, low otherwise
`PWR_PIN`          | output | High when system is in powered-up state, low otherwise

The IR decoder module should use a
[36 kHz carrier](http://en.wikipedia.org/wiki/RC-5#Protocol_Details). The 
[Vishay TSOP34136](http://www.vishay.com/docs/82490/tsop321.pdf)
seems to work well.

`VOL_UP_PIN` and `VOL_DN_PIN` will each pulse for about 150 msec on a 
corresponding event. You should be able to connect `VOL_UP_PIN` and 
`VOL_DN_PIN` to a motorized potentiometer through an 
[H-bridge](http://en.wikipedia.org/wiki/H_bridge) or to a digital 
potentiometer through appropriate glue logic.

_Don't attempt to use `VOL_UP_PIN` and `VOL_DN_PIN` to drive a motorized 
potentiometer directly!_ It won't work and you may fry your Arduino. A circuit 
using available motorized potentiometers is under development.

If you use a digital potentiometer, you'll need to implement the logic in front
of it that senses the command pulses and delivers the appropriate control
signals to the digital potentiometer. A circuit using the
[Maxim DS1882](http://www.maximintegrated.com/en/products/analog/data-converters/digital-potentiometers/DS1882.html/tb_tab0)
and another Arduino for interfacing is under development.

`SOURCE_UP_PIN` and `SOURCE_DN_PIN` will each pulse for about 150 msec on a
corresponding event. Design of an appropriate input switching circuit using 
relay switching under control by another Arduino is under development.

The `MUTE_PIN` can be used to control a digital volume potentiometer's 
attenuation or an additional muting circuit.

Since RC5-preamp wants to be on continuously (see **Behavior** below), it's 
expected that you'll use `PWR_PIN` to control the power delivered to the rest 
of the preamp--possibly via relay switching of a separate mains power 
transformer.

### Behavior
RC5-preamp was designed to be powered continuously, even when the preamp is 
"off". Doing otherwise would make powering on the system via remote control a 
mite tricky.

RC5-preamp does not remember the state of the system when the power is cycled 
or the Arduino is reset. On power-up/reset, `PWR_PIN` will be `LOW`
(i.e., power off) and `MUTE_PIN` will be in a `LOW` (i.e., umnuted) state.

RC5-preamp does not handle power on/off muting. This functionality should be 
built into the muting hardware if needed.

A power button press or remote control signal toggles `PWR_PIN` `HIGH` (on) or 
`LOW` (off).  When in the off state, RC5-preamp is inhibited from processing 
commands other than power button and remote control signals. `PWR_PIN` can be 
used to control the main power delivered to the preamp--possibly via relay
control.

Volume up/down button presses or remote control signals will pulse the 
`VOL_UP_PIN` or `VOL_DN_PIN` outputs (whichever is appropriate) for
about 150 msec on each press. Holding down any of these of these will pulse
the appropriate output about every 150 msec. If the system is muted when a 
volume up/down even happens, it will be unmuted.

A mute button press or remote control signal will toggle the mute state of the
system.

Source up/down button presses or source up remote control signals will pulse
the `SOURCE_UP_PIN` or `SOURCE_DN_PIN` outputs (whichever is appropriate) for
about 150 msec on each press. Holding down any of these of these will pulse
the appropriate output about every 500 msec. Note that there is no remote 
control source down signal. I have not found an instance of an RC5 remote that 
provides  this  functionality, nor does there appear to be a standard for it, 
so it's not implemented.

### Software 
Making sure the [RC5 library](https://github.com/guyc/RC5) is in
`../libraries`, compile and upload this project onto your Arduino Uno using 
your favorite method.

For development, I used Sudar's 
[Arduino-Makefile](https://github.com/sudar/Arduino-Makefile) in a customized 
C++ IDE. The project's child makefile is included in this distribution. Using
Arduino-Makefile and the child makefile is not required; the sketch should 
build just fine in the vanilla Arduino IDE.

With appropriate changes to the source code, you should be able adapt this 
project to other Arduinos, provided it can support the desired I/O. If you
do so, be sure to share the love. (See **License** below.)

License
-------
The RC5-preamp source code is licensed under the GPLv3. Details are in 
the file COPYING. Guy Carpenter's [RC5 library](https://github.com/guyc/RC5) 
carries its own license (BSD at the time of this writing) as does the
[Arduino platform](http://arduino.cc/en/Main/FAQ) (GPL/LGPL for software, 
Creative Commons Attribution Share-Alike license for hardware at the time of 
this writing).

Be sure you know what freedoms and obligations this brings you.

Copyright (C) 2015 Mithat Konar.
