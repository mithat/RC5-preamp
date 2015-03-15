/**
 * @file
 * @author    Mithat Konar (mithat ~at~ mithatkonar.com)
 * @copyright Copyright (C) 2015 Mithat Konar
 * @brief     Derived input switches
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

#ifndef SWITCHES_H
#define SWITCHES_H

#include "InputSwitch.h"
#include "config.h"
#include "utils.h"

/** Pulse VOL_UP_PIN when VOL_UP_SWITCH is activated. */
class VolUpSwitch : public InputSwitch
{
public:
    VolUpSwitch() : InputSwitch(VOL_UP_SWITCH, VOL_UP_PIN, ACTIVE, DEBOUNCE_LEN) {};
    virtual void action()
    {
        pulsePin(m_outPin, PULSE_LEN);
    }
};

/** Pulse VOL_DN_PIN when VOL_DN_SWITCH is activated. */
class VolDnSwitch : public InputSwitch
{
public:
    VolDnSwitch() : InputSwitch(VOL_DN_SWITCH, VOL_DN_PIN, ACTIVE, DEBOUNCE_LEN) {};
    virtual void action()
    {
        pulsePin(m_outPin, PULSE_LEN);
    }
};

/** Pulse SOURCE_UP_PIN when SOURCE_UP_SWITCH is activated. */
class SrcUpSwitch : public InputSwitch
{
public:
    SrcUpSwitch() : InputSwitch(SOURCE_UP_SWITCH, SOURCE_UP_PIN, ACTIVE, DEBOUNCE_LEN) {};
    virtual void action()
    {
        pulsePin(m_outPin, PULSE_LEN);
    }
};


/** Pulse SOURCE_UP_PIN when SOURCE_UP_SWITCH is activated. */
class SrcDnSwitch : public InputSwitch
{
public:
    SrcDnSwitch() : InputSwitch(SOURCE_DN_SWITCH, SOURCE_DN_PIN, ACTIVE, DEBOUNCE_LEN) {};
    virtual void action()
    {
        pulsePin(m_outPin, PULSE_LEN);
    }
};

/** Toggle system power state when SOURCE_UP_SWITCH is activated. */
class PwrSwitch : public InputSwitch
{
public:
    PwrSwitch() : InputSwitch(PWR_SWITCH, PWR_PIN, ACTIVE, DEBOUNCE_LEN) {};
    virtual void action()
    {
        pulsePin(m_outPin, PULSE_LEN);
    }
};

/** Toggle system mute state when MUTE_SWITCH is activated. */
class MuteSwitch : public InputSwitch
{
public:
    MuteSwitch() : InputSwitch(MUTE_SWITCH, MUTE_PIN, ACTIVE, DEBOUNCE_LEN) {};
    virtual void action()
    {
        pulsePin(m_outPin, PULSE_LEN);
    }
};

#endif // SWITCHES_H
