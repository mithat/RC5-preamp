/**
 * @file
 * @author    Mithat Konar (mithat ~at~ mithatkonar.com)
 * @copyright Copyright (C) 2015 Mithat Konar
 * @brief     Configuration constants
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

#ifndef CONFIG_H
#define CONFIG_H

// ====================
// Options
// ====================
//#define PDEBUG          // Print DEBUG stuff to Serial. Comment out or #undef for production.
//#define LATCHING_VOLUME // Comment out for pulsing volume control, uncomment for continuous on-until-off.
#define ACTIVE_LOW      // Uncomment to make switch inputs active low and enable pullups;
                        // comment out to make switch inputs active high with no pullups.
// =======
// Timings
// =======
#define PULSE_LEN       150         // Number of milliseconds output pulses should last.
#define PULSE_SKIP      5           // Number of pulses to skip in "long-gap" repetitions.
#define DEBOUNCE_LEN    20          // Number of milliseconds to debounce switches.
#define POWERUP_MUTE_LEN     4000   // Number of milliseconds to mute output on powerup.
#define POWERUP_FLASH_PERIOD 500    // Length of powerup LED flashing period (ms).
                                    // POWERUP_MUTE_LEN should be divisible by POWERUP_FLASH_PERIOD.
                                    // Set to 0 (zero) to disable.
#define POWERDOWN_DELAY 200         // Number of milliseconds to delay powering down so mute can engage.
#define LATCH_LEN       115         // Milliseconds between remote control "are we still latched?" detections.
                                    // (Only makes sense if LATCHING_VOLUME is defined)

// ====================
// I/O connections
// ====================
// UI
#define VOL_UP_SWITCH    A0 // Input: volume up switch.
#define VOL_DN_SWITCH    A1 // Input: volume down switch.
#define SOURCE_UP_SWITCH A2 // Input: input source up switch.
#define SOURCE_DN_SWITCH A3 // Input: input source down switch.
#define MUTE_SWITCH      A4 // Input: mute switch.
#define PWR_SWITCH       A5 // Input: power switch.
#define PWR_LED          6  // Output: power indicator.

// Remote control
#define IR_PIN        2     // Pin to which the IR decoder module connects.
#define RC_CMD_PIN    13    // Output: changes state when valid command is received.

// Control outputs
#define VOL_UP_PIN    12    // Pulses high when volume should increase.
#define VOL_DN_PIN    11    // Pulses high when volume should decrease.
#define SOURCE_UP_PIN 10    // Pulses high when input should cycle to next source.
#define SOURCE_DN_PIN 9     // Pulses high when input should cycle to previous source.
#define MUTE_PIN      8     // High when system is in muted state, low otherwise
#define PWR_PIN       7     // High when system is in powered-up state, low otherwise.


// ============
// RC5 commands
// ============
// Taken from http://en.wikipedia.org/wiki/RC-5#System_and_Command_Codes
// and real-world testing with an RCA RCRN0GR universal remote.
#define DEVICE_PREAMP 16
#define CMD_VOLUP     16
#define CMD_VOLDN     17
#define CMD_MUTE      13
#define CMD_INPUT     59    // This might be contentious.
                            // TODO: Additional testing of RC CMD_INPUT (59).
#define CMD_PWR       12


// ================================================
// Maybe you don't play with the rest of these, ok?
// ================================================
#define DN false    // Indicates downward travel for volume and input select.
#define UP true     // Indicates upward travel for volume and input select.

#ifdef ACTIVE_LOW
#define ACTIVE LOW
#define INACTIVE HIGH
#define INPUT_SWITCH INPUT_PULLUP
#else
#define ACTIVE HIGH
#define INACTIVE LOW
#define INPUT_SWITCH INPUT
#endif // ACTIVE_LOW

#endif // CONFIG_H
