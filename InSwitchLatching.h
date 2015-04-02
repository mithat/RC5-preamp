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

#ifndef INSWITCHLATCHING_H
#define INSWITCHLATCHING_H

#include "InSwitch.h"

/**
 * Abstract class for a latching input switch.
 * An InSwitchLatching triggers some action when it is active while being polled
 * and an unlatch action when it not active while being polled.
 * Non-abstract instances will typically be singletons.
 */

class InSwitchLatching : public InSwitch
{
public:
    /** Default constructor */
    //InSwitchLatching(uint8_t inPin, uint8_t activeState, unsigned long debounceLen);

    /** Poll the switch and take action if needed. Virtual.
     * @return true iff action was taken.
     */
    virtual bool poll();

    /** The unlatching action associated with this switch. Pure virtual.
     * @return void
     */
    virtual void unlatch() =0;;
protected:
private:
};

#endif // INSWITCHLATCHING_H
