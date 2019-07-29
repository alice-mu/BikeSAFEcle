#include <msp430.h>
#include "driverlib/MSP430FR2xx_4xx/driverlib.h"
#include "stdbool.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "HAL_FR4133LP_LCD.h"
#include "HAL_FR4133LP_Learn_Board.h"

//ultrasonic sensor variables
#define ONE_CM (float)0.1
volatile int time_microsec = 0;
volatile int flag = 0;
volatile float distance_cm = 0;
volatile int i = 0;
volatile uint16_t count;

//keypad variables
volatile int input_threshold[2];
volatile int flag_keypad;
volatile int count_keypad;

int get_digit(){
           GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN1);
           if (GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN1) == GPIO_INPUT_PIN_HIGH){
               count_keypad = 0;
               flag_keypad = 0;
               Timer_A_startCounter(TIMER_A0_BASE, TIMER_A_CONTINUOUS_MODE);
               while (!flag_keypad){
                  count_keypad = Timer_A_getCounterValue(TIMER_A0_BASE);
                  if ((int)count_keypad >= 10)
                      flag_keypad = 1;
               }
               Timer_A_stop(TIMER_A0_BASE);
               Timer_A_clear(TIMER_A0_BASE);

               if (GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN1) == GPIO_INPUT_PIN_HIGH){
                   //confirmed button pressed, wait for button to be released
                   while (GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN1) == GPIO_INPUT_PIN_HIGH){}
                   return 2;
               }
           }

           if (GPIO_getInputPinValue(GPIO_PORT_P2, GPIO_PIN7) == GPIO_INPUT_PIN_HIGH){
               count_keypad = 0;
               flag_keypad = 0;
               Timer_A_startCounter(TIMER_A0_BASE, TIMER_A_CONTINUOUS_MODE);
               while (!flag_keypad){
                  count_keypad = Timer_A_getCounterValue(TIMER_A0_BASE);
                  if ((int)count_keypad >= 10)
                      flag_keypad = 1;
               }
               Timer_A_stop(TIMER_A0_BASE);
               Timer_A_clear(TIMER_A0_BASE);

               if (GPIO_getInputPinValue(GPIO_PORT_P2, GPIO_PIN7) == GPIO_INPUT_PIN_HIGH){
                   while (GPIO_getInputPinValue(GPIO_PORT_P2, GPIO_PIN7) == GPIO_INPUT_PIN_HIGH){}
                   return 0;
               }
           }

           if (GPIO_getInputPinValue(GPIO_PORT_P5, GPIO_PIN1) == GPIO_INPUT_PIN_HIGH){
               count_keypad = 0;
               flag_keypad = 0;
               Timer_A_startCounter(TIMER_A0_BASE, TIMER_A_CONTINUOUS_MODE);
               while (!flag_keypad){
                  count_keypad = Timer_A_getCounterValue(TIMER_A0_BASE);
                  if ((int)count_keypad >= 10)
                      flag_keypad = 1;
               }
               Timer_A_stop(TIMER_A0_BASE);
               Timer_A_clear(TIMER_A0_BASE);

               if (GPIO_getInputPinValue(GPIO_PORT_P5, GPIO_PIN1) == GPIO_INPUT_PIN_HIGH){
                   while (GPIO_getInputPinValue(GPIO_PORT_P5, GPIO_PIN1) == GPIO_INPUT_PIN_HIGH){}
                   return 8;
               }
           }

           if (GPIO_getInputPinValue(GPIO_PORT_P2, GPIO_PIN5) == GPIO_INPUT_PIN_HIGH){
               count_keypad = 0;
               flag_keypad = 0;
               Timer_A_startCounter(TIMER_A0_BASE, TIMER_A_CONTINUOUS_MODE);
               while (!flag_keypad){
                  count_keypad = Timer_A_getCounterValue(TIMER_A0_BASE);
                  if ((int)count_keypad >= 10)
                      flag_keypad = 1;
               }
               Timer_A_stop(TIMER_A0_BASE);
               Timer_A_clear(TIMER_A0_BASE);

               if (GPIO_getInputPinValue(GPIO_PORT_P2, GPIO_PIN5) == GPIO_INPUT_PIN_HIGH){
                   while (GPIO_getInputPinValue(GPIO_PORT_P2, GPIO_PIN5) == GPIO_INPUT_PIN_HIGH){}
                   return 5;
               }
           }

           GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN1);


           GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
           if (GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN1) == GPIO_INPUT_PIN_HIGH){
               count_keypad = 0;
               flag_keypad = 0;
               Timer_A_startCounter(TIMER_A0_BASE, TIMER_A_CONTINUOUS_MODE);
               while (!flag_keypad){
                  count_keypad = Timer_A_getCounterValue(TIMER_A0_BASE);
                  if ((int)count_keypad >= 10)
                      flag_keypad = 1;
               }
               Timer_A_stop(TIMER_A0_BASE);
               Timer_A_clear(TIMER_A0_BASE);

               if (GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN1) == GPIO_INPUT_PIN_HIGH){
                   while (GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN1) == GPIO_INPUT_PIN_HIGH){}
                   return 1;
               }
           }


           if (GPIO_getInputPinValue(GPIO_PORT_P5, GPIO_PIN1) == GPIO_INPUT_PIN_HIGH){
               count_keypad = 0;
               flag_keypad = 0;
               Timer_A_startCounter(TIMER_A0_BASE, TIMER_A_CONTINUOUS_MODE);
               while (!flag_keypad){
                  count_keypad = Timer_A_getCounterValue(TIMER_A0_BASE);
                  if ((int)count_keypad >= 10)
                      flag_keypad = 1;
               }
               Timer_A_stop(TIMER_A0_BASE);
               Timer_A_clear(TIMER_A0_BASE);

               if (GPIO_getInputPinValue(GPIO_PORT_P5, GPIO_PIN1) == GPIO_INPUT_PIN_HIGH){
                   while (GPIO_getInputPinValue(GPIO_PORT_P5, GPIO_PIN1) == GPIO_INPUT_PIN_HIGH){}
                   return 7;
               }
           }

           if (GPIO_getInputPinValue(GPIO_PORT_P2, GPIO_PIN5) == GPIO_INPUT_PIN_HIGH){
               count_keypad = 0;
               flag_keypad = 0;
               Timer_A_startCounter(TIMER_A0_BASE, TIMER_A_CONTINUOUS_MODE);
               while (!flag_keypad){
                  count_keypad = Timer_A_getCounterValue(TIMER_A0_BASE);
                  if ((int)count_keypad >= 10)
                      flag_keypad = 1;
               }
               Timer_A_stop(TIMER_A0_BASE);
               Timer_A_clear(TIMER_A0_BASE);

               if (GPIO_getInputPinValue(GPIO_PORT_P2, GPIO_PIN5) == GPIO_INPUT_PIN_HIGH){
                   while (GPIO_getInputPinValue(GPIO_PORT_P2, GPIO_PIN5) == GPIO_INPUT_PIN_HIGH){}
                   return 4;
               }
           }

           GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);


           GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN0);
           if (GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN1) == GPIO_INPUT_PIN_HIGH){
               count_keypad = 0;
               flag_keypad = 0;
               Timer_A_startCounter(TIMER_A0_BASE, TIMER_A_CONTINUOUS_MODE);
               while (!flag_keypad){
                  count_keypad = Timer_A_getCounterValue(TIMER_A0_BASE);
                  if ((int)count_keypad >= 10)
                      flag_keypad = 1;
               }
               Timer_A_stop(TIMER_A0_BASE);
               Timer_A_clear(TIMER_A0_BASE);

               if (GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN1) == GPIO_INPUT_PIN_HIGH){
                   while (GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN1) == GPIO_INPUT_PIN_HIGH){}
                   return 3;
               }
           }


           if (GPIO_getInputPinValue(GPIO_PORT_P5, GPIO_PIN1) == GPIO_INPUT_PIN_HIGH){
               count_keypad = 0;
               flag_keypad = 0;
               Timer_A_startCounter(TIMER_A0_BASE, TIMER_A_CONTINUOUS_MODE);
               while (!flag_keypad){
                  count_keypad = Timer_A_getCounterValue(TIMER_A0_BASE);
                  if ((int)count_keypad >= 10)
                      flag_keypad = 1;
               }
               Timer_A_stop(TIMER_A0_BASE);
               Timer_A_clear(TIMER_A0_BASE);

               if (GPIO_getInputPinValue(GPIO_PORT_P5, GPIO_PIN1) == GPIO_INPUT_PIN_HIGH){
                   while (GPIO_getInputPinValue(GPIO_PORT_P5, GPIO_PIN1) == GPIO_INPUT_PIN_HIGH){}
                   return 9;
               }
           }

           if (GPIO_getInputPinValue(GPIO_PORT_P2, GPIO_PIN5) == GPIO_INPUT_PIN_HIGH){
               count_keypad = 0;
               flag_keypad = 0;
               Timer_A_startCounter(TIMER_A0_BASE, TIMER_A_CONTINUOUS_MODE);
               while (!flag_keypad){
                  count_keypad = Timer_A_getCounterValue(TIMER_A0_BASE);
                  if ((int)count_keypad >= 10)
                      flag_keypad = 1;
               }
               Timer_A_stop(TIMER_A0_BASE);
               Timer_A_clear(TIMER_A0_BASE);

               if (GPIO_getInputPinValue(GPIO_PORT_P2, GPIO_PIN5) == GPIO_INPUT_PIN_HIGH){
                   while (GPIO_getInputPinValue(GPIO_PORT_P2, GPIO_PIN5) == GPIO_INPUT_PIN_HIGH){}
                   return 6;
               }
           }

           GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN0);

           return -1;
}

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    //not sure what this is for
    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode
                                            // to activate previously configured port settings

    volatile float distance_threshold = 2 * ONE_CM; //trigger at 2 cm
    input_threshold[0] = 0;
    input_threshold[1] = 2;

    //ultrasonic sensor
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN4);
    GPIO_setAsInputPin(GPIO_PORT_P1, GPIO_PIN5);

    //keypad
    GPIO_setAsOutputPin(GPIO_PORT_P8, GPIO_PIN1);
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
    GPIO_setAsOutputPin(GPIO_PORT_P8, GPIO_PIN0);
    GPIO_setAsInputPinWithPullDownResistor(GPIO_PORT_P1, GPIO_PIN1);
    GPIO_setAsInputPinWithPullDownResistor(GPIO_PORT_P2, GPIO_PIN7);
    GPIO_setAsInputPinWithPullDownResistor(GPIO_PORT_P5, GPIO_PIN1);
    GPIO_setAsInputPinWithPullDownResistor(GPIO_PORT_P2, GPIO_PIN5);

    GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN1);
    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
    GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN0);



    Timer_A_initContinuousModeParam param = {0};
    param.clockSource = TIMER_A_CLOCKSOURCE_SMCLK;
    param.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_16;
    param.timerInterruptEnable_TAIE = TIMER_A_TAIE_INTERRUPT_DISABLE;
    param.timerClear = TIMER_A_DO_CLEAR;
    param.startTimer = false;
    Timer_A_initContinuousMode(TIMER_A0_BASE, &param);


    count = 0;
    Init_LCD();

    while(1){
        int check_input = get_digit();

        //if new digit picked up, check for corresponding second one
        if (check_input != -1){
            input_threshold[0] = check_input;
            check_input = get_digit();
            while (check_input == -1){
                check_input = get_digit();
            }
            input_threshold[1] = check_input;

            distance_threshold = (float)(input_threshold[0] * 10 + input_threshold[1]);
            distance_threshold = distance_threshold * ONE_CM;
        }


        //turn trigger on high
        GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN4);
        Timer_A_startCounter(TIMER_A0_BASE, TIMER_A_CONTINUOUS_MODE);

        flag = 0;
        while (!flag){
           count = Timer_A_getCounterValue(TIMER_A0_BASE);
           if ((int)count >= 10)
               flag = 1;
        }

        //turn trigger on low
        GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN4);
        Timer_A_stop(TIMER_A0_BASE);
        Timer_A_clear(TIMER_A0_BASE);

        uint8_t received_echo = GPIO_INPUT_PIN_LOW;
        while (received_echo == GPIO_INPUT_PIN_LOW){
            //poll for start of echo
            received_echo = GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN5);
        }

        Timer_A_startCounter(TIMER_A0_BASE, TIMER_A_CONTINUOUS_MODE);
        while (received_echo == GPIO_INPUT_PIN_HIGH){
            //poll for end of echo
            received_echo = GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN5);
        }

        time_microsec = Timer_A_getCounterValue(TIMER_A0_BASE);
        Timer_A_stop(TIMER_A0_BASE);
        Timer_A_clear(TIMER_A0_BASE);


        // Formula: Distance in cm = (Time in uSec)/58
        distance_cm = (float)(time_microsec)/(float)58;

        LCD_Clear();

        if (distance_cm < (float)distance_threshold){
            LCD_Display_letter(pos1,3);//D
            LCD_Display_letter(pos2,0);//A
            LCD_Display_letter(pos3,13);//N
            LCD_Display_letter(pos4,6);//G
            LCD_Display_letter(pos5,4);//E
            LCD_Display_letter(pos6,17);//R
        }
        else{
            if (input_threshold[0] != 0){
                LCD_Display_digit(pos1, input_threshold[0]);
            }
            LCD_Display_digit(pos2, input_threshold[1]);
            LCD_Display_letter(pos4,2);//C
            LCD_Display_letter(pos5,12);//M
        }

    }
    return 0;
}
