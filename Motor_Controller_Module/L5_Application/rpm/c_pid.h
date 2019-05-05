#ifndef C_PID_H
#define C_PID_H

#ifdef __cplusplus
extern "C" {
#endif

#define KP      0.001
#define KI      0.01
#define KD      0.1
#define DT      0.5
#define MIN     -255
#define MAX     255

typedef struct
{
    double dt;
    double max;
    double min;
    double kp;
    double ki;
    double kd;
    double pre_error;
    double integral;
} s_pid_t;

void createPID(s_pid_t *_pid);
double calculate(double targetSpeed, double actualSpeed, s_pid_t *_pid);

#ifdef __cplusplus
}
#endif

#endif // C_PID_H
