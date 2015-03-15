/** @file */

/*
 * Copyright (C) 2015 Mithat Konar (mithat ~at~ mithatkonar.com).
 *
 * This file is part of RC-preamp.
 *
 * RC-preamp is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * RC-preamp is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with RC-preamp.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <RC5.h>
#include "config.h"
#include "utils.h"
#include "switches.h"

// ===================================
// Program state variables and objects
// ===================================
// TODO: Refactor state globals and utils into an object(?)
// remote control
unsigned char rcAddress;            ///< code for the current RC address.
unsigned char rcCommand;            ///< code for the current RC command.
unsigned char rcToggle;             ///< toggle state of current RC command.
unsigned char rcTogglePrevious;     ///< toggle state of previously received RC command.
unsigned long rcConsecutivePressed; ///< counter for consecutive RC commands.

// system
bool isMute;    ///< mute state of the system.
bool isPower;   ///< power state of the system.
RC5 *rc5;       ///< remote control decoder

#define NUM_SWITCHES 5
InputSwitch* switchArr[NUM_SWITCHES];
InputSwitch* pwrSwitch;

// switch states
int previousPwr = INACTIVE;

// ====================
// Action!
// ====================
void setup()
{
#ifdef PDEBUG
    Serial.begin(9600);
    Serial.println("Started");
#endif // PDEBUG

    // Config I/O
    pinMode(VOL_UP_PIN, OUTPUT);
    pinMode(VOL_DN_PIN, OUTPUT);
    pinMode(SOURCE_UP_PIN, OUTPUT);
    pinMode(SOURCE_DN_PIN, OUTPUT);
    pinMode(MUTE_PIN, OUTPUT);
    pinMode(PWR_PIN, OUTPUT);
    pinMode(RC_CMD_PIN, OUTPUT);

    pinMode(VOL_UP_SWITCH, INPUT_SWITCH);
    pinMode(VOL_DN_SWITCH, INPUT_SWITCH);
    pinMode(SOURCE_UP_SWITCH, INPUT_SWITCH);
    pinMode(SOURCE_DN_SWITCH, INPUT_SWITCH);
    pinMode(MUTE_SWITCH, INPUT_SWITCH);
    pinMode(PWR_SWITCH, INPUT_SWITCH);

    // Instantiate system objects.
    rc5 = new RC5(IR_PIN);
    pwrSwitch = new PwrSwitch();
    switchArr[0] = new VolUpSwitch();
    switchArr[1] = new VolDnSwitch();
    switchArr[2] = new SrcUpSwitch();
    switchArr[3] = new SrcDnSwitch();
    switchArr[4] = new MuteSwitch();

    // Set intial state
    digitalWrite(RC_CMD_PIN, HIGH);
    rcTogglePrevious = 99; // state of rc5.toggle on initialization seems to be 0, so...
    rcConsecutivePressed = 0;
    setPower(false);     // makes sure the power is off on reset.
}

void loop()
{
    if (rc5->read(&rcToggle, &rcAddress, &rcCommand) && (rcAddress == DEVICE_PREAMP))
    {
#ifdef PDEBUG
        Serial.println("");
        Serial.print("rcAddress: ");
        Serial.print(rcAddress);
        Serial.print(" rcCommand: ");
        Serial.print(rcCommand);
        Serial.print(" [");
        Serial.print(rcToggle);
        Serial.print("]");
        Serial.println();
#endif // PDEBUG
        rcProcessCommand();
    }

//    // Poll the switches because the remote control library may use timer interrupts.
//    if (digitalRead(PWR_SWITCH) == ACTIVE)
//    {
//        delay(DEBOUNCE_LEN);
//        if ((digitalRead(PWR_SWITCH) == ACTIVE) && (previousPwr == INACTIVE))
//        {
//            setPower(!isPower);
//            previousPwr = ACTIVE;
//        }
//    }
//    else
//    {
//        previousPwr = INACTIVE;
//    }

    // Unconditionally poll power switch.
    pwrSwitch->poll();

    // Poll remaining switches
    if (isPower)
    {
        for (int i = 0; i < NUM_SWITCHES; i++)
        {
            if (switchArr[i]->poll())
                break;
        }
    }
}
