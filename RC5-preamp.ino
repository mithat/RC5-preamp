/*
 * Copyright (C) 2015 Mithat Konar (mithat ~at~ mithatkonar.com).
 *
 * This file is part of RC-preamp-minimal.
 *
 * RC-preamp-minimal is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * RC-preamp-minimal is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with RC-preamp-minimal.  If not, see <http://www.gnu.org/licenses/>.
 */

#define PDEBUG  // uncomment to print useful stuff to Serial, comment for production.

#include <RC5.h>

// ====================
// Constants
// ====================

// Total I/O:
//   7 digital inputs
//   7 digital outputs

// Inputs
#define IR_PIN 2            // Pin to which the IR decoder chip connects.

// Outputs
#define VOL_UP_PIN    12    // Goes high when volume should increase.
#define VOL_DN_PIN    11    // Goes high when volume should decrease.
#define SOURCE_UP_PIN 10    // Goes high when input should cycle to next source.
#define SOURCE_DN_PIN 9     // Goes high when input should cycle to previous source.
#define MUTE_PIN      8     // Goes high when system should mute.
#define PWR_PIN       7     // Goes high iff system is in powered-up state.
#define RC_CMD_PIN    13    // Changes state when valid command is received.

// UI
#define VOL_UP_SWITCH   A0  // Input pin: debounced volume up switch.
#define VOL_DN_SWITCH   A1  // Input pin: debounced volume down switch.
#define SOURCE_UP_SWITCH A2 // Input pin: debounced input source up switch.
#define SOURCE_DN_SWITCH A3 // Input pin: debounced input source down switch.
#define MUTE_SWITCH     A4  // Input pin: debounced mute switch.
#define PWR_SWITCH      A5  // Input pin: debounced power switch (momentary).

// RC5 commands
// Taken from http://en.wikipedia.org/wiki/RC-5#System_and_Command_Codes
// and real-world testing with an RCA RCRN0GR universal remote.
#define DEVICE_PREAMP 16
#define CMD_VOLUP     16
#define CMD_VOLDN     17
#define CMD_MUTE      13
#define CMD_INPUT     59
#define CMD_PWR       12    // This might be contentious. TODO: additional testing.

#define DN false    // Indicates downward travel for volume and input select.
#define UP true     // Indicates upward travel for volume and input select.

#define VOL_PULSE_LEN   100     // number of milliseconds volume pulses should last.
#define SOURCE_PULSE_LEN 1000   // number of milliseconds source select pulses should last.


// ====================================
// Program state variables and objects.
// ====================================
// "private"
unsigned long t0;
unsigned char togglePrevious;
unsigned char toggle;
unsigned char address;
unsigned char command;

// exposable in the API
bool isMute;
bool isPower;
RC5 rc5(IR_PIN);

// ==========
// Functions!
// ==========

/** Pulse the specified output pin for the given time in msec. */
void pulsePin(uint8_t pin, unsigned long len)
{
    digitalWrite(pin, HIGH);
    delay(len);
    digitalWrite(pin, LOW);
}

/** Acknowledge recipt of a valid RC command */
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
 * Handle a volume command.
 */
void volCmd(bool direction)
{
    setMute(false);
    pulsePin(direction == UP ? VOL_UP_PIN : VOL_DN_PIN, VOL_PULSE_LEN);
}

/**
 * Handle a mute command.
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
 * Handle an input (select) command.
 */
void sourceCmd(bool direction)
{
    pulsePin(direction == UP ? SOURCE_UP_PIN : SOURCE_DN_PIN, SOURCE_PULSE_LEN);
}

/**
 * Handle a power command.
 * Toggle power on explicit keypress.
 */
void pwrCmd()
{
    if (toggle != togglePrevious)
    {
        setPower(!isPower);
    }
}

// ===========
// Action time
// ===========
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
