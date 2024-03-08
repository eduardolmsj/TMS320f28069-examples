
#include "teste.h"
#include "DSP28x_Project.h"


void config_sci(){
    InitSciGpio();
    scia_fifo_init();
    scia_loopback_init();
}

void
scia_xmit(int a)
{
    SciaRegs.SCITXBUF=a;
}


void scia_loopback_init()
{
    SciaRegs.SCICCR.all =0x0007;

    SciaRegs.SCICTL1.all =0x0003;
    SciaRegs.SCICTL2.all =0x0003;
    SciaRegs.SCICTL2.bit.TXINTENA = 0;
    SciaRegs.SCICTL2.bit.RXBKINTENA = 0;
    SciaRegs.SCIHBAUD    =0x0000;
    SciaRegs.SCILBAUD    =0x000F;
    SciaRegs.SCICCR.bit.LOOPBKENA =1; // Enable loop back
    SciaRegs.SCICTL1.all =0x0023;     // Relinquish SCI from Reset
}

void scia_fifo_init()
{
    SciaRegs.SCIFFTX.all=0xE040;
    SciaRegs.SCIFFRX.all=0x2044;
    SciaRegs.SCIFFCT.all=0x0;
}
