/**
 * @file
 * @author    Mithat Konar (mithat ~at~ mithatkonar.com)
 * @copyright Copyright (C) 2015 Mithat Konar
 * @brief     Utilites
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

#ifndef UTILS_H
#define UTILS_H

#include <Arduino.h>

// ====================
// Utility functions
// ====================

/**
 * Pulse the specified output pin for the given number of msec.
 * @param  pin  The pin to pulse.
 * @param  len  Milliseconds to pulse.
 * @return void
 */
void pulsePin(uint8_t pin, unsigned long len);

/**
 * Set the mute state of the system.
 * Set MUTE_PIN HIGH or LOW.
 * @param  mute true for muted, false for unmuted.
 * @return void
 */
void setMute(bool mute);

/**
 * Set the power state of the system.
 * Set PWR_PIN HIGH or LOW. Unmute the system if going from off to on.
 * @param  pwr  true to turn on, false to turn off.
 * @return void
 */
void setPower(bool pwr);

/**
 * Increase or decrease the volume level.
 * @param  direction  UP or DN.
 * @return void
 */
void changeVolume(bool direction);

/**
 * Select the next or previous source input.
 * @param  direction  UP or DN.
 * @return void
 */
void changeSource(bool direction);

#endif // UTILS_H
