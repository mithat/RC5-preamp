/**
 * @file
 * @author    Mithat Konar (mithat ~at~ mithatkonar.com)
 * @copyright Copyright (C) 2015 Mithat Konar
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

#ifndef INPUTSWITCHNOREPEAT_H
#define INPUTSWITCHNOREPEAT_H

#include "InSwitch.h"

/**
 * Abstract encapsulation of a non-repeating input switch.
 * An InSwitchNoRepeat triggers some action when it is active while being polled.
 * Repeated triggering of the associated action will be inhibited while the switch
 * is active. In other words, after an action is triggered, subsequent actions
 * will be inhibited until the switch is polled at least once in an inactive
 * state.
 * Non-abstract instances will typically be singletons.
 */
class InSwitchNoRepeat : public InSwitch
{
public:
    InSwitchNoRepeat(uint8_t inPin, uint8_t activeState, unsigned long debounceLen);

    /** Poll the switch and take action if needed. Virtual.
     * @return true iff action was taken.
     */
    virtual bool poll();
protected:
    uint8_t previousState;
private:
};

#endif // INPUTSWITCHNOREPEAT_H
