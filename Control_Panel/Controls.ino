#include "Controls.h"



void Controls::init(void)
{
    pinMode(PRIMARY_BTN, INPUT_PULLUP);
    pinMode(EXTRA_BTN, INPUT_PULLUP);
}



bool Controls::isPrimaryButtonPressed(void)
{
    return digitalRead(PRIMARY_BTN) == LOW;
}

bool Controls::isSecondaryButtonPressed(void)
{
    return digitalRead(EXTRA_BTN) == LOW;
}