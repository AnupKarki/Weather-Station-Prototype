//*****************************************************************************
//
// MSP432 main.c template - Empty main
//
//****************************************************************************

#include "driverlib.h"
#include "msprf24.h"
#include "nrf_userconfig.h"
#include "nRF24L01.h"
#include "Transmission.h"
#include "supportfunctions.h"

#include "utils/cmdline.h"
#include "fatfs/src/ff.h"
#include "fatfs/src/diskio.h"

#include "spiDriver.h"

//#include "rtcInterface.h"

#define CODE 0  //0 for TX, 1 for RX


// Defines the size of the buffers that hold the path, or temporary data from
// the SD card.  There are two buffers allocated of this size.  The buffer size
// must be large enough to hold the longest expected full path name, including
// the file name, and a trailing null character.
#define PATH_BUF_SIZE           80

// Defines the size of the buffer that holds the command line.
#define CMD_BUF_SIZE            64


//char *FILENAME = "logger2.csv";
#define FILENAME  "logdata2.csv"
// This buffer holds the full path to the current working directory.  Initially
// it is root ("/").
static char g_pcCwdBuf[PATH_BUF_SIZE] = "/";

// A temporary data buffer used when manipulating file paths, or reading data
// from the SD card.
static char g_pcTmpBuf[PATH_BUF_SIZE];

// The buffer that holds the command line.
static char g_pcCmdBuf[CMD_BUF_SIZE];

// The following are data structures used by FatFs.
static FATFS g_sFatFs,fts;
static DIR g_sDirObject;
static FILINFO g_sFileInfo;
static FIL g_sFileObject,fil;
static FRESULT iFResult,fresult;


typedef struct {
    FRESULT iFResult;
    char *pcResultStr;
} tFResultString;


/* Time is March 21 2017 9:03:00 PM */
const RTC_C_Calendar currentTime =
{
        00,
        42,
        8,
        3,
        22,
        03,
        2017
};


// A macro to make it easy to add result codes to the table.
#define FRESULT_ENTRY(f)        { (f), (#f) }

// A table that holds a mapping between the numerical FRESULT code and it's
// name as a string.  This is used for looking up error codes for printing to
// the console.
tFResultString g_psFResultStrings[] = {
FRESULT_ENTRY(FR_OK),
FRESULT_ENTRY(FR_DISK_ERR),
FRESULT_ENTRY(FR_INT_ERR),
FRESULT_ENTRY(FR_NOT_READY),
FRESULT_ENTRY(FR_NO_FILE),
FRESULT_ENTRY(FR_NO_PATH),
FRESULT_ENTRY(FR_INVALID_NAME),
FRESULT_ENTRY(FR_DENIED),
FRESULT_ENTRY(FR_EXIST),
FRESULT_ENTRY(FR_INVALID_OBJECT),
FRESULT_ENTRY(FR_WRITE_PROTECTED),
FRESULT_ENTRY(FR_INVALID_DRIVE),
FRESULT_ENTRY(FR_NOT_ENABLED),
FRESULT_ENTRY(FR_NO_FILESYSTEM),
FRESULT_ENTRY(FR_MKFS_ABORTED),
FRESULT_ENTRY(FR_TIMEOUT),
FRESULT_ENTRY(FR_LOCKED),
FRESULT_ENTRY(FR_NOT_ENOUGH_CORE),
FRESULT_ENTRY(FR_TOO_MANY_OPEN_FILES),
FRESULT_ENTRY(FR_INVALID_PARAMETER), };

// A macro that holds the number of result codes.
#define NUM_FRESULT_CODES       (sizeof(g_psFResultStrings) /                 \
                                 sizeof(tFResultString))

uint8_t gucCommandReady = 0;
// This function returns a string representation of an error code that was
// returned from a function call to FatFs.  It can be used for printing human
// readable error messages.
const char *
StringFromFResult(FRESULT iFResult) {
    uint_fast8_t ui8Idx;

    // Enter a loop to search the error code table for a matching error code.
    for (ui8Idx = 0; ui8Idx < NUM_FRESULT_CODES; ui8Idx++) {
        // If a match is found, then return the string name of the error code.
        if (g_psFResultStrings[ui8Idx].iFResult == iFResult) {
            return (g_psFResultStrings[ui8Idx].pcResultStr);
        }
    }

    // At this point no matching code was found, so return a string indicating
    // an unknown error.
    return ("UNKNOWN ERROR CODE");
}

char data[60];
int bw = 0;
int br =0;
int offset = 0;
char myStringToWrite[60];


volatile unsigned int user;
int receiveBytes;
int receiveBuffer[14];
int writeTofileFlag = 0;

int transmitState = 0;
int bufferPosition = 0;
int dateAndTimeRecieved = 0;

char date[15];
char time[10];

static volatile RTC_C_Calendar newTime,myTime,dateAndTimeWrite;

const eUSCI_UART_Config uartConfig =
{
        EUSCI_A_UART_CLOCKSOURCE_SMCLK,          // SMCLK Clock Source
        104,                                      // BRDIV = 26
        0,                                       // UCxBRF = 0
        0,                                       // UCxBRS = 0
        EUSCI_A_UART_NO_PARITY,                  // No Parity
        EUSCI_A_UART_LSB_FIRST,                  // MSB First
        EUSCI_A_UART_ONE_STOP_BIT,               // One stop bit
        EUSCI_A_UART_MODE,                       // UART mode
        EUSCI_A_UART_LOW_FREQUENCY_BAUDRATE_GENERATION  // Low Frequency Mode
};

void initRTC()
{
    MAP_RTC_C_initCalendar(&newTime, RTC_C_FORMAT_BINARY);

    /* Setup Calendar Alarm for 10:04pm (for the flux capacitor) */
    //MAP_RTC_C_setCalendarAlarm(0x04, 0x22, RTC_C_ALARMCONDITION_OFF,
    //        RTC_C_ALARMCONDITION_OFF);

    /* Specify an interrupt to assert every minute */
    MAP_RTC_C_setCalendarEvent(RTC_C_CALENDAREVENT_MINUTECHANGE);
    /* Start RTC Clock */
    MAP_RTC_C_startClock();

}

void writeTofile()
{
    dateAndTimeWrite = MAP_RTC_C_getCalendarTime();
    printf("offset = %d\r\n",offset);
//    offset += (bw);
    sprintf(myStringToWrite,"%d/%d/%d %d:%d:%d, %s \n", dateAndTimeWrite.year,dateAndTimeWrite.month,dateAndTimeWrite.dayOfmonth,dateAndTimeWrite.hours,dateAndTimeWrite.minutes,dateAndTimeWrite.seconds,data);
    printf("\n Checking %s\r\n",myStringToWrite);
    fresult = f_open(&fil,FILENAME,FA_OPEN_ALWAYS|FA_WRITE|FA_READ);
    printf("f_open error: %s\r\n", StringFromFResult(fresult));
    fresult = f_lseek(&fil,offset);
    fresult = f_write(&fil,myStringToWrite,sizeof(myStringToWrite),&bw);
//    while(fresult != FR_OK){
//        printf("f_write error: %s\n", StringFromFResult(fresult));
//        fresult = f_write(&fil,myStringToWrite,sizeof(myStringToWrite),&bw);
//
//    }
    if(fresult == FR_OK){
        offset += (bw);
    }else{
    printf("f_write error: %s\n", StringFromFResult(fresult));
    }
    //printf("%d bytes written\r\n", StringFromFResult(fresult));
    fresult = f_close(&fil);
   // offset += (bw);

}

/*
 * USCIA0 interrupt handler.
 */
void EUSCIA0_IRQHandler(void)
{
    int receiveByte = UCA0RXBUF;

    receiveBytes = receiveByte;

    if(receiveByte == 13){
            transmitState = 1;

    }
    else
    {
        receiveBuffer[bufferPosition] = (receiveByte-48);
        bufferPosition++;
    }


    GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);

    /* Echo back. */
    EUSCI_A_UART_transmitData(EUSCI_A0_BASE, receiveByte);

    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);

}



void convertToDateAndtime()
{
    newTime.year = 0;
    newTime.month = 0;
    newTime.dayOfmonth = 0;
    newTime.hours = 0;
    newTime.minutes = 0;
    newTime.seconds = 0;

    newTime.year += receiveBuffer[0] * 1000;
    newTime.year+= receiveBuffer[1] * 100;
    newTime.year += receiveBuffer[2] * 10;
    newTime.year += receiveBuffer[3];
    newTime.year = (uint_fast8_t)newTime.year;

    newTime.month += receiveBuffer[4] * 10;
    newTime.month += receiveBuffer[5];
    newTime.month = (uint_fast8_t) newTime.month;

    newTime.dayOfmonth += receiveBuffer[6] * 10;
    newTime.dayOfmonth += receiveBuffer[7];
    newTime.dayOfmonth = (uint_fast8_t) newTime.dayOfmonth;

    newTime.hours += receiveBuffer[8] * 10;
    newTime.hours += receiveBuffer[9];
    newTime.hours = (uint_fast8_t) newTime.hours;

    newTime.minutes += receiveBuffer[10] * 10;
    newTime.minutes += receiveBuffer[11];
    newTime.minutes = (uint_fast8_t) newTime.minutes;

    newTime.seconds += receiveBuffer[12] * 10;
    newTime.seconds += receiveBuffer[13];
    newTime.seconds = (uint_fast8_t) newTime.seconds;

  //  newTime.dayOfWeek = 0;
}

/* RTC ISR */
void RTC_C_IRQHandler(void)
{
    uint32_t status;

    status = MAP_RTC_C_getEnabledInterruptStatus();
    MAP_RTC_C_clearInterruptFlag(status);

    if (status & RTC_C_CLOCK_READ_READY_INTERRUPT)
    {
        MAP_GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);
        myTime = MAP_RTC_C_getCalendarTime();
        //writeTofileFlag = 1;
        //displayOnLCD();
    }

    if (status & RTC_C_TIME_EVENT_INTERRUPT)
    {
        /* Interrupts every minute - Set breakpoint here */
        //__no_operation();
        writeTofileFlag = 1;
        //myTime = MAP_RTC_C_getCalendarTime();


    }

    if (status & RTC_C_CLOCK_ALARM_INTERRUPT)
    {
        /* Interrupts at 10:04pm */
        __no_operation();
    }

}

void getAndSetDateAndTime(){
    printf("Enter the date and time in the format yyyymmddhhmmss (e.g 20170214065300) \n");
    while(!transmitState){}
    if (transmitState){
        convertToDateAndtime();
     //   displayOnScreen();
        printf("\n Date and Time Set");

      // transmitState = 0;
       dateAndTimeRecieved = 1;
    }
    if (dateAndTimeRecieved)
    {
        initRTC();
       // dateAndTimeRecieved = 0;

    }

}



#if CODE == 0
void main(void)
{
    //uint8_t addr[5];

    //uint8_t buf[32];
char rx_buff[20];
    WDTCTL = WDTPW | WDTHOLD;           // Stop watchdog timer

    clockInit48MHzXTL();
    MAP_CS_initClockSignal(CS_MCLK, CS_HFXTCLK_SELECT, CS_CLOCK_DIVIDER_2);
    MAP_CS_initClockSignal(CS_SMCLK, CS_HFXTCLK_SELECT, CS_CLOCK_DIVIDER_4);


    MAP_GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN0|GPIO_PIN1);

    /* Configuring SysTick to trigger at 48000 (MCLK is 48 MHz so this will trigger every 1 ms) */
        MAP_SysTick_enableModule();
        MAP_SysTick_setPeriod(24 * 1000 * 1);
        MAP_SysTick_enableInterrupt();  // use a simple interrupt service routine to keep track of time intervals
    //    MAP_Interrupt_enableMaster();

        /* Select Port 6 for I2C - Set Pin 4, 5 to input Primary Module Function,
         *   (UCB1SIMO/UCB1SDA, UCB1SOMI/UCB1SCL).
         */
        MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P6,
                GPIO_PIN4 + GPIO_PIN5, GPIO_PRIMARY_MODULE_FUNCTION);

    user = 0xFE;

    /* Enabling the FPU for floating point operation */
    MAP_FPU_enableModule();
    MAP_FPU_enableLazyStacking();


    /* Select Port 6 for I2C - Set Pin 4, 5 to input Primary Module Function,
     *   (UCB1SIMO/UCB1SDA, UCB1SOMI/UCB1SCL).
     */
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P6,
            GPIO_PIN4 + GPIO_PIN5, GPIO_PRIMARY_MODULE_FUNCTION);

    /* Selecting P1.0 as output (LED). */
       MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1,
           GPIO_PIN0, GPIO_PRIMARY_MODULE_FUNCTION);

       GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
       GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);

       //Configuring 1.1 as push button
      // MAP_GPIO_setAsInputPin(GPIO_PORT_P1, GPIO_PIN1);
       //MAP_GPIO_clearInterruptFlag(GPIO_PORT_P1, GPIO_PIN1);
       //MAP_GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN1);
       //MAP_Interrupt_enableInterrupt(INT_PORT1);



    /* Selecting P1.2 and P1.3 in UART mode. */
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1,
        GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);

    /* Configuring UART Module */
    MAP_UART_initModule(EUSCI_A0_BASE, &uartConfig);

    /* Enable UART module */
    MAP_UART_enableModule(EUSCI_A0_BASE);

    UART_enableInterrupt(EUSCI_A0_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
    Interrupt_enableInterrupt(INT_EUSCIA0);

    /*RTC interrupts*/


    /* Initializing RTC with current time as described in time in
     * definitions section */
    MAP_RTC_C_initCalendar(&currentTime, RTC_C_FORMAT_BINARY);

    /* Setup Calendar Alarm for 10:04pm (for the flux capacitor) */
    //MAP_RTC_C_setCalendarAlarm(0x04, 0x22, RTC_C_ALARMCONDITION_OFF,
    //        RTC_C_ALARMCONDITION_OFF);

    /* Specify an interrupt to assert every minute */
    MAP_RTC_C_setCalendarEvent(RTC_C_CALENDAREVENT_MINUTECHANGE);

    /* Enable interrupt for RTC Ready Status, which asserts when the RTC
      * Calendar registers are ready to read.
      * Also, enable interrupts for the Calendar alarm and Calendar event. */
     MAP_RTC_C_clearInterruptFlag(
             RTC_C_CLOCK_READ_READY_INTERRUPT | RTC_C_TIME_EVENT_INTERRUPT
                     | RTC_C_CLOCK_ALARM_INTERRUPT);
     MAP_RTC_C_enableInterrupt(
             RTC_C_CLOCK_READ_READY_INTERRUPT | RTC_C_TIME_EVENT_INTERRUPT
                     | RTC_C_CLOCK_ALARM_INTERRUPT);

     MAP_RTC_C_startClock();

     spi_Open();

     // Print hello message to user.
    printf("\n\nSD Card Example Program\r\n");
    // printf("Type \'help\' for help.\r\n");

     // Mount the file system, using logical disk 0.
     fresult = f_mount(0, &fts);
     //iFResult = f_mount(&g_sFatFs, "", 0);
     while (fresult != FR_OK) {
         printf("f_mount error: %s\n", StringFromFResult(fresult));
         fresult = f_mount(0, &fts);
     }
     fresult = f_open(&fil,FILENAME,FA_CREATE_ALWAYS|FA_WRITE);

     printf("f_open %s \n",StringFromFResult(fresult));

     //fresult = f_write(&fil,"hello",5,&bw);


     fresult = f_write(&fil,"Date,Temperature,Pressure,Humidity,LightConditions \n",52,&bw);
     offset += bw;

     fresult = f_close(&fil);
     printf("f_close %s \n",StringFromFResult(fresult));
//     writeTofile();


#if 0
     fresult = f_open(&fil,FILENAME,FA_OPEN_ALWAYS|FA_WRITE|FA_READ);
     while (fresult != FR_OK) {
         printf("f_open error: %s\n", StringFromFResult(fresult));
         fresult = f_open(&fil,FILENAME,FA_OPEN_ALWAYS|FA_WRITE);
     }
     printf("open done\r\n");
     fresult = f_write(&fil,"hello123",8,&bw);
     while(fresult != FR_OK){
         fresult = f_write(&fil,"hello",8,&bw);
         printf("f_write error: %s\n", StringFromFResult(fresult));
     }
     printf("%d bytes written!\r\n",bw);
     offset += bw;


          fresult = f_lseek(&fil,0);
          while(fresult != FR_OK){
              printf("f_lseek error: %s\n", StringFromFResult(fresult));
              fresult = f_lseek(&fil,0);
          }
          printf("Flseek done\r\n");

          fresult = f_read(&fil,rx_buff,bw,&br);
          while(fresult != FR_OK){
              printf("f_read error: %s\n", StringFromFResult(fresult));
              fresult = f_read(&fil,rx_buff,bw,&br);
          }
          printf("%d bytes read!\r\n",br);


     fresult = f_close(&fil);
     while(fresult != FR_OK){
         printf("f_close error: %s\n", StringFromFResult(fresult));
         fresult = f_close(&fil);
     }
     printf("Close done\r\n");
#endif
//     fresult = f_open(&fil,FILENAME,FA_CREATE_ALWAYS|FA_WRITE|FA_READ);
//     while (fresult != FR_OK) {
//         printf("f_open error: %s\n", StringFromFResult(fresult));
//         fresult = f_open(&fil,FILENAME,FA_CREATE_ALWAYS|FA_WRITE);
//     }
//     printf("open done again\r\n");
//     fresult = f_lseek(&fil,0);
//     while(fresult != FR_OK){
//         printf("f_lseek error: %s\n", StringFromFResult(fresult));
//         fresult = f_lseek(&fil,0);
//     }
//     printf("Flseek done\r\n");
//     fresult = f_read(&fil,rx_buff,bw,&br);
//     while(fresult != FR_OK){
//         printf("f_read error: %s\n", StringFromFResult(fresult));
//         fresult = f_read(&fil,rx_buff,bw,&br);
//     }
//     printf("%d bytes read!\r\n",br);
//     while(fresult != FR_OK){
//         printf("f_close error: %s\n", StringFromFResult(fresult));
//         fresult = f_close(&fil);
//     }
//     printf("Close done\r\n");



//     /* Enable interrupts and go to sleep. */
     MAP_Interrupt_enableInterrupt(INT_RTC_C);
//
    adcInit();
    bme280Init();
    transmitInit();
 //   float val = 19.23;
//
//
//        /* Enabling MASTER interrupts */
         MAP_Interrupt_enableMaster();
//         //int i;
//
//         printf("Checking float %f",val);
       // getAndSetDateAndTime();
         /* Going to LPM3 */
            while (1)
            {
                getSensorValues(data);
                transmit(data);
                //if(!transmitState)
                //{
                //   getAndSetDateAndTime();
               // }
                if(writeTofileFlag)
                {
                    writeTofile();
                    writeTofileFlag=0;


                }
            }
}


void PORT1_IRQHandler(void)
{
    uint32_t status;
    status = MAP_GPIO_getEnabledInterruptStatus(GPIO_PORT_P1);
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P1, status);
        if (status & GPIO_PIN1){
            printf("\n Button Pressed \n");
            transmitState = 0;
            bufferPosition = 0;
            dateAndTimeRecieved = 0;
            /* Enable UART module */
            //    MAP_UART_enableModule(EUSCI_A0_BASE);

              //  UART_enableInterrupt(EUSCI_A0_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
               // Interrupt_enableInterrupt(INT_EUSCIA0);

        }
}




#elif CODE == 1

void main(void)
{
    uint8_t addr[5];
    uint8_t buf[32];
    char s[16];
    WDTCTL = WDTPW | WDTHOLD;           // Stop watchdog timer

    clockInit48MHzXTL();

    MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_PJ,
                GPIO_PIN0 | GPIO_PIN1, GPIO_PRIMARY_MODULE_FUNCTION);
        MAP_GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);

    MAP_CS_initClockSignal(CS_MCLK, CS_HFXTCLK_SELECT, CS_CLOCK_DIVIDER_1);
    MAP_CS_initClockSignal(CS_SMCLK, CS_HFXTCLK_SELECT, CS_CLOCK_DIVIDER_4);




    MAP_GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN0|GPIO_PIN1);


    /* Selecting P1.2 and P1.3 in UART mode. */
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1,
        GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);


    /* Configuring UART Module */
    MAP_UART_initModule(EUSCI_A0_BASE, &uartConfig);

    /* Enable UART module */
    MAP_UART_enableModule(EUSCI_A0_BASE);

    //UART_enableInterrupt(EUSCI_A0_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
    //Interrupt_enableInterrupt(INT_EUSCIA0);

    receiveInit();

    user = 0xFE;

        /* Enabling MASTER interrupts */
         MAP_Interrupt_enableMaster();

         printf("Receiver Code \n");
         /* Going to LPM3 */
            while (1)
            {
               // w_reg(0,7);
               // check = r_reg(0);
              //  w_reg(1,5);
              //  check1 = r_reg(1);
                receive();

            }

}


#endif
