/** @file utils.cpp
 * Miscellaneous utilities for RC-preamp. */

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

#include "utils.h"
#include "config.h"

extern unsigned char togglePrevious;
extern unsigned char toggle;
extern unsigned long consecutivePressed;
extern unsigned char address;
extern unsigned char command;
extern bool isMute;
extern bool isPower;

/**
 * Pulse the specified output pin for the given number of msec.
 * @param  pin  The pin to pulse.
 * @param  len  Milliseconds to pulse.
 * \return void
 */
void pulsePin(uint8_t pin, unsigned long len)
{
    digitalWrite(pin, HIGH);
    delay(len);
    digitalWrite(pin, LOW);
}

/**
 * Acknowledge receipt of a valid RC command.
 * Toggle the state of the RC_CMD_PIN.
 * @return void
 */
void commandAck()
{
    digitalWrite(RC_CMD_PIN, !digitalRead(RC_CMD_PIN));
}

/**
 * Set the mute state of the system.
 * Set MUTE_PIN HIGH or LOW.
 * @param  mute true for muted, false for unmuted.
 * @return void
 */
void setMute(bool mute)
{
    isMute = mute;
    digitalWrite(MUTE_PIN, isMute);
}

/**
 * Set the power state of the system.
 * Set PWR_PIN HIGH or LOW. Unmute the system if going from off to on.
 * @param  pwr  true to turn on, false to turn off.
 * @return void
 */
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
 * Pulse VOL_UP_PIN or VOL_DN_PIN. Repeat on consecutive events.
 * @param  direction    UP or DOWN
 * @return void
 */
void volCmd(bool direction)
{
    setMute(false);
    pulsePin(direction == UP ? VOL_UP_PIN : VOL_DN_PIN, PULSE_LEN);
}

/**
 * Handle a mute event.
 * Toggle the mute state on explicit keypress (don't repeat on consecutive events).
 * @return void
 */
void muteCmd()
{
    if (toggle != togglePrevious)
    {
        setMute(!isMute);
    }
}

/**
 * Handle a source select event.
 * Pulse SOURCE_UP_PIN or SOURCE_DN_PIN. Repeat at a low rate on consecutive events.
 * @param  direction    UP or DOWN
 * @return void
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
 * Toggle power on explicit keypress (don't repeat on consecutive events).
 * @return void
 */
void pwrCmd()
{
    if (toggle != togglePrevious)
    {
        setPower(!isPower);
    }
}
