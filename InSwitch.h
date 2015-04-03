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

#ifndef INSWITCH_H
#define INSWITCH_H

#include <limits.h>
#include <Arduino.h>

// TODO: Merge InSwitch with InSwitchNoRepeat by adding a "repeatOnConsecutive" member.

/**
 * Abstract encapsulation of an input switch.
 * An InSwitch triggers some action when it is active while being polled.
 * Non-abstract instances will typically be singletons.
 */
class InSwitch
{
public:
    /** Constructor for switches.
     * @param inPin         The pin associated with this switch.
     * @param outPin        The output pin acted on by ::action or UCHAR_MAX for none.
     * @param activeState   HIGH if switch is active high, LOW otherwise.
     * @param debounceLen   msecs needed to debounce switch
     */
    InSwitch(uint8_t inPin, uint8_t activeState, unsigned long debounceLen);

    // Accessors/mutators are YAGNI.

    /** The action associated with this switch. Pure virtual.
     * @return void
     */
    // TODO: No, really, this should be done with a function pointer rather than derived singletons,
    // but I don't know if function pointers are supported in Arduino. */
    virtual void action() =0;

    /** Poll the switch and take action if needed. Virtual.
     * @return true iff action was taken.
     */
    virtual bool poll();

protected:
    uint8_t m_inPin;        //!< Pin number associated with this switch.
    uint8_t m_outPin;       //!< Pin number associated with this switch.
    unsigned long m_debounceLen;    //!< msecs needed to debounce switch
    uint8_t m_activeState;  //!< HIGH iff active high, LOW otherwise.

private:

};

#endif // INSWITCH_H
