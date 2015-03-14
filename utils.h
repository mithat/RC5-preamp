/** @file */

#ifndef UTILS_H
#define UTILS_H

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

#include <Arduino.h>

// ====================
// Utility functions
// ====================

void pulsePin(uint8_t pin, unsigned long len);
void rcCommandAck();
void setMute(bool mute);
void setPower(bool pwr);
void volCmd(bool direction);
void muteCmd();
void sourceCmd(bool direction);
void pwrCmd();
void rcProcessCommand();

#endif // UTILS_H
