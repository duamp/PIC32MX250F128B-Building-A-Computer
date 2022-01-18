# PIC32MX250F128B-Building-a-computer-

INTRODUCTION
Microcontrollers are small computers with nothing but a CPU, registers and some I/O peripheral
ports which can communicate with the outside world. They are amazing pieces of hardware,
which are useless without a good understanding how to write compliable software. We can
control these amazing pieces of technology by writing a software to communicate in the form of
1s and 0s, I plan to demonstrate this using the PIC32MX250f128b.

CONTEXT:
The goal was to create a project where a PIC32 could communicate with multiple LEDs on a
breadboard all while trying to fulfill the learning outcomes of EECS 2021. First, I wanted to
demonstrate my understanding of assembler by calling upon assembly code. The assembly code
performed basic arithmetic operations on the global variable period register 2 hence controlling
the Interrupt Service Routine. I also wanted to demonstrate my understanding of how to load and
store memory on the chip, an example of this would be in the assembler functions. Information
was passed into the assembler function. This information was then altered and passed back to C
in the main function. The use of assembler is important because it can be more efficient.
Assembler operations can be faster than operations converted from C because C must be
converted to assembler first before operation code. Next, I wanted to stress the difference
between different microcontrollers specifically the atMega328b and the PIC32. To do this I
decided to test the bit manipulation of the GPIO ports on the PIC32 by manipulate pins to work,
invert, set and clear in comparison to the atMega328b in trying to demonstrate the PIC32s
absolute advantage in bit manipulation. This is since the PIC32 can perform bit manipulation in
one operation meanwhile the atMega328b uses bit shifting which takes multiple operations,
signifying a key difference between these two microcontrollers.
TECHNICAL REQUIREMENTS / SPECIFICATIONS
• The Frequency of the peripheral bus should run at 250 MHz.
• An interrupt should be called every second at the start of the project.
• Button 1 decreases frequency by increasing the overflow value by double.
• Button 2 increases frequency by reducing the overflow value by value by half.
• Toggle voltage to MCLR to reset operations to allow for code to reset.
• Access SNAP programmer in accessible way for easy testing and development.
• All LEDs toggle on before they start to toggle off and this process repeats.
Schematic
Figure 1: PIC32MX all minimum connections in addition to LEDs
empty pins signify SNAP connections.
COMPONENTS LIST: [as you built the device]
• Power Supply Module
• Buttons
• 1k resistor
• Breadboard
• LEDs
• SNAP Debugger
• 0.1uF capacitor
• PIC32MX250f128b
• Jumper Wire
• 10k resistor
• 10uF capacitor
Figure 2: Assembled Project
PROCEDURE:
Creating this project started with the idea of replicating a display. When I tried to create this
project, I used methods and tools that we have learned in class such as an Interrupt Service
Routines, Timers, and Assembly Language. I used these tools to toggle the LEDs. The frequency
that the LEDs flashed changed depending on the number of overflows required before an ISR is
called. The timer register is changed by two assembly functions, one of which is called in Figure
3 and executed in Figure 4, this example is the function that increases the number overflows that
must alters the integer in the period register to increase the number of overflows.


 Figure 3: Calling the function Figure 4: Assembler File Figure 5: Compiler version of assembly
Assembler was used instead of C in trying to replicate the strength of writing efficient code using
assembler rather than using the compiler to generate assembler code on its lonesome. Figure 5 is
a representation of how the complier would disassemble the math operations in comparison to
the version in Figure 4. The compiler is very efficient at converting to assembler and in this
instance, it may be more beneficial to use the compiler, but assembler in theory is faster than
writing in C. Next, I created the timer and wanted to create a relatively slower frequency because
I did not require a large frequency for this project and the trade-off in the amount of power was
not worth it. I decided to use a frequency of ~ 1,000 Hz for timer 2. I started the project by
configuring the pragma values for the phase lock loop, as shown in Figure 6. First, I wanted the
output of the input divider to be between 4 – 5 Hz which the PIC32 is designed to use. After this
I tried to get a frequency of around 1,000 Hz, so 1000 overflows would result in an interrupt
every one second, as shown by the calculations to the left of Figure 6.
Fsystem = 8𝑀ℎ𝑧 ×
1
2
× 16 ×
1
64
= 1 𝑀𝐻𝑧
Fperipheral bus = Fsystem ×
1
𝐹𝑃𝐿𝐿𝐷𝐼𝑉 (
1
4
) = 250𝑘𝐻𝑧
FT2 =
𝐹𝑝𝑏𝑢𝑠
𝑇2 𝑝𝑟𝑒𝑠𝑐𝑎𝑙𝑒
=
250 𝑘𝐻𝑧
256
~ = 977 𝐻𝑧 Figure 6: Preoperational parameters
T2 period =
1
977
= 1.024 𝑚𝑠
T2 period = 1.024 ms

The frequency of the system is 250kHz which controls communication, not USB, analog to
digital convertors and the timer. With a frequency of 250kHz and a pre-scale of 256 the
frequency of the timer equals approximately 1 kHz or a period of 1.024 milliseconds. At the start
of the project period register 2 is set to 1000 overflows meaning the ISR will be called after
every second if the user does not press a button.
Next, I wanted to demonstrate my understanding of data in a machine-readable form and
describe how it is manipulated in the CPU, an example of this would be in the assembler
function from Figure 4. Computers only understand 1s and 0s in a binary format. An example of
this is done with period register 2 (pr2_value) as it is created in C equalling 1000decimal or
00000011 11101000binary or 3E8hexadecimal. The binary value (1s and 0s) is understood by the
computer as a high or a low voltage, these voltages are loaded in assembler using the load word
key word, which is then stored in temporary register 1 to later perform a math operation. After
the math operation is invoked, the value is stored in RAM and passed back to the C file.
The GPIO pins are important pins on every microcontroller, and most pins on the PIC32 are
General purpose I/O ports. In this instance, I decided to use Port B bits as output by setting
“TRISB = 0” and bits 7 and 8 (RB7 & RB8 and inputs). I originally set the value of the pins as
low (0) and over time after the ISR is repetitively called they are toggled on and off, using by
changing the value of LATB from 0 to 1 (low to high). This is more efficient for the PIC32 than
the atMega328 because it is done in a single operation. I wanted to use the PIC32 in this instance
because I knew it was faster than the atMega328b which means it has more flexibility in terms of
projects I can do in the future. As I stated before speed is not so much a concern with this project
as humans can only register LEDs flashing so fast, but for future projects such as monitoring
multiple inputs and having outputs such as self-deriving cars, we want the fastest possible
reaction time in terms of clock cycles from a computer.
TEST:
Test 1 (changed RB7 - > RA3 && RB8 -> RA2 for testing purposes):
The input pins were the greatest obstacle. They were difficult to get working because they were
many variables that could have gone wrong. I was unsure if the button, the jumper cables, the
pins, or the software was not working properly. I tested the input registers using the Logic
Analyzer, variables, and IO port tabs to see if the software was operating correctly in MPLABx
as follows.
1. Make sure RA3 voltage equals 0 in I/O pins
2. Check the value of Period Register 2 in Watches Menu
3. Toggle on RA3 in I/O pins menu
4. Should multiple pr2_value by 2 to yield 2000
Figure 8: Testing Simulator to see if problem is software or hardware based
Test 2:
The PIC32 is supposedly more advantageous in this type of project in terms of bit manipulation.
The PIC32 should handle bit manipulation on the GPIO in a single operation unlike the
atMega328b where a bit shift which can take multiple operations, shou. This can be done by
clearing or setting pins. Below is Figure 9 which is a logic analyzer of the atMega328 which
operates with little variation in instruction cycles in comparison to Figure 10, when avoiding
start up time. Unfortunately, I was not able to replicate these results as tried to manipulate each
bit but my experiments did not operate as expected.

Figure 9: atMega328b setting and clearing bits 5 on port B (PB5)
Figure 10: PIC32 setting and clearing bits on PORT B register 5 (RB5)
CONTINGENCY
I had another idea in mind but unfortunately it did not work out because it became too complex
for me to create with the time constraint. My original idea was to create a game using where two
LEDs flashed morse code and a player would have to press a button corresponding to which
LED flash represented a larger number. I really wanted to do this, but I could not figure out how
to create random integers outside of using a library. The concept would have been similar as I
would have to implement an ISR. Now unfortunately this project was created with a lesser
amount of time than I would have liked and looking forward to ENG 4000 I will spend the first
few weeks defining the problem and creating a concrete solution, so I do not waste any further
time being confused or completing unnecessary requirements.
ADDITIONAL MATERIAL
This project is a candidate for exceeding expectations because the learning outcomes were meet
and demonstrated a high level. This project implemented features that were no taught in class
such as changing the period of a timer register during runtime, assembling a PIC32 minimum
connections on a breadboard and by creating a project that represents a small-scale display which
have impacted all our lives in one way or another. I believe being able to change the period of a
timer register during run time is very important because it can save a lot of power. If a computer
can detect instances when the frequency should be low vs high, you can save enormous amounts
of power. For example, we want the software powering self-driving cars to operate at a high
frequency when the car is being driven because safety is the number one priority, but when a car
is idling or in a stand still not moving we do not need a high frequency clock cycle in the
computer which can save energy from the battery.
CONCLUSION
In conclusion this project at the very least should demonstrate the capabilities of working with
microcontrollers. These amazing pieces of hardware when combined with working software can
communicate with the outside world using GPIOs. The PIC32MX250f128b is just one
microcontroller which have improved humans’ lives, these computers have a lot of potential and
are very useful when trying to automate a problem of your own.
