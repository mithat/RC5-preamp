/**
 * @file
 * @author    Mithat Konar (mithat ~at~ mithatkonar.com)
 * @copyright Copyright (C) 2015 Mithat Konar
 * @brief     Derived input switches
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

#ifndef SWITCHES_H
#define SWITCHES_H

#include "InSwitch.h"
#include "InSwitchNoRepeat.h"
#include "InSwitchLatching.h"
#include "config.h"
#include "utils.h"

extern bool isPower;
extern bool isMute;

/** Turn up the volume when the VOL_UP_SWITCH is activated. */
#ifdef LATCHING_VOLUME
class VolUpSwitch : public InSwitchLatching
{
public:
    VolUpSwitch() : InSwitchLatching(VOL_UP_SWITCH, ACTIVE, DEBOUNCE_LEN) {};
    virtual void action()
    {
        changeVolume(UP);
    }
    virtual void unlatchAction()
    {
        unlatchVolume(UP);
    }
};
#else  // #ndef LATCHING_VOLUME
class VolUpSwitch : public InSwitch
{
public:
    VolUpSwitch() : InSwitch(VOL_UP_SWITCH, ACTIVE, DEBOUNCE_LEN) {};
    virtual void action()
    {
        changeVolume(UP);
        delay(100); // extra delay to make consistent with RC repeat speed.
    }
};
#endif // LATCHING_VOLUME

#ifdef LATCHING_VOLUME
/** Turn down the volume when the VOL_DN_SWITCH is activated. */
class VolDnSwitch : public InSwitchLatching
{
public:
    VolDnSwitch() : InSwitchLatching(VOL_DN_SWITCH, ACTIVE, DEBOUNCE_LEN) {};
    virtual void action()
    {
        changeVolume(DN);
    }
    virtual void unlatchAction()
    {
        unlatchVolume(DN);
    }
};
#else  // #ndef LATCHING_VOLUME
class VolDnSwitch : public InSwitch
{
public:
    VolDnSwitch() : InSwitch(VOL_DN_SWITCH, ACTIVE, DEBOUNCE_LEN) {};
    virtual void action()
    {
        changeVolume(DN);
        delay(100); // extra delay to make consistent with RC repeat speed.
    }
};
#endif // LATCHING_VOLUME

/** Pulse SOURCE_UP_PIN when SOURCE_UP_SWITCH is activated. */
class SrcUpSwitch : public InSwitchNoRepeat
{
public:
    SrcUpSwitch() : InSwitchNoRepeat(SOURCE_UP_SWITCH, ACTIVE, DEBOUNCE_LEN) {};
    virtual void action()
    {
        changeSource(UP);
    }
};


/** Pulse SOURCE_UP_PIN when SOURCE_UP_SWITCH is activated. */
class SrcDnSwitch : public InSwitchNoRepeat
{
public:
    SrcDnSwitch() : InSwitchNoRepeat(SOURCE_DN_SWITCH, ACTIVE, DEBOUNCE_LEN) {};
    virtual void action()
    {
        changeSource(DN);
    }
};

/** Toggle system power state when SOURCE_UP_SWITCH is activated. */
class PwrSwitch : public InSwitchNoRepeat
{
public:
    PwrSwitch() : InSwitchNoRepeat(PWR_SWITCH, ACTIVE, DEBOUNCE_LEN) {};
    virtual void action()
    {
        setPower(!isPower);
    }
};

/** Toggle system mute state when MUTE_SWITCH is activated. */
class MuteSwitch : public InSwitchNoRepeat
{
public:
    MuteSwitch() : InSwitchNoRepeat(MUTE_SWITCH, ACTIVE, DEBOUNCE_LEN) {};
    virtual void action()
    {
        setMute(!isMute);
    }
};

#endif // SWITCHES_H
