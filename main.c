/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC18F14Q41
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"

volatile uint8_t sw_flag = 0;
uint8_t rgb[3];
uint8_t i;
    
void setcolor(uint8_t *rgb);
void delay_s(uint8_t seconds);

/*
                         Main application
 */
void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global Interrupts
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable high priority global interrupts
    //INTERRUPT_GlobalInterruptHighDisable();

    // Disable low priority global interrupts.
    //INTERRUPT_GlobalInterruptLowDisable();
    SPI1CON0bits.EN = 0;
    SPI1CON1 = 0x40;
    SPI1CLK = 0x06;
    SPI1CON2bits.TXR = 1;
    SPI1CON2bits.RXR = 0;
    
    SPI1CON0bits.MST = 1;
    SPI1CON0bits.BMODE = 1;
    SPI1CON0bits.EN = 1;
    
    RC4PPS = 0x02;  //CLC2
    
    while (1)
    {
        PORTCbits.RC5 = 1;
                
        rgb[0] = 0x20;
        rgb[1] = 0x00;
        rgb[2] = 0x00;
        setcolor(&rgb);
        delay_s(1);
        
        rgb[0] = 0x00;
        rgb[1] = 0x20;
        rgb[2] = 0x00;
        setcolor(&rgb);
        delay_s(1);
        
        rgb[0] = 0x00;
        rgb[1] = 0x00;
        rgb[2] = 0x20;
        setcolor(&rgb);
        delay_s(1);
        
        rgb[0] = 0x20;
        rgb[1] = 0x20;
        rgb[2] = 0x00;
        setcolor(&rgb);
        delay_s(1);
        
        rgb[0] = 0x20;
        rgb[1] = 0x00;
        rgb[2] = 0x20;
        setcolor(&rgb);
        delay_s(1);
        
        rgb[0] = 0x00;
        rgb[1] = 0x20;
        rgb[2] = 0x20;
        setcolor(&rgb);
        delay_s(1);
        
        PORTCbits.RC5 = 0;
        
        // Add your application code        
    }
}

void setcolor(uint8_t *rgb)
{
    uint8_t i;
    for(i=0;i<3;)
    {
        while(PIR3bits.SPI1TXIF == 0){}
        SPI1TXB = rgb[i];
        i++;
    }
}

void delay_s(uint8_t seconds)
{
    uint8_t i;
    for(i=0;i<seconds;i++)
    {
        TMR0_StopTimer();
        PIR3bits.TMR0IF = 0;
        TMR0_StartTimer();
        while(~TMR0_HasOverflowOccured()){}
    }        
}

/**
 End of File
*/