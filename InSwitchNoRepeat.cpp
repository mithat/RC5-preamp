#include "InSwitchNoRepeat.h"

#include "config.h"

InSwitchNoRepeat::InSwitchNoRepeat(uint8_t inPin, uint8_t activeState, unsigned long debounceLen)
    : InSwitch(inPin, activeState, debounceLen)
{
    previousState = !m_activeState;
}

bool InSwitchNoRepeat::InSwitchNoRepeat::poll()
{
    if (digitalRead(m_inPin) == m_activeState)
    {
        delay(m_debounceLen);
        if (digitalRead(m_inPin) == m_activeState && (previousState == !m_activeState))
        {
            action();
            previousState = m_activeState;
            return true;
        }
    }
    else
    {
        previousState = !m_activeState;
    }
    return false;
}
