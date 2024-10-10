#ifndef INC_PID_H_
#define INC_PID_H_

#include "main.h"

struct Pid_Handle {
    // configuration
    float kp;
    float ki;
    float kd;

    // internal
    float target;

    float errPrev;
    float errInt;
};

void Pid_Init(struct Pid_Handle* handle);

float Pid_Update(struct Pid_Handle* handle, float current);

void Pid_Reset(struct Pid_Handle* handle);

#endif