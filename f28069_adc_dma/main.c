//###########################################################################
//
// FILE:   Example_2806xdma_ram_to_ram.c
//
// TITLE:  DMA RAM to RAM Transfer for F28M35x Example
//
//! \addtogroup f2806x_example_list
//! <h1> DMA RAM to RAM Transfer (dma_ram_to_ram)</h1>
//!
//! Code will perform a block copy from L5 DMARAM to L6 DMARAM of 1024 words.
//! The transfer will be started by CPU Timer0.  This example uses a
//! data size of 32-bits decrease the transfer time.
//! An interrupt is taken each time a transfer completes (local_DINTCH1_ISR).
//!
//!
//! \b Watch \b Variables: \n
//! - DMABuf1        - Destination buffer for the DMA
//! - DMABuf2        - Source buffer for the DMA
//
//###########################################################################
// $TI Release: $
// $Release Date: $
// $Copyright:
// Copyright (C) 2009-2023 Texas Instruments Incorporated - http://www.ti.com/
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions 
// are met:
// 
//   Redistributions of source code must retain the above copyright 
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the 
//   documentation and/or other materials provided with the   
//   distribution.
// 
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
//###########################################################################

//
// Included Files
//
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File

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

volatile Uint16 *DMADest;
volatile Uint16 *DMASource;

//
// Function Prototypes

int adc, adc_interrupt=0, dma_interrupt=0;
//
__interrupt void local_DINTCH1_ISR(void);

__interrupt void adc_isr(void);
void Adc_Config(void);
//
// Main
//
void main(void)
{
    Uint16 i;
    
    //
    // Step 1. Initialize System Control:
    // PLL, WatchDog, enable Peripheral Clocks
    // This example function is found in the F2806x_SysCtrl.c file.
    //
    InitSysCtrl();

    //
    // Step 2. Initialize GPIO:
    // This example function is found in the F2806x_Gpio.c file and
    // illustrates how to set the GPIO to it's default state.
    //
    // InitGpio();  // Skipped for this example

    //
    // Step 3. Clear all interrupts and initialize PIE vector table:
    // Disable CPU interrupts
    //
    DINT;

    //
    // Initialize the PIE control registers to their default state.
    // The default state is all PIE interrupts disabled and flags
    // are cleared.
    // This function is found in the F2806x_PieCtrl.c file.
    //
    InitPieCtrl();

    //
    // Disable CPU interrupts and clear all CPU interrupt flags:
    //
    IER = 0x0000;
    IFR = 0x0000;

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    // This will populate the entire table, even if the interrupt
    // is not used in this example.  This is useful for debug purposes.
    // The shell ISR routines are found in F2806x_DefaultIsr.c.
    // This function is found in F2806x_PieVect.c.
    //
    InitPieVectTable();

    //
    // Interrupts that are used in this example are re-mapped to
    // ISR functions found within this file.
    //
    EALLOW;     // Allow access to EALLOW protected registers
    PieVectTable.DINTCH1= &local_DINTCH1_ISR;
    EDIS;       // Disable access to EALLOW protected registers

    IER = M_INT7 ;                   // Enable INT7 (7.1 DMA Ch1)
    EnableInterrupts();
    CpuTimer0Regs.TCR.bit.TSS  = 1;  // Stop Timer0 for now

    //
    // Step 5. User specific code, enable interrupts: Initialize DMA
    //
    DMAInitialize();

    //meu codigo
    InitAdc();  // For this example, init the ADC
    //InitAdcAio();
    AdcOffsetSelfCal();

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

        //
        // setup EOC1 to trigger ADCINT1 to fire
        //
        AdcRegs.INTSEL1N2.bit.INT1SEL   = 1;

        AdcRegs.ADCSOC0CTL.bit.CHSEL    = 4;  // set SOC0 channel select to ADCINA4
        AdcRegs.ADCSOC1CTL.bit.CHSEL    = 2;  // set SOC1 channel select to ADCINA2

        //
        // set SOC0 start trigger on EPWM1A, due to round-robin SOC0 converts
        // first then SOC1
        //
        AdcRegs.ADCSOC0CTL.bit.TRIGSEL  = 5;

        //
        // set SOC1 start trigger on EPWM1A, due to round-robin SOC0 converts
        // first then SOC1
        //
        AdcRegs.ADCSOC1CTL.bit.TRIGSEL  = 5;

        //
        // set SOC0 S/H Window to 7 ADC Clock Cycles, (6 ACQPS plus 1)
        //
        AdcRegs.ADCSOC0CTL.bit.ACQPS    = 6;

        //
        // set SOC1 S/H Window to 7 ADC Clock Cycles, (6 ACQPS plus 1)
        //
        AdcRegs.ADCSOC1CTL.bit.ACQPS    = 6;
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

        //
        // Wait for ADC interrupt
        //

    //

    //
    // Initialize Tables
    //
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
    //DMASource = &DMABuf2[0];
    DMACH1AddrConfig(DMADest,DMASource);
    
    //
    // Will set up to use 32-bit datasize, pointers are based on 16-bit words
    //
    DMACH1BurstConfig(15,0,1);
    
    //
    // so need to increment by 2 to grab the correct location
    //
    DMACH1TransferConfig(16,0,1);
    
    DMACH1WrapConfig(1,0,50,0);
    
    //
    // Use timer0 to start the x-fer.
    // Since this is a static copy use one shot mode, so only one trigger is 
    // needed. Also using 32-bit mode to decrease x-fer time
    //
    DMACH1ModeConfig(DMA_TINT0, PERINT_ENABLE, ONESHOT_ENABLE, CONT_ENABLE,
                     SYNC_DISABLE, SYNC_SRC, OVRFLOW_DISABLE, SIXTEEN_BIT,
                     CHINT_END, CHINT_ENABLE);

    StartDMACH1();

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
    for(;;)
    {
        adc = AdcResult.ADCRESULT0;
    }
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
    PieCtrlRegs.PIEACK.all |= PIEACK_GROUP7;
    dma_interrupt++;
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
    AdcRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;

    PieCtrlRegs.PIEACK.all |= PIEACK_GROUP1;   // Acknowledge interrupt to PIE
    adc_interrupt++;
    return;
}
// End of File
//

