#ifndef RCCOMMANDER_H
#define RCCOMMANDER_H

#include <RC5.h>

class RCCommander
{
public:
    RCCommander(RC5 *rc5);

    /**
    * Acknowledge receipt of a valid RC command.
    * Toggle the state of the RC_CMD_PIN.
    * @return void
    */
    void commandAck();

    /**
     * Handle a volume event.
     * Pulse VOL_UP_PIN or VOL_DN_PIN. Repeat on consecutive events.
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
     * Pulse SOURCE_UP_PIN or SOURCE_DN_PIN. Repeat at a low rate on consecutive events.
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
