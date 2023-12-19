/*
**************************************************************************************************************
*                                                uC/OS-II
*                                          The Real-Time Kernel
*
*
*                                             AVR Sample code
* File        : TEST.C
* Version     : V1.01
**************************************************************************************************************
*/

// A/D Converter Test program

#include "includes.h"
#include "ATmega128_TK.H"
#include <math.h>
volatile char plusPressed = 0;
char code_data_number1 = 0;
char code_data_number2 = 0;
char code_data_number3 = 0;
char code_data_number4 = 0;

static int switch_count = 0;

/*
**************************************************************************************************************
*                                               CONSTANTS
**************************************************************************************************************
*/

#define TASK_STK_SIZE OS_TASK_DEF_STK_SIZE /* Size of each task's stacks (# of bytes)          */
#define N_TASKS 4                              /* Number of identical tasks                        */

#define TASK_START_PRIO 10               /* Application tasks priorities                  */
#define TASK_1_PRIO 11
#define TASK_2_PRIO 12
#define TASK_3_PRIO 13
#define TASK_4_PRIO 14
#define TASK_5_PRIO 15
#define TASK_6_PRIO 16
#define TASK_7_PRIO 17
#define TASK_8_PRIO 18
#define TASK_9_PRIO 19
#define TASK_10_PRIO 20
#define TASK_11_PRIO 21
#define TASK_12_PRIO 22

/*
**************************************************************************************************************
*                                               VARIABLES
**************************************************************************************************************
*/
OS_STK TaskStartStk[TASK_STK_SIZE]; /* Startup    task stack                         */
OS_STK Task1Stk[TASK_STK_SIZE];       /* Task #1    task stack                         */
OS_STK Task2Stk[TASK_STK_SIZE];       /* Task #2    task stack                         */
OS_STK Task3Stk[TASK_STK_SIZE];       /* Task #3    task stack                         */
OS_STK Task4Stk[TASK_STK_SIZE];       /* Task #4    task stack                         */
OS_STK Task5Stk[TASK_STK_SIZE];       /* Task #5    task stack                         */
OS_STK Task6Stk[TASK_STK_SIZE];       /* Task #6    task stack                         */
OS_STK Task7Stk[TASK_STK_SIZE];       /* Task #7    task stack                         */
OS_STK Task8Stk[TASK_STK_SIZE];       /* Task #8    task stack                         */
OS_STK Task9Stk[TASK_STK_SIZE];       /* Task #5    task stack                         */
OS_STK Task10Stk[TASK_STK_SIZE];       /* Task #6    task stack                         */
OS_STK Task11Stk[TASK_STK_SIZE];       /* Task #7    task stack                         */
OS_STK Task12Stk[TASK_STK_SIZE];       /* Task #7    task stack                         */
OS_EVENT *DispSem;
OS_EVENT *Tx1Mbox;
OS_EVENT *Tx2Mbox;
OS_EVENT *Tx3Mbox;
OS_EVENT *Tx4Mbox;
/*
**************************************************************************************************************
*                                           FUNCTION PROTOTYPES
**************************************************************************************************************
*/

void Task1(void *data);       /* Function prototypes of tasks*/
void Task2(void *data);       /* Function prototypes of tasks*/
void Task3(void *data);       /* Function prototypes of tasks*/
void Task4(void *data);       /* Function prototypes of tasks*/
void Task5(void *data);       /* Function prototypes of tasks*/
void Task6(void *data);       /* Function prototypes of tasks*/
void Task7(void *data);       /* Function prototypes of tasks*/
void Task8(void *data);       /* Function prototypes of tasks*/
void Task9(void *data);       /* Function prototypes of tasks*/
void Task10(void *data);       /* Function prototypes of tasks*/
void Task11(void *data);       /* Function prototypes of tasks*/
void Task12(void *data);       /* Function prototypes of tasks*/
void TaskStart(void *data); /* Function prototypes of Startup task              */

/*
**************************************************************************************************************
*                                                MAIN
**************************************************************************************************************
*/

int main(void)
{
    MCU_init();

    Delay_ms(300);

    LCD_initialize();

    LCD_string(0x80, "  ON Calculator ");
    LCD_string(0xC0, "                ");

    OSInit();

    Tx1Mbox = OSMboxCreate((void *)0);
    Tx2Mbox = OSMboxCreate((void *)0);
    Tx3Mbox = OSMboxCreate((void *)0);
    Tx4Mbox = OSMboxCreate((void *)0);
    KeyInit();

    OSTaskCreate(TaskStart, (void *)0, (void *)&TaskStartStk[TASK_STK_SIZE - 1], 0);

    OSStart(); /* Start multitasking                               */
    return 0;
}

/*
**************************************************************************************************************
*                                              STARTUP TASK
**************************************************************************************************************
*/

void TaskStart(void *data)
{
    data = data; /* Prevent compiler warning                         */

    OS_ENTER_CRITICAL();

    TCCR1B = 0x05;
    TIMSK = _BV(TOIE1);

    TCNT1H = ((65536 - (CPU_CLOCK_HZ / OS_TICKS_PER_SEC / 1024)) >> 8);
    TCNT1L = ((65536 - (CPU_CLOCK_HZ / OS_TICKS_PER_SEC / 1024)) & 0xFF);

    OS_EXIT_CRITICAL();

    OSStatInit(); /* Initialize uC/OS-II's statistics */

    DispSem = OSSemCreate(1); /* Display semaphore */


    OSTaskCreate(Task1, (void *)0, (void *)&Task1Stk[TASK_STK_SIZE - 1], TASK_1_PRIO);
    OSTaskCreate(Task2, (void *)0, (void *)&Task2Stk[TASK_STK_SIZE - 1], TASK_2_PRIO);
    OSTaskCreate(Task3, (void *)0, (void *)&Task3Stk[TASK_STK_SIZE - 1], TASK_3_PRIO);
    OSTaskCreate(Task4, (void *)0, (void *)&Task4Stk[TASK_STK_SIZE - 1], TASK_4_PRIO);
    OSTaskCreate(Task5, (void *)0, (void *)&Task5Stk[TASK_STK_SIZE - 1], TASK_5_PRIO);
    OSTaskCreate(Task6, (void *)0, (void *)&Task6Stk[TASK_STK_SIZE - 1], TASK_6_PRIO);
    OSTaskCreate(Task7, (void *)0, (void *)&Task7Stk[TASK_STK_SIZE - 1], TASK_7_PRIO);
    OSTaskCreate(Task8, (void *)0, (void *)&Task8Stk[TASK_STK_SIZE - 1], TASK_8_PRIO);
    OSTaskCreate(Task9, (void *)0, (void *)&Task9Stk[TASK_STK_SIZE - 1], TASK_9_PRIO);
    OSTaskCreate(Task10, (void *)0, (void *)&Task10Stk[TASK_STK_SIZE - 1], TASK_10_PRIO);
    OSTaskCreate(Task11, (void *)0, (void *)&Task11Stk[TASK_STK_SIZE - 1], TASK_11_PRIO);
    OSTaskCreate(Task12, (void *)0, (void *)&Task12Stk[TASK_STK_SIZE - 1], TASK_12_PRIO);
    for (;;)
    {
        OSCtxSwCtr = 0;
        OSTimeDlyHMSM(0, 0, 1, 0); /* Wait one second */
    }
}

/*
**************************************************************************************************************
*                                                  TASKS
**************************************************************************************************************
*/

void Task1(void *data)
{

   INT8U err;
   INT8U code;
   int First_number;
   int Second_number;
   int switchState = 0;
   int Number;
   int Number1;
   data = data;

    for (;;)
    {
        if ((PINB & (1 << PB2)) == 0) {
            switchState = 2; // 슬라이드 스위치 2번 상태
        } else if ((PINB & (1 << PB3)) == 0) {
            switchState = 3; // 슬라이드 스위치 3번 상태
        } 
		  else if ((PINB & (1 << PB4)) == 0) {
		  	switchState = 4;  // 슬라이드 스위치 4번 상태
		}
	  	  else {
            switchState = 0; // 슬라이드 스위치 미작동 상태
        }
///////////////////////////////////////////////////////////////////////////////////////////////
if (switchState == 2) 
{
        PORTC = 0b10000000;
        code = KeyInput();
        LCD_string(0x80, "Mode1 Calculator");
        if (code != 0xff)
        {
            switch_count++;
            switch (switch_count)
            {
            case 0:
                OSSemPend(DispSem, 0, &err);
                LCD_command(0xc0);
                LCD_2d(0);
                OSSemPost(DispSem);
                break;
            case 1:
                code_data_number1 = code;
                OSSemPend(DispSem, 0, &err);
                LCD_command(0xc0);
                LCD_1d(code_data_number1);
                OSSemPost(DispSem);
                break;
            case 2:
                code_data_number2 = code;
                OSSemPend(DispSem, 0, &err);
                LCD_command(0xc0 + 1);
                LCD_1d(code_data_number2);
                OSSemPost(DispSem);
                break;
            case 3:
                code_data_number3 = code;
                OSSemPend(DispSem, 0, &err);
                LCD_command(0xc0 + 5);
                LCD_1d(code_data_number3);
                OSSemPost(DispSem);
                break;
            case 4:
                code_data_number4 = code;
                OSSemPend(DispSem, 0, &err);
                LCD_command(0xc0 + 6);
                LCD_1d(code_data_number4);
                OSSemPost(DispSem);
                break;
            default:
                break;
            }
        }

        if (code == 11)
        {
            OSSemPend(DispSem, 0, &err);
            LCD_command(0x01);
            Delay_ms(500);
            LCD_string(0x80, "Mode1 Calculator");
            LCD_string(0xC0, "                ");
            OSSemPost(DispSem);
         switch_count = 0;
        }

        if (code == 12)
        {
            plusPressed = 1;

            // Task1에서 "+" 및 "=" 표시
            OSSemPend(DispSem, 0, &err);
            LCD_string(0xc0 + 3, "+");
            LCD_string(0xc0 + 8, "=");
            OSSemPost(DispSem);
        }
        if (code == 13)
        {
            plusPressed = 2;
            OSSemPend(DispSem, 0, &err);
            LCD_string(0xc0 + 3, "-");
            LCD_string(0xc0 + 8, "=");
            OSSemPost(DispSem);
        }
        if (code == 14)
        {
            plusPressed = 3;
            OSSemPend(DispSem, 0, &err);
            LCD_string(0xc0 + 3, "x");
            LCD_string(0xc0 + 8, "=");
            OSSemPost(DispSem);
        }
        if (code == 15)
        {
            plusPressed = 4;
            OSSemPend(DispSem, 0, &err);
            LCD_string(0xc0 + 3, "/");
            LCD_string(0xc0 + 8, "=");
            OSSemPost(DispSem);
        }     
        First_number = code_data_number1 * 10 + code_data_number2;
        Second_number = code_data_number3 * 10 + code_data_number4;
        OSMboxPost(Tx1Mbox, (void *)&First_number);
        OSMboxPost(Tx2Mbox, (void *)&Second_number);
        OSTimeDlyHMSM(0, 0, 0, 200);
}

//////////////////////////////////////////////////////////////////////////////////////////
else if (switchState == 3)
{
         PORTC = 0b10100000;
         LCD_string(0x80, "Mode2 Calculator");
         code = KeyInput();
         if (code != 0xff)
             {
          		  switch_count++;
        	      switch (switch_count)
             {
            case 0:
                OSSemPend(DispSem, 0, &err);
                LCD_command(0xc0);
                LCD_1d(0);
                OSSemPost(DispSem);
                break;
            case 1:
                code_data_number1 = code;
                OSSemPend(DispSem, 0, &err);
                LCD_command(0xc0 + 5);
                LCD_1d(code_data_number1);
                OSSemPost(DispSem);
                break;
            case 2:
                code_data_number2 = code;
                OSSemPend(DispSem, 0, &err);
                LCD_command(0xc0 + 6);
                LCD_1d(code_data_number2);
                OSSemPost(DispSem);
                break;
            default:
                break;
             }
             }

        if (code == 11)
        {
            OSSemPend(DispSem, 0, &err);
            LCD_command(0x01);
            Delay_ms(500);
            LCD_string(0x80, "Mode1 Calculator");
            LCD_string(0xC0, "                ");
            OSSemPost(DispSem);
            switch_count = 0;
        }

        if (code == 12)
        {
            plusPressed = 1;
            OSSemPend(DispSem, 0, &err);
            LCD_string(0xc0, "Sin");
            LCD_string(0xc0 + 8, "=");
            OSSemPost(DispSem);
        }
        if (code == 13)
        {
            plusPressed = 2;
            OSSemPend(DispSem, 0, &err);
            LCD_string(0xc0, "Cos");
            LCD_string(0xc0 + 8, "=");
            OSSemPost(DispSem);'
        }
        if (code == 14)
        {
            plusPressed = 3;
            OSSemPend(DispSem, 0, &err);
            LCD_string(0xc0, "Tan");
            LCD_string(0xc0 + 8, "=");
            OSSemPost(DispSem);
        }
        Number = code_data_number1 * 10 + code_data_number2;
        OSMboxPost(Tx3Mbox, (void *)&Number);
        OSTimeDlyHMSM(0, 0, 0, 200);
}
   
/////////////////////////////////////////////////////////////////////////////////////////////////
else if (switchState == 4)
{
     PORTC = 0b10101000;
     LCD_string(0x80, "Mode3 Calculator");
     code = KeyInput();
     if (code != 0xff)
         {
            switch_count++;
            switch (switch_count)
         {
            case 0:
                OSSemPend(DispSem, 0, &err);
                LCD_command(0xc0);
                LCD_1d(0);
                OSSemPost(DispSem);
                break;
            case 1:
                code_data_number1 = code;
                OSSemPend(DispSem, 0, &err);
                LCD_command(0xc0+4);
                LCD_1d(code_data_number1);
                OSSemPost(DispSem);
                break;
            case 2:
                code_data_number2 = code;
                OSSemPend(DispSem, 0, &err);
                LCD_command(0xc0 + 5);
                LCD_1d(code_data_number2);
                OSSemPost(DispSem);
                break;
            case 3:
                code_data_number3 = code;
                OSSemPend(DispSem, 0, &err);
                LCD_command(0xc0 + 6);
                LCD_1d(code_data_number3);
                OSSemPost(DispSem);
                break;
            default:
                break;
          }
          }

        if (code == 11)
        {
            OSSemPend(DispSem, 0, &err);
            LCD_command(0x01);
            Delay_ms(500);
            LCD_string(0x80, "Mode1 Calculator");
            LCD_string(0xC0, "                ");
            OSSemPost(DispSem);
            switch_count = 0;
        }

        if (code == 12)
        {
            plusPressed = 1;
            OSSemPend(DispSem, 0, &err);
            LCD_string(0xc0, "^2");
            LCD_string(0xc0 + 7, "=");
            OSSemPost(DispSem);
        }
        if (code == 13)
        {
            plusPressed = 2;
            OSSemPend(DispSem, 0, &err);
            LCD_string(0xc0, "root");
            LCD_string(0xc0 + 9, "=");
            OSSemPost(DispSem);
        }
        if (code == 14)
        {
            plusPressed = 3;
            OSSemPend(DispSem, 0, &err);
            LCD_string(0xc0, "ln");
            LCD_string(0xc0 + 9, "=");
            OSSemPost(DispSem);
        }
        if (code == 15)
        {
            plusPressed = 4;
            OSSemPend(DispSem, 0, &err);
            LCD_string(0xc0, "log");
            LCD_string(0xc0 + 9, "=");
            OSSemPost(DispSem);
        }

        Number1 = code_data_number1 * 100 + code_data_number2 *10 + code_data_number3;
        OSMboxPost(Tx4Mbox, (void *)&Number1);


        OSTimeDlyHMSM(0, 0, 0, 200);
}

//////////////////////////////////////////////////////////////////////////////////////
else if(switchState == 0)
{
      code = KeyInput();
      PORTC = 0b00000000;
		
        if (code == 11)
        {
            OSSemPend(DispSem, 0, &err);
            LCD_command(0x01);
            Delay_ms(500);
            LCD_string(0x80, "  ON Calculator ");
            LCD_string(0xC0, "                ");
            OSSemPost(DispSem);
         switch_count = 0;
        }
}
}
}
///////////////////////////////////////////////////////// TASK 2 /////////////////////////////////////////////////////////////////////

void Task2(void *data)
{
    char *Fn; //Fn = First number의 약자 Task1에서 메일박스로 보낸 값을 받아 저장하는 변수 
    char *Sn; //Sn = Second number의 약자 Task1에서 메일박스로 보낸 값을 받아 저장하는 변수
    int sum_result;
    INT8U err;
    data = data;

    for (;;)
    {
        if (plusPressed == 1)
        {
            Fn = (char *)OSMboxPend(Tx1Mbox, 0, &err);
            Sn = (char *)OSMboxPend(Tx2Mbox, 0, &err);
            sum_result = *Fn + *Sn;

            OSSemPend(DispSem, 0, &err);
            LCD_command(0xc0 + 12);
            LCD_4d(sum_result);
            OSSemPost(DispSem);

            plusPressed = 0;
        }

        OSTimeDlyHMSM(0, 0, 0, 500);
    }
}
void Task3(void *data)
{
    char *Fn;
    char *Sn;
    char sub_result;
    INT8U err;
    data = data;

    for (;;)
    {
        if (plusPressed == 2)
        {
            Fn = (char *)OSMboxPend(Tx1Mbox, 0, &err);
            Sn = (char *)OSMboxPend(Tx2Mbox, 0, &err);
            sub_result = *Fn - *Sn;

            OSSemPend(DispSem, 0, &err);
            LCD_command(0xc0 + 10);
            LCD_s4d(sub_result);
            OSSemPost(DispSem);

            plusPressed = 0;
        }

        OSTimeDlyHMSM(0, 0, 0, 500);
    }
}
void Task4(void *data)
{
    char *Fn;
    char *Sn;
    int mul_result;
    INT8U err;
    data = data;

    for (;;)
    {
        if (plusPressed == 3)
        {
            Fn = (char *)OSMboxPend(Tx1Mbox, 0, &err);
            Sn = (char *)OSMboxPend(Tx2Mbox, 0, &err);
            mul_result = *Fn * *Sn;

            OSSemPend(DispSem, 0, &err);
            LCD_command(0xc0 + 10);
            LCD_4d(mul_result);
            OSSemPost(DispSem);

            plusPressed = 0;
        }

        OSTimeDlyHMSM(0, 0, 0, 500);
    }
}
void Task5(void *data)
{
    char *Fn;
    char *Sn;
    float div_result;
    INT8U err;
    data = data;

    for (;;)
    {
        if (plusPressed == 4)
        {
            Fn = (char *)OSMboxPend(Tx1Mbox, 0, &err);
            Sn = (char *)OSMboxPend(Tx2Mbox, 0, &err);
            div_result = (float)*Fn / *Sn;

            OSSemPend(DispSem, 0, &err);
            LCD_command(0xc0 + 10);
            LCD_4f2(div_result);
            OSSemPost(DispSem);

            plusPressed = 0;
        }

        OSTimeDlyHMSM(0, 0, 0, 500);
    }
}
void Task6(void *data)
{
    int *Number; // Change this to an int variable
    float sin_result;
    INT8U err;
    data = data;

    for (;;)
    {
        if (plusPressed == 1) // Assuming plusPressed value for sin function is 1
        {
            Number = (int *)OSMboxPend(Tx3Mbox, 0, &err);
            sin_result = (float)sin(*Number * M_PI / 180); // Convert degrees to radians for sin function
            OSSemPend(DispSem, 0, &err);
            LCD_command(0xc0 + 10);
            LCD_s4f2(sin_result);
            OSSemPost(DispSem);

            plusPressed = 0;
        }

        OSTimeDlyHMSM(0, 0, 0, 500);
    }
}

void Task7(void *data)
{
    int *Number; // Change this to an int variable
    float cos_result;
    INT8U err;
    data = data;

    for (;;)
    {
        if (plusPressed == 2) // Assuming plusPressed value for cos function is 2
        {
            Number = (int *)OSMboxPend(Tx3Mbox, 0, &err);
            cos_result = (float)cos(*Number * M_PI / 180); // Convert degrees to radians for cos function
            OSSemPend(DispSem, 0, &err);
            LCD_command(0xc0 + 10);
            LCD_s4f2(cos_result);
            OSSemPost(DispSem);

            plusPressed = 0;
        }

        OSTimeDlyHMSM(0, 0, 0, 500);
    }
}

void Task8(void *data)
{
    int *Number; // Change this to an int variable
    float tan_result;
    INT8U err;
    data = data;

    for (;;)
    {
        if (plusPressed == 3) // Assuming plusPressed value for tan function is 3
        {
            Number = (int *)OSMboxPend(Tx3Mbox, 0, &err);
            tan_result = (float)tan(*Number * M_PI / 180); // Convert degrees to radians for tan function
            OSSemPend(DispSem, 0, &err);
            LCD_command(0xc0 + 10);
            LCD_s4f2(tan_result);
            OSSemPost(DispSem);

            plusPressed = 0;
        }
        OSTimeDlyHMSM(0, 0, 0, 500);
    }
}
void Task9(void *data)
{
    int *Number1;
    long squ_result;
    INT8U err;
    data = data;

    for (;;)
    {
        if (plusPressed == 1)
        {
            Number1 = (int *)OSMboxPend(Tx4Mbox, 0, &err);
            squ_result = *Number1 * *Number1;
            OSSemPend(DispSem, 0, &err);
            LCD_command(0xc0 + 9);
            LCD_6d(squ_result);
            OSSemPost(DispSem);

            plusPressed = 0;
        }

        OSTimeDlyHMSM(0, 0, 0, 500);
    }
}
void Task10(void *data)
{
    int *Number1;
    float sqrt_result;
    INT8U err;
    data = data;

    for (;;)
    {
        if (plusPressed == 2)
        {
            Number1 = (int *)OSMboxPend(Tx4Mbox, 0, &err);
            sqrt_result = (float)sqrt(*Number1);
            OSSemPend(DispSem, 0, &err);
            LCD_command(0xc0 + 10);
            LCD_4f2(sqrt_result);
            OSSemPost(DispSem);

            plusPressed = 0;
        }

        OSTimeDlyHMSM(0, 0, 0, 500);
    }
}
void Task11(void *data)
{
    int *Number1;
    float ln_result;
    INT8U err;
    data = data;

    for (;;)
    {
        if (plusPressed == 3)
        {
            Number1 = (int *)OSMboxPend(Tx4Mbox, 0, &err);
            ln_result = (float)log(*Number1);
            OSSemPend(DispSem, 0, &err);
            LCD_command(0xc0 + 10);
            LCD_4f2(ln_result);
            OSSemPost(DispSem);

            plusPressed = 0;
        }

        OSTimeDlyHMSM(0, 0, 0, 500);
    }
}
void Task12(void *data)
{
    int *Number1;
    float log10_result;
    INT8U err;
    data = data;

    for (;;)
    {
        if (plusPressed == 4)
        {
            Number1 = (int *)OSMboxPend(Tx4Mbox, 0, &err);
            log10_result = (float)log10(*Number1);
            OSSemPend(DispSem, 0, &err);
            LCD_command(0xc0 + 10);
            LCD_4f2(log10_result);
            OSSemPost(DispSem);

            plusPressed = 0;
        }

        OSTimeDlyHMSM(0, 0, 0, 500);
    }
}
