/*
 * Copyright (c) 2023, CATIE
 * SPDX-License-Identifier: Apache-2.0
 */

// ============ THIS FILE IS APPLICATION SPECIFIC ========================

#ifndef MOTOR_BASE_EXAMPLE_H
#define MOTOR_BASE_EXAMPLE_H

#include "mbed.h"
#include "motor_base/motor_base_two_wheels.h"

namespace sixtron {

#define ENC_WHEELS_DISTANCE (0.40f) // in meters
#define MAX_MOTOR_PWM 0.4f // With MBED, pwm command should be between -1.0f and +1.0f max

class MotorBaseExample: public MotorBaseTwoWheels {

public:
    MotorBaseExample(float rate_dt): MotorBaseTwoWheels(ENC_WHEELS_DISTANCE), _dt_pid(rate_dt) {};

    ~MotorBaseExample() = default;

    // Specific for this Example, uses two PIDs to control each motor.
    void init() override;

    // Specific for this Example.
    void update() override;

private:
    float _dt_pid; // in [s]
};
}

#endif // MOTOR_BASE_EXAMPLE_H
