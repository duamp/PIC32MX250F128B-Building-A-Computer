/*
** file: ex1.S
*/
#include <xc.h>
 /* define which section (for example "text")
 * does this portion of code resides in. Typically,
 * all your code will reside in .text section as
 * shown below.
 */
 .text
 /* This is important for an assembly programmer. This
 * directive tells the assembler that don't optimize
 * the order of the instructions as well as don't insert
 * 'nop' instructions after jumps and branches.
 */
 .set noreorder
/*********************************************************************
* asmFunction(int bits)
* This function clears the specified bites in IOPORT A.
********************************************************************/
.global asmFunction
.ent asmFunction //entry
asmFunction:
 /* function prologue - save registers used in this function
  * on stack and adjust stack-pointer
 */

/* store values */
lw t1, pr2_value
addiu t2, zero, 2 //value 5 in register t3

/* arthmetic */
multu t1, t2

mfhi t3 //Move From HI
mflo t4 // Move From LO (special register, stores least significant bit) 
 
/* return to caller */
la s0, pr2_value 
sw t4, 0(s0)

jr ra //return to jump address
nop //no operation
 
.end asmFunction //end of assembler function
 
 .bss
 .global asmVariable
 .align 2
asmVariable: .space 4