/**
 * @file
 * @author    Mithat Konar (mithat ~at~ mithatkonar.com)
 * @copyright Copyright (C) 2015 Mithat Konar
 * @brief     Main Arduino file.
 * @section   LICENSE
 *
 * This file is part of RC5-preamp.
 *
 * RC5-preamp is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * RC5-preamp is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with RC5-preamp.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "RCCommander.h"
#include "config.h"
#include "utils.h"
#include "switches.h"

// ===================================
// Program state variables and objects
// ===================================

bool isMute;        ///< mute state of the system
bool isPower;       ///< power state of the system
RCCommander *rc;    ///< remote control processor

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
    pinMode(PWR_LED, OUTPUT);
    pinMode(RC_CMD_PIN, OUTPUT);

    pinMode(VOL_UP_SWITCH, INPUT_SWITCH);
    pinMode(VOL_DN_SWITCH, INPUT_SWITCH);
    pinMode(SOURCE_UP_SWITCH, INPUT_SWITCH);
    pinMode(SOURCE_DN_SWITCH, INPUT_SWITCH);
    pinMode(MUTE_SWITCH, INPUT_SWITCH);
    pinMode(PWR_SWITCH, INPUT_SWITCH);

    // Instantiate system objects.
    rc = new RCCommander(new RC5(IR_PIN));
    pwrSw = new PwrSwitch();
    switchArr[0] = new VolUpSwitch();
    switchArr[1] = new VolDnSwitch();
    switchArr[2] = new SrcUpSwitch();
    switchArr[3] = new SrcDnSwitch();
    switchArr[4] = new MuteSwitch();

    // Set initial state
    digitalWrite(RC_CMD_PIN, LOW);
    isPower = true;      // kludge to get setPower to work correctly
    setPower(false);     // makes sure the power is off on reset.
}

void loop()
{
    // Process an RC command or a button push, not both.
    if (rc->readCommand() && (rc->getAddress() == DEVICE_PREAMP))
    {
#ifdef PDEBUG
        Serial.println("");
        Serial.print("rc->address: "); Serial.print(rc->getAddress());
        Serial.print(" rc->command: "); Serial.print(rc->getCommand());
        Serial.print(" ["); Serial.print(rc->getToggle()); Serial.print("]");
        Serial.println();
#endif // PDEBUG
        rc->processCommand();
    }
    else
    {
#ifdef LATCHING_VOLUME
        rc->testVolLatch();
#endif // LATCHING_VOLUME

        // Unconditionally poll power switch.
        pwrSw->poll();

        // Poll remaining switches only if power is on.
        if (isPower)
        {
            for (int i = 0; i < NUM_SWITCHES; i++)
            {
                if (switchArr[i]->poll())
                    break;
            }
        }
    }
}
