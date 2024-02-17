//
// Included Files
//
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "teste.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

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

#define STACK_SIZE  256U

//static StaticTask_t redTaskBuffer;
//static StackType_t  redTaskStack[STACK_SIZE];

//static StaticTask_t blueTaskBuffer;
//static StackType_t  blueTaskStack[STACK_SIZE];

static StaticTask_t insertionTaskBuffer;
static StackType_t  insertionTaskStack[STACK_SIZE];

static StaticTask_t controlTaskBuffer;
static StackType_t  controlTaskStack[STACK_SIZE];

static StaticTask_t idleTaskBuffer;
static StackType_t  idleTaskStack[STACK_SIZE];

static SemaphoreHandle_t xSemaphore = NULL;
static StaticSemaphore_t xSemaphoreBuffer;

void vApplicationSetupTimerInterrupt( void )
{
    // Start the timer than activate timer interrupt to switch into first task.
    EALLOW;
    PieVectTable.TINT2 = &portTICK_ISR;
    EDIS;

    ConfigCpuTimer(&CpuTimer2,
                   configCPU_CLOCK_HZ / 1000000,  // CPU clock in MHz
                   1000000 / configTICK_RATE_HZ); // Timer period in uS
    CpuTimer2Regs.TCR.all = 0x4000;               // Enable interrupt and start timer
    IER |= M_INT14;
}

//-------------------------------------------------------------------------------------------------
static void blueLedToggle(void)
{
    static uint32_t counter = 0;

    counter++;
    if(counter & 1)
    {
        GpioDataRegs.GPBCLEAR.bit.GPIO39 = 1;
    }
    else
    {
        GpioDataRegs.GPBSET.bit.GPIO39 = 1;
    }
}

//-------------------------------------------------------------------------------------------------
static void redLedToggle(void)
{
    static uint32_t counter = 0;

    counter++;
    if(counter & 1)
    {
        GpioDataRegs.GPBCLEAR.bit.GPIO34 = 1;
    }
    else
    {
        GpioDataRegs.GPBSET.bit.GPIO34 = 1;
    }
}

//-------------------------------------------------------------------------------------------------
interrupt void timer1_ISR( void )
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    xSemaphoreGiveFromISR( xSemaphore, &xHigherPriorityTaskWoken );
    portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
}

//-------------------------------------------------------------------------------------------------
static void setupTimer1( void )
{
    // Start the timer than activate timer interrupt to switch into first task.
    EALLOW;
    PieVectTable.TINT1 = &timer1_ISR;
    EDIS;

    ConfigCpuTimer(&CpuTimer1,
                   configCPU_CLOCK_HZ / 1000000,  // CPU clock in MHz
                   100000);                       // Timer period in uS
    CpuTimer1Regs.TCR.all = 0x4000;               // Enable interrupt and start timer

    IER |= M_INT13;
}

//-------------------------------------------------------------------------------------------------
void insertionTask(void * pvParameters)
{
    static uint32_t period_ms = 500;
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = period_ms / portTICK_PERIOD_MS;
    xLastWakeTime = xTaskGetTickCount();

    int n =10;
    int *insertion_arr = (int *)malloc(n * sizeof(int));
    for(;;)
    {
        insertion_rotine(n, insertion_arr);
        blueLedToggle();
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}

void controlTask(void * pvParameters)
{
    static uint32_t period_ms = 200;
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = period_ms / portTICK_PERIOD_MS;
    xLastWakeTime = xTaskGetTickCount();

    double kp = 1.0;
    double ki = 0.1;
    double kd = 0.01;
    double setpoint = 10.0;
    PIDController pid;

    for(;;)
    {
        PID_routine(&pid_output, &pid, kp, ki, kd, setpoint, adc_buffer_size, DMABuf1, &mean_adc_value);
        redLedToggle();
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}

//-------------------------------------------------------------------------------------------------
//void LED_TaskBlue(void * pvParameters)
//{
//    for(;;)
//    {
//        blueLedToggle();
//        vTaskDelay(500 / portTICK_PERIOD_MS);
//    }
//}

//-------------------------------------------------------------------------------------------------
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
    *ppxIdleTaskTCBBuffer = &idleTaskBuffer;
    *ppxIdleTaskStackBuffer = idleTaskStack;
    *pulIdleTaskStackSize = STACK_SIZE;
}

//-------------------------------------------------------------------------------------------------
void vApplicationStackOverflowHook(TaskHandle_t xTask, signed char *pcTaskName)
{
    while(1);
}

//-------------------------------------------------------------------------------------------------

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
    InitCpuTimers();
    setupTimer1();

//    // point to interrupt function
//    EALLOW;
//    PieVectTable.ADCINT1 = &adc_isr;
//    PieVectTable.DINTCH1= &local_DINTCH1_ISR;
//    EDIS;
    Config_adc(2); //ADCINA2
    Config_dma_4_adc(DMADest, DMASource, DMABuf1, adc_buffer_size);
    Config_GPIO();
    config_interrupts();

//    PIDController pid;

    xTaskCreateStatic(insertionTask,         // Function that implements the task.
                          "Insertion Task",      // Text name for the task.
                          STACK_SIZE,           // Number of indexes in the xStack array.
                          ( void * ) 2,         // Parameter passed into the task.
                          tskIDLE_PRIORITY + 1, // Priority at which the task is created.
                          insertionTaskStack,        // Array to use as the task's stack.
                          &insertionTaskBuffer );    // Variable to hold the task's data structure.

    xTaskCreateStatic(controlTask,         // Function that implements the task.
                              "Control Task",      // Text name for the task.
                              STACK_SIZE,           // Number of indexes in the xStack array.
                              ( void * ) 2,         // Parameter passed into the task.
                              tskIDLE_PRIORITY + 1, // Priority at which the task is created.
                              controlTaskStack,        // Array to use as the task's stack.
                              &controlTaskBuffer );    // Variable to hold the task's data structure.

    vTaskStartScheduler();

    for(;;)
    {
//        adc_value = AdcResult.ADCRESULT0;
//        double kp = 1.0;
//        double ki = 0.1;
//        double kd = 0.01;
//        double setpoint = 10.0;
//        int n =100;
//        int insertion_arr[100];
//
//        // Inicializa o controlador PID
//        PID_routine(&pid_output, &pid, kp, ki, kd, setpoint, adc_buffer_size, DMABuf1, &mean_adc_value);
//        insertion_rotine(n, insertion_arr);
//        GpioDataRegs.GPBTOGGLE.bit.GPIO34 = 1;
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

