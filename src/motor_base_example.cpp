/*
 * Copyright (c) 2023, CATIE
 * SPDX-License-Identifier: Apache-2.0
 */

// ============ THIS FILE IS APPLICATION SPECIFIC ========================

#include "motor_base_example.h"

namespace sixtron {

void MotorBaseExample::init()
{

    // In this function, should be setup the two motors used by the robot

    // If necessary, user can pass variables like the dt_pid to the class,
    // and use it here to setup all motors.

    // For the purpose of this example, nothing is set
}

void MotorBaseExample::update()
{

    // Compute new motors speed, if setTargetSpeeds() has been called
    computeMotorSpeeds();

    // Update all motor according to new speed commands.
    // For the purpose of this example, we just print the two speeds.

    printf("New speeds: L=%3.3f, R%3.3f\n", _targetSpeedMotorLeft, _targetSpeedMotorRight);
}
}
