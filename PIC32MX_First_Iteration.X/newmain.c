/* MAJOR PROJECT */
#pragma config FNOSC = FRCPLL       // Internal Fast RC oscillator (8 MHz) w/ PLL
#pragma config FPLLIDIV = DIV_2     // Divide FRC before PLL (now 4 MHz)
#pragma config FPLLMUL = MUL_20     // PLL Multiply (now 80 MHz)
#pragma config FPLLODIV = DIV_32     // 40MHz System Clock
#pragma	config	FPBDIV	=	DIV_1   //	FPBDIV	is	Peripheral	bus
#pragma config FWDTEN = OFF         // Watchdog Timer Disabled
#pragma config ICESEL = ICS_PGx1    // ICE/ICD Comm Channel Select
#pragma config JTAGEN = OFF       // Disable JTAG
#pragma config FSOSCEN = OFF        // Disable Secondary Oscillator

//#include <p32xxxx.h>
#include <xc.h>
#include <sys/attribs.h>

volatile unsigned int pr2_value = 10000;
volatile unsigned int ISR_RELOAD = 0;
extern void asmFunction();
extern unsigned int asmVariable;
//extern void asmFunction2();
//extern unsigned int asmVariable2;


 void main(void){
    INTCONbits.MVEC=1; //MULTIVECTOR INTERRUPT MODE
    asm("ei"); //ENABLE INTERRUPT
    TRISB = 0;   // Set PORTB as digital output
    TRISA = 1;   // Set PORTA as digital input
    LATB = 0;
    // Setting up Timer 2
    T2CON = 0; //stop timer and clear control 
    T2CONbits.TCKPS = 7; //PRESCALE 256
    PR2 = pr2_value; //COUNTED UP TO      
        
    TMR2 = 0x0; //clear timer2 register
    T2CONbits.TON = 1; // Enable Timer2
    
    //TIMER INTERRUPT
    IFS0CLR=_IFS0_T2IF_MASK; //CLEAR ISR FLASG
    IEC0bits.T2IE = 0;       // INTERRUPT DISABLE 
    IPC2bits.T2IP = 1;       //INTERRUPT PRIORITY 4
    IEC0bits.T2IE = 1;       // INTERRUPT ENABLE 
    while(1); //wait for Interrupt
    }
 
// Timer2 Interrupt Service Routine
void __attribute__( (interrupt(ipl4auto), vector(_TIMER_2_VECTOR))) Timer2Handler (void); void Timer2Handler(void)
{
    int status = 1;
    asmFunction();
       //new file
    if(LATBbits.LATB9 == 1){
        asmFunction();
        asmVariable++;
        status = 2;
    }
    if(LATBbits.LATB8 == 1){
         //asmFunction2();
         //asmVariable2++;
         status = 2;
    }
    //TOGGLE LEDS IN ORDER
    if(ISR_RELOAD == 0 || status == 2){ISR_RELOAD = 0;} //STEP IN?
    else if(ISR_RELOAD == 1){LATBbits.LATB3 = ~LATBbits.LATB3;}                     //RB3
    else if(ISR_RELOAD == 2){LATBbits.LATB2 = ~LATBbits.LATB2;}                     //RB2
    else if(ISR_RELOAD == 3){LATBbits.LATB15 = ~LATBbits.LATB15;}                   //RB15
    else if(ISR_RELOAD == 4){LATBbits.LATB14 = ~LATBbits.LATB14;}                   //RB14
    else if(ISR_RELOAD == 5){LATBbits.LATB10 = ~LATBbits.LATB10;}                   //RB10
    else if(ISR_RELOAD == 6){LATBbits.LATB11 = ~LATBbits.LATB11; ISR_RELOAD = 0;}   //RB11
    ISR_RELOAD = ISR_RELOAD + 1;
    IFS0CLR=_IFS0_T2IF_MASK;
}
