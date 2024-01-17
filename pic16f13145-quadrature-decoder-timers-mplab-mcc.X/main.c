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

void countTicks(uint16_t CW_ticks, uint16_t CCW_ticks);

int main(void)
{   
    uint16_t CW_pulses = 0; 
    uint16_t CCW_pulses = 0;
    
    SYSTEM_Initialize();
    
    TMR0_Write(0);
    TMR1_Write(0);
    
    while(1)
    {
        CW_pulses = TMR0_Read();
        CCW_pulses = TMR1_Read();
            
        countTicks(CW_pulses, CCW_pulses);
    }    
}

void countTicks(uint16_t CW_ticks, uint16_t CCW_ticks)
{
    static int16_t value;
    static int16_t old_value;
    
    old_value = value; 
    value = (int16_t)CW_ticks -  (int16_t)CCW_ticks;
    
    if(value != old_value)
    {
        if(value > 0)
        {
            printf("%d CW ticks\r\n", value);
        }
        else if(value < 0)
        {
            printf("%d CCW ticks\r\n", -value);
        }
        else
        {
            printf("%d ticks\r\n", value);
        }
    }
}