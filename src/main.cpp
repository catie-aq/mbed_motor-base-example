/*
 * Copyright (c) 2023, CATIE
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "motor_base_example.h"

// Define the motor base update rate
#define MOTOR_BASE_RATE 100ms

static DigitalOut led1(LED1);

#define MOTOR_BASE_FLAG 0x01
Ticker MotorBaseUpdateTicker;
EventFlags MotorBaseFlag;
Thread motorBaseThread(osPriorityRealtime);
sixtron::MotorBaseExample *my_simulated_motor_base;

void MotorBaseUpdate()
{
    MotorBaseFlag.set(MOTOR_BASE_FLAG);
}

void motorBaseThreadMain()
{

    // Init the motor base, and thus all motors
    my_simulated_motor_base->init();

    while (true) {
        // wait for the flag trigger
        MotorBaseFlag.wait_any(MOTOR_BASE_FLAG);
        led1 = !led1;

        // Update motors speeds of the robot base
        my_simulated_motor_base->update();
    }
}

int main()
{
    // First, convert the rate of the loop in seconds [float]
    auto f_secs = std::chrono::duration_cast<std::chrono::duration<float>>(MOTOR_BASE_RATE);
    float dt_pid = f_secs.count();

    // Create a fake/simulated motor base (see motor_base_example.h for more infos)
    my_simulated_motor_base = new sixtron::MotorBaseExample(dt_pid);

    // Start the thread for motor base
    motorBaseThread.start(motorBaseThreadMain);

    // Setup ticker to update the motor base flag at exactly the defined rate
    MotorBaseUpdateTicker.attach(&MotorBaseUpdate, MOTOR_BASE_RATE);

    // Create a set of target speed
    sixtron::target_speeds my_target_speeds;

    while (true) {

        my_target_speeds.cmd_lin = 1.0f; // in m/s
        my_target_speeds.cmd_rot = 0.0f; // in rad/s
        my_simulated_motor_base->setTargetSpeeds(my_target_speeds);

        ThisThread::sleep_for(1s);

        my_target_speeds.cmd_lin = 0.0f; // in m/s
        my_target_speeds.cmd_rot = 3.14f; // in rad/s
        my_simulated_motor_base->setTargetSpeeds(my_target_speeds);

        ThisThread::sleep_for(1s);

        my_target_speeds.cmd_lin = -2.0f; // in m/s
        my_target_speeds.cmd_rot = 0.0f; // in rad/s
        my_simulated_motor_base->setTargetSpeeds(my_target_speeds);

        ThisThread::sleep_for(1s);

        my_target_speeds.cmd_lin = 0.0f; // in m/s
        my_target_speeds.cmd_rot = 6.28f; // in rad/s
        my_simulated_motor_base->setTargetSpeeds(my_target_speeds);

        ThisThread::sleep_for(1s);
    }
}
