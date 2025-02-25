/* ECE319K_Lab4main.c
 * Traffic light FSM
 * ECE319H students must use pointers for next state
 * ECE319K students can use indices or pointers for next state
 * Put your names here or look silly
  */

#include <ti/devices/msp/msp.h>
#include "../inc/LaunchPad.h"
#include "../inc/Clock.h"
#include "../inc/UART.h"
#include "../inc/Timer.h"
#include "../inc/Dump.h"  // student's Lab 3
#include <stdio.h>
#include <string.h>

#define goS 0
#define waitS 1
#define redS 2
#define goWalk 3
#define redOn1 4
#define redOff1 5
#define redOn2 6
#define redOff2 7
#define redWalk 8
#define goW 9
#define waitW 10
#define redW 11
// put both EIDs in the next two lines
const char EID1[] = "CDR3585"; //  ;replace abc123 with your EID carlos
const char EID2[] = "GOO287"; //  ;replace abc123 with your EID grant
// Hint implement Traffic_Out before creating the struct, make struct match your Traffic_Out

struct state {
  uint32_t output;
  uint32_t delay;
  uint8_t Next[8]
};

typedef struct state state_t;

const state_t FSM[12] = {
  {67109121, 3000, {goS, goS, waitS, waitS, waitS, waitS, waitS, waitS}}, // goS / [0]
  {67109122, 1000, {redS, redS, redS, redS, redS, redS, redS, redS}}, // waitS / [1]
  {67109124, 2000, {goS, goS, goW, goW, goWalk, goWalk, goWalk, goWalk}}, // redS / [2]
  {205521156, 3000, {redOn1, redOn1, redOn1, redOn1, redOn1, redOn1, redOn1, redOn1}}, // goWalk / [3]
  {67109124, 2000, {redOff1, redOff1, redOff1, redOff1, redOff1, redOff1, redOff1, redOff1}}, // redOn1 / [4]
  {260, 2000, {redOn2, redOn2, redOn2, redOn2, redOn2, redOn2, redOn2, redOn2}}, // redOff1 / [5]
  {67109124, 2000, {redOff2, redOff2, redOff2, redOff2, redOff2, redOff2, redOff2, redOff2}}, // redOn2 / [5]
  {260, 2000, {redWalk, redWalk, redWalk, redWalk, redWalk, redWalk, redWalk, redWalk}}, // redOff2 / [6]
  {67109124, 2000, {goS, goS, goW, goW, goWalk, goS, goW, goW}}, // redWalk / [7]
  {67108932, 3000, {waitW, waitW, goW, waitW, waitW, waitW, waitW, waitW}}, // goW / [8]
  {67108996, 1000, {redW, redW, redW, redW, redW, redW, redW, redW}}, // waitW / [9]
  {67109124, 2000, {goS, goS, goW, goS, goWalk, goS, goWalk, goS}}; // redW / [10]
};

uint8_t CS = goS;
// initialize all 6 LED outputs and 3 switch inputs
// assumes LaunchPad_Init resets and powers A and B
void Traffic_Init(void){ // assumes LaunchPad_Init resets and powers A and B
  // write this
 
  // South outputs
  // RED - PB2
  IOMUX->SECCFG.PINCM[PB2INDEX] = 0x81;
  GPIOB->DOE31_0 |= 0x04; // PB2 output;
  // YELLOW - PB1
  IOMUX->SECCFG.PINCM[PB1INDEX] = 0x81;
  GPIOB->DOE31_0 |= 0x02; // PB1 output;
  // GREEN - PB
  IOMUX->SECCFG.PINCM[PB3INDEX] = 0x81;
  GPIOB->DOE31_0 |= 0x08; // PB3 output;

  // West outputs
  // RED - PB8
  IOMUX->SECCFG.PINCM[PB8INDEX] = 0x81;
  GPIOB->DOE31_0 |= 0x100; // PB8 output;
  // YELLOW - PB7
  IOMUX->SECCFG.PINCM[PB7INDEX] = 0x81;
  GPIOB->DOE31_0 |= 0x80; // PB7 output;
  // GREEN - PB6
  IOMUX->SECCFG.PINCM[PB6INDEX] = 0x81;
  GPIOB->DOE31_0 |= 0x40; // PB6 output;

  // Walk outputs (set all high for white)
  // RED - PB26
  IOMUX->SECCFG.PINCM[PB26INDEX] = 0x81;
  GPIOB->DOE31_0 |= 0x4000000; // PB26 output;
  // GREEN - PB27
  IOMUX->SECCFG.PINCM[PB27INDEX] = 0x81;
  GPIOB->DOE31_0 |= 0x8000000; // PB27 output;
  // BLUE - PB22
  IOMUX->SECCFG.PINCM[PB22INDEX] = 0x81;
  GPIOB->DOE31_0 |= 0x400000; // PB22 output;
  

  // Inputs
  // West sensor - PB15
  IOMUX->SECCFG.PINCM[PB15INDEX] = 0x40081;
  // South sensor - PB16
  IOMUX->SECCFG.PINCM[PB16INDEX] = 0x40081;
  // Walk sensor - PB17
  IOMUX->SECCFG.PINCM[PB17INDEX] = 0x40081;

}

/* Activate LEDs
* Inputs: west is 3-bit value to three east/west LEDs
*         south is 3-bit value to three north/south LEDs
*         walk is 3-bit value to 3-color positive logic LED on PB22,PB26,PB27
* Output: none
* - west =1 sets west green
* - west =2 sets west yellow
* - west =4 sets west red
* - south =1 sets south green
* - south =2 sets south yellow
* - south =4 sets south red
* - walk=0 to turn off LED
* - walk bit 22 sets blue color
* - walk bit 26 sets red color
* - walk bit 27 sets green color
* Feel free to change this. But, if you change the way it works, change the test programs too
* Be friendly
void Traffic_Out(uint32_t west, uint32_t south, uint32_t walk){

}
*/

void Traffic_Out(uint32_t out){
  GPIOB->DOUT31_0 = (GPIOB->DOUT31_0 & (~0xC4001C7) | out)
}

/* Read sensors
 * Input: none
 * Output: sensor values
 * - bit 0 is west car sensor
 * - bit 1 is south car sensor
 * - bit 2 is walk people sensor
* Feel free to change this. But, if you change the way it works, change the test programs too
 */
uint32_t Traffic_In(void){
    return (GPIOB->DIN31_0 & 0x38000) >> 16; // write this
}
// use main1 to determine Lab4 assignment
void Lab4Grader(int mode);
void Grader_Init(void);
int main(void){ // main1
  Clock_Init80MHz(0);
  LaunchPad_Init();
  Lab4Grader(0); // print assignment, no grading
  while(1){
  }
}
// use main2 to debug LED outputs
// at this point in ECE319K you need to be writing your own test functions
// modify this program so it tests your Traffic_Out  function
int main2(void){ // main2
  Clock_Init80MHz(0);
  LaunchPad_Init();
  Grader_Init(); // execute this line before your code
  LaunchPad_LED1off();
  Traffic_Init(); // your Lab 4 initialization
  if((GPIOB->DOE31_0 & 0x20)==0){
    UART_OutString("access to GPIOB->DOE31_0 should be friendly.\n\r");
  }
  UART_Init();
  UART_OutString("Lab 4, Spring 2025, Step 1. Debug LEDs\n\r");
  UART_OutString("EID1= "); UART_OutString((char*)EID1); UART_OutString("\n\r");
  UART_OutString("EID2= "); UART_OutString((char*)EID2); UART_OutString("\n\r");
  while(1){
    // write code to test your Traffic_Out
    if((GPIOB->DOUT31_0&0x20) == 0){
      UART_OutString("DOUT not friendly\n\r");
    }
  }
}
// use main3 to debug the three input switches
// at this point in ECE319K you need to be writing your own test functions
// modify this program so it tests your Traffic_In  function
int main3(void){ // main3
  uint32_t last=0,now;
  Clock_Init80MHz(0);
  LaunchPad_Init();
  Traffic_Init(); // your Lab 4 initialization
  Debug_Init();   // Lab 3 debugging
  UART_Init();
  __enable_irq(); // UART uses interrupts
  UART_OutString("Lab 4, Spring 2025, Step 2. Debug switches\n\r");
  UART_OutString("EID1= "); UART_OutString((char*)EID1); UART_OutString("\n\r");
  UART_OutString("EID2= "); UART_OutString((char*)EID2); UART_OutString("\n\r");
  while(1){
    now = Traffic_In(); // Your Lab4 input
    if(now != last){ // change
      UART_OutString("Switch= 0x"); UART_OutUHex(now); UART_OutString("\n\r");
      Debug_Dump(now);
    }
    last = now;
    Clock_Delay(800000); // 10ms, to debounce switch
  }
}
// use main4 to debug using your dump
// proving your machine cycles through all states
int main4(void){// main4
uint32_t input;
  Clock_Init80MHz(0);
  LaunchPad_Init();
  LaunchPad_LED1off();
  Traffic_Init(); // your Lab 4 initialization
 // set initial state
  Debug_Init();   // Lab 3 debugging
  UART_Init();
  __enable_irq(); // UART uses interrupts
  UART_OutString("Lab 4, Spring 2025, Step 3. Debug FSM cycle\n\r");
  UART_OutString("EID1= "); UART_OutString((char*)EID1); UART_OutString("\n\r");
  UART_OutString("EID2= "); UART_OutString((char*)EID2); UART_OutString("\n\r");
// initialize your FSM
  SysTick_Init();   // Initialize SysTick for software waits

  while(1){
      // 1) output depending on state using Traffic_Out
      // call your Debug_Dump logging your state number and output
      // 2) wait depending on state
      // 3) hard code this so input always shows all switches pressed
      // 4) next depends on state and input
  }
}
// use main5 to grade
int main5(void){// main5
  Clock_Init80MHz(0);
  LaunchPad_Init();
  Grader_Init(); // execute this line before your code
  LaunchPad_LED1off();
  Traffic_Init(); // your Lab 4 initialization
// initialize your FSM
  SysTick_Init();   // Initialize SysTick for software waits
  // initialize your FSM
  Lab4Grader(0); // activate UART, grader and interrupts
  while(1){
      // 1) output depending on state using Traffic_Out
      Traffic_Out(FSM[CS].output);
      // call your Debug_Dump logging your state number and output
      // 2) wait depending on state
      SysTick_Wait10ms(FSM[CS].delay);
      // 3) input from switches
      uint32_t input = Traffic_In()
      // 4) next depends on state and input
      CS = FSM[CS].Next[input];
  }
}

