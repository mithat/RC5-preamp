#ifndef CONFIG_H
#define CONFIG_H

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

// ====================
// Config constants
// ====================

// UI
#define VOL_UP_SWITCH    A0 // Input: debounced N.O. volume up switch.
#define VOL_DN_SWITCH    A1 // Input: debounced N.O. volume down switch.
#define SOURCE_UP_SWITCH A2 // Input: debounced N.O. input source up switch.
#define SOURCE_DN_SWITCH A3 // Input: debounced N.O. input source down switch.
#define MUTE_SWITCH      A4 // Input: debounced N.O. mute switch.
#define PWR_SWITCH       A5 // Input: debounced N.O. power switch.
#define RC_CMD_PIN       13 // Output: changes state when valid command is received.

// Inputs
#define IR_PIN 2            // Pin to which the IR decoder chip connects.

// Outputs
#define VOL_UP_PIN    12    // Pulses high when volume should increase.
#define VOL_DN_PIN    11    // Pulses high when volume should decrease.
#define SOURCE_UP_PIN 10    // Pulses high when input should cycle to next source.
#define SOURCE_DN_PIN 9     // Pulses high when input should cycle to previous source.
#define MUTE_PIN      8     // Goes high when system should mute.
#define PWR_PIN       7     // Goes high when system is in powered-up state.

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

#define PULSE_LEN   150     // number of milliseconds pulses should last.
#define PULSE_SKIP  5       // number of pulses to skip in "long-gap" repetitions.

#endif
