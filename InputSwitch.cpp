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

#include "InputSwitch.h"

InputSwitch::InputSwitch(uint8_t inPin, uint8_t activeState, unsigned long debounceLen)
{
    m_inPin = inPin;
    m_outPin = UCHAR_MAX;
    m_activeState = activeState;
    m_debounceLen = debounceLen;
}

InputSwitch::InputSwitch(uint8_t inPin, uint8_t outPin, uint8_t activeState, unsigned long debounceLen)
{
    m_inPin = inPin;
    m_outPin = outPin;
    m_activeState = activeState;
    m_debounceLen = debounceLen;
}

bool InputSwitch::poll()
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
