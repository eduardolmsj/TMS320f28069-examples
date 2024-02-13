//
// Included Files
//
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include <stdio.h>
#include "teste.h"

int teste=0;

//

//
// Defines
//
#define BUF_SIZE   1024  // Sample buffer size

//
// DMA Defines
//
#define CH1_TOTAL               DATA_POINTS_PER_CHANNEL
#define CH1_WORDS_PER_BURST     ADC_CHANNELS_TO_CONVERT

#pragma DATA_SECTION(DMABuf1,"DMARAML5");
#pragma DATA_SECTION(DMABuf2,"DMARAML6");

volatile Uint16 DMABuf1[1024];
volatile Uint16 DMABuf2[1024];

int adc_buffer_size = 128;
Uint32 adc_value;
unsigned long int mean_adc_value=0;
double pid_output;

volatile Uint16 *DMADest;
volatile Uint16 *DMASource;

//__interrupt void local_DINTCH1_ISR(void);
//
//__interrupt void adc_isr(void);

//
// Main
//
void main(void)
{
    Uint16 i;

    InitSysCtrl();

    //
    DINT;

    //
    InitPieCtrl();

    IER = 0x0000;
    IFR = 0x0000;

    InitPieVectTable();

//    // point to interrupt function
//    EALLOW;
//    PieVectTable.ADCINT1 = &adc_isr;
//    PieVectTable.DINTCH1= &local_DINTCH1_ISR;
//    EDIS;
    Config_adc(2); //ADCINA2
    Config_dma_4_adc(DMADest, DMASource, DMABuf1, adc_buffer_size);
    Config_GPIO();
    config_interrupts();

    PIDController pid;
    for(;;)
    {
        adc_value = AdcResult.ADCRESULT0;
        double kp = 1.0;
        double ki = 0.1;
        double kd = 0.01;
        double setpoint = 10.0;
        int n =100;
        int insertion_arr[100];

        // Inicializa o controlador PID
        PID_routine(&pid_output, &pid, kp, ki, kd, setpoint, adc_buffer_size, DMABuf1, &mean_adc_value);
        insertion_rotine(n, insertion_arr);
        GpioDataRegs.GPBTOGGLE.bit.GPIO34 = 1;
    }
}


//__interrupt void
//local_DINTCH1_ISR(void)
//{
//    //
//    // To receive more interrupts from this PIE group, acknowledge this
//    // interrupt
//    //
//    PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;
////    PieCtrlRegs.PIEACK.all |= PIEACK_GROUP1;
//    //mean_adc_value = 0;
//    //Uint16 i;
//    //for (i=0;i<adc_buffer_size;i++) {
//    //    mean_adc_value += DMABuf1[i];
//    //}
//    //mean_adc_value = mean_adc_value >> 7;
//    GpioDataRegs.GPATOGGLE.bit.GPIO1 = 1;
//    StartDMACH1();

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    //__asm ("      ESTOP0");
    //for(;;);
//}
//
//__interrupt void
//adc_isr(void)
//{
//    //
//    // Clear ADCINT1 flag reinitialize for next SOC
//    //
//    AdcRegs.ADCINTFLGCLR.bit.ADCINT1 = 0;
//    GpioDataRegs.GPBTOGGLE.bit.GPIO39 = 1;
//
////    PieCtrlRegs.PIEACK.all |= PIEACK_GROUP1;   // Acknowledge interrupt to PIE
//    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
//    return;
//}
//
// End of File

