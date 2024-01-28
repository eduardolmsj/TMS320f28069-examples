/*
 * teste.h
 *
 *  Created on: 18 de jan de 2024
 *      Author: Eduardo
 */

#ifndef METHODS_HEADERS_TESTE_H_
#define METHODS_HEADERS_TESTE_H_

// Estrutura para armazenar os parâmetros do controlador PID
typedef struct {
    double kp;  // Ganho proporcional
    double ki;  // Ganho integral
    double kd;  // Ganho derivativo
    double setpoint;  // Valor desejado de referência
    double integral;   // Termo integral acumulado
    double prev_error; // Último erro
} PIDController;


//__interrupt void local_DINTCH1_ISR(void);
//
//__interrupt void adc_isr(void);

//void Config_adc (int channel);
//
//void Config_dma_4_adc(Uint16 DMADest[], Uint16 DMASource[], Uint16 DMABuf1[], Uint16 DMABuf2[], int adc_buffer_size);
//
//void initPID(PIDController *pid, double kp, double ki, double kd, double setpoint);
//double calculatePIDOutput(PIDController *pid, double process_variable);
//double simulateSystem(double input) ;
//void PID_routine(double *pid_output, PIDController *pid, double kp, double ki, double kd, double setpoint, int adc_buffer_size, Uint16 DMABuf1[]);
//
//void Config_GPIO();

#endif /* METHODS_HEADERS_TESTE_H_ */
