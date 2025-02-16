#include<xc.h>
#include "microwave_oven.h"
#include "clcd.h"
//defining power on function
void power_on_screen(void){
    for(unsigned int i=0;i<16;i++){
        clcd_putch(BAR,LINE1(i));
        //priinting the bars on 15 positions
    }
    clcd_print("Powering ON",LINE2(1));
    clcd_print("Microwave Oven",LINE3(1));
    for(unsigned int i=0;i<16;i++){
        clcd_putch(BAR,LINE4(i));
        //priinting the bars on 15 positions
    }    
}
void clear_screen(void){
    clcd_write(CLEAR_DISP_SCREEN,INST_MODE);
    __delay_ms(500);
}

void display_menu_screen(void){
    clcd_print("1.Micro ",LINE1(0));
    clcd_print("2.Grill",LINE2(0));
    clcd_print("3.Convention",LINE3(0));
    clcd_print("4.Start",LINE4(0));
}

void set_time(unsigned char key){
    clcd_print("SET TIME (MM:SS)",LINE1(0));
    clcd_print("TIME -",LINE2(0));
    clcd_print("*:CLEAR  #:ENTER",LINE4(0));
}