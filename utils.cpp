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

#include "utils.h"
#include "config.h"

extern bool isMute;
extern bool isPower;

void pulsePin(uint8_t pin, unsigned long len)
{
    digitalWrite(pin, HIGH);
    delay(len);
    digitalWrite(pin, LOW);
}

void setMute(bool mute)
{
    isMute = mute;
    digitalWrite(MUTE_PIN, isMute);
}

// TODO: Get readme up to speed on power LED stuff.
// TODO: More better Doxygen comments for setPower().
void setPower(bool pwr)
{

#if POWERUP_FLASH_PERIOD > 0
#define NUM_FLASHES POWERUP_MUTE_LEN/POWERUP_FLASH_PERIOD
#else
#define NUM_FLASHES 0
#endif // POWERUP_FLASH_PERIOD
    if (pwr && !isPower)        // if powering up
    {
        setMute(true);
        isPower = pwr;
        digitalWrite(PWR_PIN, HIGH);

        // TODO: Poll rc5 and power switch to override powerup?
        for (int i = 0; i < NUM_FLASHES; i++)
        {
            digitalWrite(PWR_LED, HIGH);
            delay(POWERUP_FLASH_PERIOD/2);
            digitalWrite(PWR_LED, LOW);
            delay(POWERUP_FLASH_PERIOD/2);
        }

        digitalWrite(PWR_LED, HIGH);
        setMute(false);
    }
    else if (!pwr && isPower)   // if powering down
    {
        digitalWrite(PWR_LED, LOW);
        setMute(true);
        delay(POWERDOWN_DELAY);
        isPower = pwr;
        digitalWrite(PWR_PIN, LOW);
        delay(POWERUP_MUTE_LEN);
        setMute(false);
    }
}

void changeVolume(bool direction)
{
    setMute(false);
#ifdef LATCHING_VOLUME
    digitalWrite(direction == UP ? VOL_UP_PIN : VOL_DN_PIN, HIGH);
#else
    pulsePin(direction == UP ? VOL_UP_PIN : VOL_DN_PIN, PULSE_LEN);
#endif // LATCHING_VOLUME
}

#ifdef LATCHING_VOLUME
void unlatchVolume(bool direction)
{
    digitalWrite(direction == UP ? VOL_UP_PIN : VOL_DN_PIN, LOW);
}
#endif // LATCHING_VOLUME

void changeSource(bool direction)
{
    pulsePin(direction == UP ? SOURCE_UP_PIN : SOURCE_DN_PIN, PULSE_LEN);
}
