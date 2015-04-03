#include "RCCommander.h"
#include "config.h"
#include "utils.h"

extern bool isMute;
extern bool isPower;

RCCommander::RCCommander(RC5 *rcDecoder)
{
    m_decoder = rcDecoder;
    m_togglePrevious = 99; // state of RC5 objet's toggle on initialization seems to be 0, so...
    m_consecutivePressed = 0;
}

void RCCommander::commandAck()
{
    digitalWrite(RC_CMD_PIN, !digitalRead(RC_CMD_PIN));
}

void RCCommander::volCmd(bool direction)
{
    changeVolume(direction);
}

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
        pulsePin(direction == UP ? SOURCE_UP_PIN : SOURCE_DN_PIN, PULSE_LEN);
    }
    else                            // if key held down,
    {
        m_consecutivePressed++;
        if (m_consecutivePressed % PULSE_SKIP == 0)    // execute only every PULSE_SKIP pulses
        {
            pulsePin(direction == UP ? SOURCE_UP_PIN : SOURCE_DN_PIN, PULSE_LEN);
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
