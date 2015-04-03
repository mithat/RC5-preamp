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

#ifndef RCCOMMANDER_H
#define RCCOMMANDER_H

#include <RC5.h>

/**
 * Decoder and processor of remote control communications.
 * The typical loop will be:
    if (rc->readCommand() && (rc->getAddress() == <desired-device>))
    {
        rc->processCommand();
    }
 */
class RCCommander
{
public:
    RCCommander(RC5 *rc5);

    unsigned char getAddress() {return m_address;}
    unsigned char getCommand() {return m_command;}
    unsigned char getToggle() {return m_toggle;}

    /**
    * Acknowledge receipt of a valid RC command.
    * Toggle the state of the RC_CMD_PIN.
    * @return void
    */
    void commandAck();

    /**
     * Handle a volume event.
     * Increase or decrease the volume.
     * Repeat on consecutive events.
     * @param  direction    UP or DOWN
     * @return void
     */
    void volCmd(bool direction);

    /**
     * Handle a mute event.
     * Toggle the mute state on explicit keypress (don't repeat on consecutive events).
     * @return void
     */
    void muteCmd();

    /**
     * Handle a source select event.
     * Select the next input source.
     * Repeat at a low rate on consecutive events.
     * @param  direction    UP or DOWN
     * @return void
     */
    void sourceCmd(bool direction);

    /**
     * Handle a power event.
     * Toggle power on explicit keypress (don't repeat on consecutive events).
     * @return void
     */
    void pwrCmd();

    /**
     * Read (acquire) a command from the decoder.
     * @return bool true iff a command was decoded.
     */
    bool readCommand();

    /**
     * Handle remote control commands.
     * @pre  ::m_address is DEVICE_PREAMP
     * @pre  ::m_command is valid.
     * @pre  ::m_toggle is valid.
     * @post ::m_togglePrevious set to ::m_toggle
     * @return void
     */
    void processCommand();
protected:
private:
    unsigned char m_address;            ///< code for the current RC address.
    unsigned char m_command;            ///< code for the current RC command.
    unsigned char m_toggle;             ///< toggle state of current RC command.
    unsigned char m_togglePrevious;     ///< toggle state of previously received RC command.
    unsigned long m_consecutivePressed; ///< counter for consecutive RC commands.
    RC5 *m_decoder;                     ///< the IR decoder
};

#endif // RCCOMMANDER_H
