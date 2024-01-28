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
#include <stdio.h>
#include "teste.h"

int teste=0;

//}

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
    config_interrupts();
    Config_adc(2);
    Config_dma_4_adc(DMADest, DMASource, DMABuf1, DMABuf2, adc_buffer_size);
    Config_GPIO();

    PIDController pid;
    for(;;)
    {
        adc_value = AdcResult.ADCRESULT0;
        double kp = 1.0;
        double ki = 0.1;
        double kd = 0.01;
        double setpoint = 10.0;

        // Inicializa o controlador PID
        PID_routine(&pid_output, &pid, kp, ki, kd, setpoint, adc_buffer_size, DMABuf1, &mean_adc_value);

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
//    //
//    // Next two lines for debug only to halt the processor here
//    // Remove after inserting ISR Code
//    //
//    //__asm ("      ESTOP0");
//    //for(;;);
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

