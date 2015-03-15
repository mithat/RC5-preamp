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

#ifndef INPUTSWITCH_H
#define INPUTSWITCH_H

#include <limits.h>
#include <Arduino.h>

/**
 * Abstract encapsulation of an input switch.
 * Non-abstract instances will typically be singletons.
 */
class InputSwitch
{
public:
    /** Parmeterized constructor.
    * For switches not associated with an output.
     * \param inPin         The pin associated with this switch.
     * \param outPin        The output pin acted on by ::action or UCHAR_MAX for none.
     * \param activeState   HIGH if switch is active high, LOW otherwise.
     * \param debounceLen   msecs needed to debounce switch
     */
    InputSwitch(uint8_t inPin, uint8_t activeState, unsigned long debounceLen);

    /** Parmeterized constructor.
     * For switches not associated with an output.
     * \param inPin         The pin associated with this switch.
     * \param outPin        The output pin acted on by ::action or UCHAR_MAX for none.
     * \param activeState   HIGH if switch is active high, LOW otherwise.
     * \param debounceLen   msecs needed to debounce switch
     */
    InputSwitch(uint8_t inPin, uint8_t outPin, uint8_t activeState, unsigned long debounceLen);

    // Accessors are currently YAGNI.

    /** The action associated with this switch. Pure virtual.
     * \return void
     */
    // No, really, this should be a function pointer, but I don't know
    // if that's supported in Arduino.
    virtual void action() =0;

    /** Poll the switch and take action if needed. Virtual.
     * \return true iff action was taken.
     */
    virtual bool poll();

protected:
    uint8_t m_inPin;        //!< Pin number associated with this switch.
    uint8_t m_outPin;       //!< Pin number associated with this switch.
    unsigned long m_debounceLen;    //!< msecs needed to debounce switch
    uint8_t m_activeState;  //!< HIGH iff active high, LOW otherwise.

private:

};

#endif // INPUTSWITCH_H
