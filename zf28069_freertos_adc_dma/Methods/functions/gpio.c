#include "teste.h"
#include "DSP28x_Project.h"

void Config_GPIO() {
//    InitGpio();
    EALLOW;
    GpioCtrlRegs.GPBMUX1.bit.GPIO39 = 0;
    GpioCtrlRegs.GPBDIR.bit.GPIO39 = 1;
    GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0;
    GpioCtrlRegs.GPBDIR.bit.GPIO34 = 1;
    GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 0;
    GpioCtrlRegs.GPADIR.bit.GPIO1 = 1;
    GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 0;
    GpioCtrlRegs.GPADIR.bit.GPIO2 = 1;
    EDIS;
}
