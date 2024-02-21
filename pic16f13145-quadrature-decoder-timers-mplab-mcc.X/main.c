 /*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.0
*/

/*
© [2024] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

#include "mcc_generated_files/system/system.h"

#define RESET_TMR0_TMR1() do{TMR0_Write(0); TMR1_Write(0);}while(0);

void TMR2_Overflow_Handler(void);
int16_t countTicks(void);

volatile bool overflow_flag = false;

int main(void)
{    
    SYSTEM_Initialize();
    
    INTERRUPT_GlobalInterruptEnable(); 
    INTERRUPT_PeripheralInterruptEnable();  
    TMR2_OverflowCallbackRegister(TMR2_Overflow_Handler);
    RESET_TMR0_TMR1();
   
    while(1)
    {
        if(overflow_flag == true)
        {
            printf("%d ticks\r\n", countTicks());
            overflow_flag = false;
        }
    }    
}

void TMR2_Overflow_Handler(void)
{
    overflow_flag = true;
}

int16_t countTicks(void)
{
    uint16_t CW_pulses = 0; 
    uint16_t CCW_pulses = 0;
    int16_t result;
    
    CW_pulses = TMR0_Read();
    CCW_pulses = TMR1_Read();
    result = (int16_t)CW_pulses -  (int16_t)CCW_pulses;  
    RESET_TMR0_TMR1();
    return result;
}