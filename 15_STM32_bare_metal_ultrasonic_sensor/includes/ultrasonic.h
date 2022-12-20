#pragma once

//blocking measurement
void ultrasonic_init();
int ultrasonic_measure();

//interrupt-based measurement
void ultrasonic_int_init();
void ultrasonic_start_measure();