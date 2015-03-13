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

#include <RC5.h>
#include "config.h"

// ===================================
// Program state variables and objects
// ===================================
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
RC5 rc5(IR_PIN);

// ====================
// Functions
// ====================

/** Pulse the specified output pin for the given time in msec. */
void pulsePin(uint8_t pin, unsigned long len)
{
    digitalWrite(pin, HIGH);
    delay(len);
    digitalWrite(pin, LOW);
}

/** Acknowledge receipt of a valid RC command */
void commandAck()
{
    digitalWrite(RC_CMD_PIN, !digitalRead(RC_CMD_PIN));
}

/** Set the mute state of the system. */
void setMute(bool mute)
{
    isMute = mute;
    digitalWrite(MUTE_PIN, isMute);
}

/** Set the power state of the system. */
void setPower(bool pwr)
{
    // unmute if going from off to on state
    if (!isPower && pwr)
    {
        setMute(false);
    }
    isPower = pwr;
    digitalWrite(PWR_PIN, isPower);
}

/**
 * Handle a volume event.
 */
void volCmd(bool direction)
{
    setMute(false);
    pulsePin(direction == UP ? VOL_UP_PIN : VOL_DN_PIN, PULSE_LEN);
}

/**
 * Handle a mute event.
 * Toggle the mute state on explicit keypress.
 */
void muteCmd()
{
    if (toggle != togglePrevious)
    {
        setMute(!isMute);
    }
}

/**
 * Handle an source select event.
 */
void sourceCmd(bool direction)
{
    if (toggle != togglePrevious)   // if new press
    {
        consecutivePressed = 0;
        pulsePin(direction == UP ? SOURCE_UP_PIN : SOURCE_DN_PIN, PULSE_LEN);
    }
    else                            // if key held down,
    {
        consecutivePressed++;
        if (consecutivePressed % PULSE_SKIP == 0)    // execute only every PULSE_SKIP pulses
        {
            pulsePin(direction == UP ? SOURCE_UP_PIN : SOURCE_DN_PIN, PULSE_LEN);
            Serial.println(consecutivePressed);
        }
    }
}

/**
 * Handle a power event.
 * Toggle power on explicit keypress.
 */
void pwrCmd()
{
    if (toggle != togglePrevious)
    {
        setPower(!isPower);
    }
}

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
    if (rc5.read(&toggle, &address, &command) && (address == DEVICE_PREAMP))
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
