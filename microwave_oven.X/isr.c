/*
 * File:   isr.c
 * Author: Karthayani
 *
 * Created on 19 February, 2025, 10:43 PM
 */


#include <xc.h>
extern unsigned char sec, min;
extern unsigned int pre_heat_time;
unsigned int count;
void __interrupt() isr(void){
    if(TMR2IF){
        if(++count == 20000)//250, 200ns 8 bit timer for 1 sec
        {
            count = 0;
            //for every one sec, decrement sec
            if(sec !=0){
                sec--;
            }
            else if(sec ==0 && min != 0){
                min = 0;
                sec = 60;
            }
            //if sec is 0, decrement min
            else if(pre_heat_time!=0){
                pre_heat_time--;
                //down clocking 
            }
            
        }
        TMR2IF = 0;//clear interrupt flag
    }
}