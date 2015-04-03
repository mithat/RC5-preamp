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

#include "RCCommander.h"
#include "utils.h"

extern bool isMute;
extern bool isPower;

RCCommander::RCCommander(RC5 *rcDecoder)
{
    m_decoder = rcDecoder;
    m_togglePrevious = 99; // state of RC5 object's toggle on initialization seems to be 0, so...
    m_consecutivePressed = 0;
#ifdef LATCHING_VOLUME
    m_volLatchTime = 0;
#endif // LATCHING_VOLUME
}

void RCCommander::commandAck()
{
    digitalWrite(RC_CMD_PIN, !digitalRead(RC_CMD_PIN));
}

void RCCommander::volCmd(bool direction)
{
#ifdef LATCHING_VOLUME
    m_volLatchTime = millis();  // update most recent latch time
#endif // LATCHING_VOLUME
    changeVolume(direction);
}

#ifdef LATCHING_VOLUME
void RCCommander::testVolLatch()
{
    if (m_volLatchTime > 0)
    {
        // if we're past the due date or millis() has overflown ...
        if (millis() > (m_volLatchTime + LATCH_LEN) || millis() < m_volLatchTime)
        {
            // reset volumes
            unlatchVolume(UP);
            unlatchVolume(DN);

            // reset latch state
            m_volLatchTime = 0;
        }
    }
}
#endif // LATCHING_VOLUME

void RCCommander::muteCmd()
{
    if (m_toggle != m_togglePrevious)
    {
        setMute(!isMute);
    }
}

void RCCommander::sourceCmd(bool direction)
{
    if (m_toggle != m_togglePrevious)   // if new press
    {
        m_consecutivePressed = 0;
        changeSource(UP);
    }
    else                            // if key held down,
    {
        m_consecutivePressed++;
        if (m_consecutivePressed % PULSE_SKIP == 0)    // execute only every PULSE_SKIP pulses
        {
            changeSource(UP);
        }
    }
}

void RCCommander::pwrCmd()
{
    if (m_toggle != m_togglePrevious)
    {
        setPower(!isPower);
    }
}

bool RCCommander::readCommand()
{
    return m_decoder->read(&m_toggle, &m_address, &m_command);
}

void RCCommander::processCommand()
{
    if (isPower)
    {
        commandAck();
        switch (m_command)
        {
        case CMD_VOLUP:
            volCmd(UP);
            break;
        case CMD_VOLDN:
            volCmd(DN);
            break;
        case CMD_MUTE:
            muteCmd();
            break;
        case CMD_INPUT:
            sourceCmd(UP);
            break;
        case CMD_PWR:
            pwrCmd();
            break;
        default:
            ;
        }
    }
    else if (m_command == CMD_PWR)
    {
        commandAck();
        pwrCmd();
    }
    m_togglePrevious = m_toggle;
}
