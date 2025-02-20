#include<xc.h>
#include "microwave_oven.h"
#include "clcd.h"
#include "main.h"
#include "timers.h"
#include "matrix_keypad.h"

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
        //printing the bars on 15 positions
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

void set_time(unsigned char key,unsigned char reset_flag){
    static unsigned char blink_pos =0, key_count = 0;
    if(reset_flag == RESET_MODE){
        blink_pos = 0;
        key_count = 0;
        key = ALL_RELEASED;
        min = 0;
        sec = 0;
        reset_flag = RESET_NOTHING;
    }
    clcd_print("SET TIME (MM:SS", LINE1(0));
    clcd_print("TIME -",LINE2(0));
    clcd_print("*:CLEAR  #:ENTER",LINE4(0));
    
    if( key !='*' && key !='#' && key !=ALL_RELEASED){
        key_count ++;
        if(key_count <=2){
            sec =sec * 10 + key;
            blink_pos = 0;
        }
        else if(key_count <=4 ){
            min =min * 10 + key;
            blink_pos = 1;
        }
        
    }
    else if(key == '*'){
        if(blink_pos){
            min = 0;
            key_count = 2;
        }
        else{
            sec = 0;
            key_count = 0;
        }
    }
    else if(key == '#'){
        //the key # is used to start microwave oven with entered time
        
        //turn on the fan
        FAN = 1;
        
        //start down counting time
        TMR2ON = 1 ;
        //switch to display time screen
        operational_flag = DISPLAY_TIME;
        clear_screen();
    }
    //The secs field should blink indicating the field to be changed
    //to convert min and sec into ascii value to display on clcd
    if(blink_pos == 0){//blink sec
        clcd_putch(' ',LINE2(9));
        clcd_putch(' ',LINE2(10));
    }
    else{
        clcd_putch(' ',LINE2(6));
        clcd_putch(' ',LINE2(7))
    }
    for(unsigned char wait = 50; wait--;);
    
    clcd_putch((sec/10 + '0'),LINE2(9));
    clcd_putch((sec%10 + '0'),LINE2(10));
    clcd_putch(':',LINE2(8));
    clcd_putch((min/10 + '0'),LINE2(6));
    clcd_putch( (min%10 + '0'),LINE2(7));
    
}

void time_display(void){
    //displaying time and the options
    clcd_print("TIME = ",LINE1(1));
    clcd_putch((sec/10 + '0'),LINE1(12));
    clcd_putch((sec%10 + '0'),LINE1(13));
    clcd_putch(':',LINE1(11));
    clcd_putch((min/10 + '0'),LINE1(9));
    clcd_putch( (min%10 + '0'),LINE1(10));
    clcd_print("4.START/RESUME",LINE2(1));
    clcd_print("5.PAUSE",LINE2(1));
    clcd_print("6.STOP",LINE2(1));
    
    if(min == 0 && sec == 0){
        clear_screen();
        //display message cooking is completed
        TMR2ON = 0;
        FAN = 0;
        clcd_print("TIME UP!!!",LINE2(4));
        clcd_print("Enjoy your meal",LINE3(0));
        
        
        //indicate with buzzer
        BUZZER = 1;
        __delay_ms(1000);
        BUZZER = 0;
        //switch back to menu screen
        operational_flag = MENU_SCREEN;
        
    }
}
void set_temp(unsigned char key, unsigned char reset_flag)
{
    static unsigned char temp,key_count;
    //read temp, enter temp, hash
    if(reset_flag == RESET_MODE){
        temp = 0;
        key_count = 0;
    }
    clcd_print("SET TEMP <*C>", LINE1(0));
    clcd_print("TEMP -",LINE2(0));
    clcd_print("*:CLEAR  #:ENTER",LINE4(0));
    //matrix_keypad keys 0 to 9 are used to enter temperature
    if( key !='*' && key !='#' && key != ALL_RELEASED){
        if(key_count < 3){
            temp = temp * 10 + key;
            key_count++;
        }
    }
    else if( key == '*')
    {
        temp = 0;
        key_count = 0;
        
    }
    else if(key == '#'){
        if(temp > 180){
            temp = 180;
        }
        clear_screen();
        clcd_print("Pre-Heating ",LINE1(2));
        clcd_print("Time Rem:",LINE3(0));
    }
    //blinking the temp to indicate we are reading temp
    clcd_putch( ' ',LINE2(8));
    clcd_putch( ' ',LINE2(9));
    clcd_putch( ' ',LINE2(10));
    
    for(unsigned char wait = 50; wait--; );
    
    // convert decimal temp into ASCII
    clcd_putch((temp/100 + '0'),LINE2(8));
    clcd_putch( ((temp/10) % 10+ '0'),LINE2(9));
    clcd_putch( (temp/10 + '0'),LINE2(10));
    
}



