#include <stdint.h>
#include <util/delay.h>
#include <avr/io.h>
#include "OS.h"

   void Task100ms(void);
   void Task10ms(void);
   void Task1Sec(void);
   void Tasks_Init(void);

int main(void){
	Tasks_Init();
	    //creating OS tasks
	    OS_CreateNewTask(Task100ms, 1000);
	    OS_CreateNewTask(Task10ms, 100);
	    OS_CreateNewTask(Task1Sec,10000);
	    //Updat OS
	    while(1) OS_ServeOS();

}
void Tasks_Init(void){
       OS_Init();
       DDRD = 0xFF;
}
void Task100ms(void)
   {


   }

   void Task10ms(void)
   {

   }


   void Task1Sec(void)
   {
	   static uint8_t var = 0;
	   if(var == 0){
		   DDRD = 0x00;
		   var = 1;
	   }else{
		   DDRD = 0xFF;
		   var = 0;
	   }

   }
