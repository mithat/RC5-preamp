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

#ifndef INSWITCHLATCHING_H
#define INSWITCHLATCHING_H

#include "InSwitch.h"

/**
 * Abstract class for a latching input switch.
 * An InSwitchLatching triggers an action once when it is active
 * while being polled and an unlatch action once when it not active
 * while being polled.
 * Member functions action and unlatchAction do not need to manage
 * the latch state; they need only specify what happens when the
 * switch is first pressed and then what happens when it is
 * released.
 * Non-abstract instances will typically be singletons.
 */
// TODO: merge InSwitchLatching with base InSwitchclass?
// This will require rethinking the "latch once" behavior.
class InSwitchLatching : public InSwitch
{
public:
    InSwitchLatching(uint8_t inPin, uint8_t activeState, unsigned long debounceLen);

    /** Poll the switch and take action if needed. Virtual.
     * @return true iff action was taken.
     */
    virtual bool poll();

    /** The action that should take place when the switch is unlatched. Pure virtual.
     * @return void
     */
    virtual void unlatchAction() =0;

protected:
    bool isLatched;

private:
};

#endif // INSWITCHLATCHING_H
