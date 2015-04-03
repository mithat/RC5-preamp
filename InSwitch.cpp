/**
 * @file
 * @author    Mithat Konar (mithat ~at~ mithatkonar.com)
 * @copyright Copyright (C) 2015 Mithat Konar
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

#include "InSwitch.h"

InSwitch::InSwitch(uint8_t inPin, uint8_t activeState, unsigned long debounceLen)
{
    m_inPin = inPin;
    m_outPin = UCHAR_MAX;
    m_activeState = activeState;
    m_debounceLen = debounceLen;
}

bool InSwitch::poll()
{
    if (digitalRead(m_inPin) == m_activeState)
    {
        delay(m_debounceLen);
        if (digitalRead(m_inPin) == m_activeState)
        {
            action();
            return true;
        }
    }
    return false;
}
