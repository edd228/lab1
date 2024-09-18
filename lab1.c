#include <msp430.h>

#define RED_LED BIT0    // Assuming P1.0 is connected to the RED LED
#define GREEN_LED BIT6  // Assuming P1.6 is connected to the GREEN LED
#define BUTTON1 BIT1    // Assuming P4.1 is connected to Button S1
#define BUTTON2 BIT3    // Assuming P2.3 is connected to Button S2

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;       // Disable the GPIO power-on default high-impedance mode

    // Configure LED pins as output
    P1DIR |= RED_LED | GREEN_LED;
    P1OUT &= ~(RED_LED | GREEN_LED); // Start with both LEDs off

    // Configure Button S1 pin as input with pull-up resistor
    P4DIR &= ~BUTTON1;
    P4REN |= BUTTON1;
    P4OUT |= BUTTON1;

    // Configure Button S2 pin as input with pull-up resistor
    P2DIR &= ~BUTTON2;
    P2REN |= BUTTON2;
    P2OUT |= BUTTON2;

    while(1)
    {
        if(!(P4IN & BUTTON1))   // Check if button S1 is pressed
        {
            __delay_cycles(100000);  // Debounce delay
            P1OUT ^= RED_LED;        // Toggle RED LED
            while(!(P4IN & BUTTON1)); // Wait until button S1 is released
        }

        if(!(P2IN & BUTTON2))   // Check if button S2 is pressed
        {
            __delay_cycles(100000);  // Debounce delay
            P1OUT ^= GREEN_LED;       // Toggle GREEN LED
            while(!(P2IN & BUTTON2)); // Wait until button S2 is released
        }
    }
}
