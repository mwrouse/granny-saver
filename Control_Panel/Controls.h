/**
 * Controls are the buttons and rotary encoder
 */
#ifndef CONTROLS_H
#define CONTROLS_H

#include "Strings.h"
#include "User_Config.h"
#include "datatypes.h"




class Controls {
    public:
        void init();

        bool isPrimaryButtonPressed();
        bool isSecondaryButtonPressed();

};

Controls controls = Controls();

#endif