/**
 * @file
 * @author    Mithat Konar (mithat ~at~ mithatkonar.com)
 * @copyright Copyright (C) 2015 Mithat Konar
 * @brief     Main Arduino file.
 * @section   LICENSE
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
// TODO: Refactor state globals and utils into an object(s)?
// TODO: Refactor all RC stuff into an object?

bool isMute;    ///< mute state of the system
bool isPower;   ///< power state of the system
RC5 *rc5;       ///< remote control decoder
RCParams rc;    ///< remote control decoder params

#define NUM_SWITCHES 5
InSwitch* switchArr[NUM_SWITCHES];  ///< array of UI switches
InSwitch* pwrSw;                    ///< the power switch

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
    pwrSw = new PwrSwitch();
    switchArr[0] = new VolUpSwitch();
    switchArr[1] = new VolDnSwitch();
    switchArr[2] = new SrcUpSwitch();
    switchArr[3] = new SrcDnSwitch();
    switchArr[4] = new MuteSwitch();

    // Set intial state
    digitalWrite(RC_CMD_PIN, HIGH);
    rc.togglePrevious = 99; // state of rc5.toggle on initialization seems to be 0, so...
    rc.consecutivePressed = 0;
    setPower(false);     // makes sure the power is off on reset.
}

void loop()
{
    if (rc5->read(&rc.toggle, &rc.address, &rc.command) && (rc.address == DEVICE_PREAMP))
    {
#ifdef PDEBUG
        Serial.println("");
        Serial.print("rc.address: ");
        Serial.print(rc.address);
        Serial.print(" rc.command: ");
        Serial.print(rc.command);
        Serial.print(" [");
        Serial.print(rc.toggle);
        Serial.print("]");
        Serial.println();
#endif // PDEBUG
        rcProcessCommand();
    }
    // Unconditionally poll power switch.
    pwrSw->poll();

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
