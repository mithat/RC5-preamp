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

#define PDEBUG  // Print DEBUG stuff to Serial. Comment out or #undef for production.

#include "config.h"
#include "utils.h"
#include <RC5.h>

// ===================================
// Program state variables and objects
// ===================================
// TODO: Refactor globals and utils into a class(?)
// "private"
unsigned long t0;
unsigned char togglePrevious;
unsigned char toggle;
unsigned long consecutivePressed;   // counter for consecutive hold-down events.
unsigned char address;
unsigned char command;

// "exposable"
bool isMute;
bool isPower;

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

    pinMode(VOL_UP_SWITCH, INPUT_PULLUP);
    pinMode(VOL_DN_SWITCH, INPUT_PULLUP);
    pinMode(SOURCE_UP_SWITCH, INPUT_PULLUP);
    pinMode(SOURCE_DN_SWITCH, INPUT_PULLUP);
    pinMode(MUTE_SWITCH, INPUT_PULLUP);
    pinMode(PWR_SWITCH, INPUT_PULLUP);

    // Set intial state
    digitalWrite(RC_CMD_PIN, HIGH);
    togglePrevious = 99; // state of rc5.toggle on initialization seems to be 0, so...
    consecutivePressed = 0;
    setPower(false);    // makes sure the power is off on reset.
}

void loop()
{
    if (rc5->read(&toggle, &address, &command) && (address == DEVICE_PREAMP))
    {
        // Note: Generically blinking the LED blocks the redundant command as the
        // redundant command is sent within 100ms.

#ifdef PDEBUG
        Serial.println("");
        Serial.print("device: ");
        Serial.print(address);
        Serial.print(" command: ");
        Serial.print(command);
        Serial.print(" [");
        Serial.print(toggle);
        Serial.print("]");
        Serial.println();
#endif // PDEBUG

        if (isPower)
        {
            commandAck();
            switch (command)
            {
            case CMD_VOLUP:
                volCmd(UP);
                break;
            case CMD_VOLDN:
                volCmd(DN);
                break;
            case CMD_MUTE:
                muteCmd();
                break;
            case CMD_INPUT:
                sourceCmd(UP);
                break;
            case CMD_PWR:
                pwrCmd();
                break;
            default:
                ;
            }
        }
        else if (command == CMD_PWR)
        {
            commandAck();
            pwrCmd();
        }
        togglePrevious = toggle;
    }
}
