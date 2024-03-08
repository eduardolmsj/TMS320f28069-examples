#include "teste.h"
#include "DSP28x_Project.h"

// Função para inicializar o controlador PID
void initPID(PIDController *pid, double kp, double ki, double kd, double setpoint) {
    pid->kp = kp;
    pid->ki = ki;
    pid->kd = kd;
    pid->setpoint = setpoint;
    pid->integral = 0;
    pid->prev_error = 0;
}

// Função para calcular a saída do controlador PID
double calculatePIDOutput(PIDController *pid, double process_variable) {
    // Calcula o erro
    double error = pid->setpoint - process_variable;

    // Calcula o termo proporcional
    double proportional = pid->kp * error;

    // Calcula o termo integral
    pid->integral += pid->ki * error;

    // Calcula o termo derivativo
    double derivative = pid->kd * (error - pid->prev_error);

    // Calcula a saída do controlador PID
    double output = proportional + pid->integral + derivative;

    // Atualiza o erro anterior
    pid->prev_error = error;

    return output;
}

// Função para simular o sistema controlado (exemplo simples)
double simulateSystem(double input) {
    // Sistema: uma função linear simples para este exemplo
    return 2.0 * input;
}

void PID_routine(double *pid_output, PIDController *pid, double kp, double ki, double kd, double setpoint, int adc_buffer_size, Uint16 DMABuf1[],unsigned long int *mean_adc_value) {
    initPID(pid, kp, ki, kd, setpoint);

    // Simula o sistema controlado
    *mean_adc_value = 0;
    Uint16 i;
    for (i=0;i<adc_buffer_size;i++) {
        *mean_adc_value += DMABuf1[i];
        //mean_adc_value += AdcResult.ADCRESULT0;
    }
    *mean_adc_value = (5.0/4095.0)*(*mean_adc_value)/adc_buffer_size;
    //StartDMACH1();
    double process_variable = (double) (*mean_adc_value);
    double time_step = 0.1; // Passo de tempo da simulação
    int num_steps = 100;

    for (i = 0; i < 50; i++) {
    *pid_output = calculatePIDOutput(&pid, process_variable);
    }
    scia_xmit(pid_output);
    return;
}


