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

#include "config.h"
#include "utils.h"
#include <RC5.h>

#ifdef ACTIVE_LOW
#define ACTIVE LOW
#define INACTIVE HIGH
#define INPUT_SWITCH INPUT_PULLUP
#else
#define ACTIVE HIGH
#define INACTIVE LOW
#define INPUT_SWITCH INPUT
#endif // ACTIVE_LOW

// ===================================
// Program state variables and objects
// ===================================
// TODO: Refactor globals (and utils) into an object(?)
// "private"
unsigned char rcAddress;            ///< code for the current RC address.
unsigned char rcCommand;            ///< code for the current RC command.
unsigned char rcToggle;             ///< toggle state of current RC command.
unsigned char rcTogglePrevious;     ///< toggle state of previously received RC command.
unsigned long rcConsecutivePressed; ///< counter for consecutive RC commands.

// "exposable"
bool isMute;    ///< mute state of the system.
bool isPower;   ///< power state of the system.

RC5 *rc5;

// ====================
// Action!
// ====================
void setup()
{
#ifdef PDEBUG
    Serial.begin(9600);
    Serial.println("Started");
#endif // PDEBUG

    rc5 = new RC5(IR_PIN);

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
}
