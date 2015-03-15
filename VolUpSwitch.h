#ifndef VOLUPSWITCH_H
#define VOLUPSWITCH_H

#include "InputSwitch.h"
#include "config.h"
#include "utils.h"

/** Pulse VOL_UP_PIN when VOL_DN_SWITCH is activated. */
class VolUpSwitch : public InputSwitch
{
public:
    /** Constructor for VOL_DN_SWITCH. */
    VolUpSwitch() : InputSwitch(VOL_UP_SWITCH, VOL_UP_PIN, ACTIVE, DEBOUNCE_LEN) {};

    /** Pulse VOL_UP_PIN.
     * \return void
     */
    virtual void action()
    {
        pulsePin(m_outPin, PULSE_LEN);
    }
protected:
private:
};

#endif // SOURCEUPSWITCH_H
