/*
 * teste.c
 *
 *  Created on: 18 de jan de 2024
 *      Author: Eduardo
 */

#include "teste.h"
#include "DSP28x_Project.h"

__interrupt void local_DINTCH1_ISR(void);

__interrupt void adc_isr(void);

void config_interrupts() {
    PieVectTable.ADCINT1 = &adc_isr;
    PieVectTable.DINTCH1= &local_DINTCH1_ISR;
//    EDIS;
//    DINT;
//    IER = 0x0000;
//    IFR = 0x0000;
//    EALLOW;
//    IER |= M_INT7 ;                   // Enable INT7 (7.1 DMA Ch1)
//    EnableInterrupts();
//    DINT;
//    IER = 0x0000;
//    IFR = 0x0000;
//    EALLOW;
//    IER |= M_INT1;                   // Enable CPU Interrupt 1
//    EnableInterrupts();
//    DINT;
//    EINT;
//    ERTM;
    EALLOW;
    DINT;
    //DMA interrupt
    PieCtrlRegs.PIEIFR7.bit.INTx1 = 1; // interrupt flag register (IFR) set to GROUP7 int1 (DMA channel 1)
    PieCtrlRegs.PIEIER7.bit.INTx1 = 1; // interrupt enable register (IFR) set to GROUP7 int1 (DMA channel 1)
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP7; // acknowledge GROUP7
    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;
    //ADC interrupt
    PieCtrlRegs.PIEIFR1.bit.INTx1 = 1; // interrupt flag register (IFR) set to GROUP1 int1 (adc int 1)
    PieCtrlRegs.PIEIER1.bit.INTx1 = 1; // interrupt enable register (IFR) set to GROUP1 int1 (adc int 1)
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1; // acknowledge GROUP1
    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;
    EINT;
    EDIS;
}

void Config_adc (int channel) {
//    EALLOW;
//    PieVectTable.ADCINT1 = &adc_isr;
//    EDIS;
//    IER = 0x0000;
//    IFR = 0x0000;
//    IER = M_INT7 ;                   // Enable INT7 (7.1 DMA Ch1)

    InitAdc();  // For this example, init the ADC

    AdcOffsetSelfCal();

    //
    // Enable ADCINT1 in PIE
    //
//    PieCtrlRegs.PIEIER1.bit.INTx1 = 1; // Enable INT 1.1 in the PIE
//    IER |= M_INT1;                     // Enable CPU Interrupt 1
//    EINT;                              // Enable Global interrupt INTM
//    ERTM;                              // Enable Global realtime interrupt DBGM

    //
    // Configure ADC
    //
    EALLOW;
    AdcRegs.ADCCTL2.bit.ADCNONOVERLAP = 1; // Enable non-overlap mode

    //
    // ADCINT1 trips after AdcResults latch
    //
    AdcRegs.ADCCTL1.bit.INTPULSEPOS = 1;

    AdcRegs.INTSEL1N2.bit.INT1E     = 1;  // Enabled ADCINT1
    AdcRegs.INTSEL1N2.bit.INT1CONT  = 1;  // Disable ADCINT1 Continuous mode


//     setup EOC1 to trigger ADCINT1 to fire

    AdcRegs.INTSEL1N2.bit.INT1SEL   = 1;

    AdcRegs.ADCSOC0CTL.bit.CHSEL    = channel;  // set SOC0 channel select to ADCINA4

    //
    // set SOC0 start trigger on EPWM1A, due to round-robin SOC0 converts
    // first then SOC1
    //
    AdcRegs.ADCSOC0CTL.bit.TRIGSEL  = 5;

    //
    // set SOC0 S/H Window to 7 ADC Clock Cycles, (6 ACQPS plus 1)
    //
    AdcRegs.ADCSOC0CTL.bit.ACQPS    = 6;

    EDIS;

    //
    // Assumes ePWM1 clock is already enabled in InitSysCtrl();
    //
    EPwm1Regs.ETSEL.bit.SOCAEN  = 1;        // Enable SOC on A group
    EPwm1Regs.ETSEL.bit.SOCASEL = 4;        // Select SOC from CMPA on upcount
    EPwm1Regs.ETPS.bit.SOCAPRD  = 1;        // Generate pulse on 1st event
    EPwm1Regs.CMPA.half.CMPA    = 0x0001;   // Set compare A value
    EPwm1Regs.TBPRD             = 0x0001;   // Set period for ePWM1
    EPwm1Regs.TBCTL.bit.CTRMODE = 0;        // count up and start
}

#define BUF_SIZE   1024  // Sample buffer size

void Config_dma_4_adc(Uint16 DMADest[], Uint16 DMASource[], Uint16 DMABuf1[], Uint16 DMABuf2[], int adc_buffer_size) {

//    EALLOW;
//    PieVectTable.DINTCH1= &local_DINTCH1_ISR;
//    EDIS;
//    IER = 0x0000;
//    IFR = 0x0000;
//    IER = M_INT7 ;                   // Enable INT7 (7.1 DMA Ch1)
//    EnableInterrupts();
    CpuTimer0Regs.TCR.bit.TSS  = 1;  // Stop Timer0 for now

    DMAInitialize();
    int i;
    for (i=0; i<BUF_SIZE; i++)
        {
            DMABuf1[i] = 0;
            DMABuf2[i] = i;
        }

    //
    // Configure DMA Channel
    //
    DMADest   = &DMABuf1[0];
    DMASource = &(AdcResult.ADCRESULT0);
    DMACH1AddrConfig(DMADest,DMASource);

    //
    // Will set up to use 32-bit datasize, pointers are based on 16-bit words
    //
    //DMACH1BurstConfig(15,0,1);
    DMACH1BurstConfig(1,0,0);

    //
    // so need to increment by 2 to grab the correct location
    //
    DMACH1TransferConfig((int)adc_buffer_size-1,0,1);

    DMACH1WrapConfig(1024,0,1024,0);

    //
    // Use timer0 to start the x-fer.
    // Since this is a static copy use one shot mode, so only one trigger is
    // needed. Also using 32-bit mode to decrease x-fer time
    //
    DMACH1ModeConfig(DMA_EPWM2A, PERINT_ENABLE, ONESHOT_ENABLE, CHINT_ENABLE,
                     SYNC_DISABLE, SYNC_SRC, OVRFLOW_DISABLE, SIXTEEN_BIT,
                     CHINT_END, CHINT_ENABLE);

    StartDMACH1();

    EPwm2Regs.ETSEL.bit.SOCAEN  = 1;        // Enable SOC on A group
    EPwm2Regs.ETSEL.bit.SOCASEL = 4;        // Select SOC from CMPA on upcount
    EPwm2Regs.ETPS.bit.SOCAPRD  = 1;        // Generate pulse on 1st event
    EPwm2Regs.CMPA.half.CMPA    = 0x0001;   // Set compare A value
    EPwm2Regs.TBPRD             = 0x0001;   // Set period for ePWM1
    EPwm2Regs.TBCTL.bit.CTRMODE = 0;        // count up and start

    //
    // Init the timer 0
    //

    //
    // load low value so we can start the DMA quickly
    //
    CpuTimer0Regs.TIM.half.LSW = 512;
    CpuTimer0Regs.TCR.bit.SOFT = 1;      // Allow to free run even if halted
    CpuTimer0Regs.TCR.bit.FREE = 1;
    CpuTimer0Regs.TCR.bit.TIE  = 1;      // Enable the timer0 interrupt signal
    CpuTimer0Regs.TCR.bit.TSS  = 0;      // restart the timer 0
}

//
// local_DINTCH1_ISR - INT7.1 DMA Channel 1
//
__interrupt void
local_DINTCH1_ISR(void)
{
    //
    // To receive more interrupts from this PIE group, acknowledge this
    // interrupt
    //
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;
//    PieCtrlRegs.PIEACK.all |= PIEACK_GROUP1;
    //mean_adc_value = 0;
    //Uint16 i;
    //for (i=0;i<adc_buffer_size;i++) {
    //    mean_adc_value += DMABuf1[i];
    //}
    //mean_adc_value = mean_adc_value >> 7;
    GpioDataRegs.GPATOGGLE.bit.GPIO1 = 1;
    StartDMACH1();

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    //__asm ("      ESTOP0");
    //for(;;);
}

__interrupt void
adc_isr(void)
{
    //
    // Clear ADCINT1 flag reinitialize for next SOC
    //
    AdcRegs.ADCINTFLGCLR.bit.ADCINT1 = 0;
    GpioDataRegs.GPBTOGGLE.bit.GPIO39 = 1;

//    PieCtrlRegs.PIEACK.all |= PIEACK_GROUP1;   // Acknowledge interrupt to PIE
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
    return;
}
////
//// End of File
