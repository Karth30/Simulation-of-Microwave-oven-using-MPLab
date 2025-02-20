/*
 * File:   main.c
 * Author: Karthayani
 *
 * Created on 19 February, 2025, 10:10 PM
 */
#include<xc.h>
#include "clcd.h"
#include "main.h"
#include "microwave_oven.h"
#include "matrix_keypad.h"
#include "timers.h"

unsigned char sec, min;
extern unsigned char operational_flag;
unsigned char operational_flag = POWER_ON_SCREEN;
unsigned char reset_flag = RESET_NOTHING;
void init_config(void){
    //config CLCD
    init_clcd();
    init_matrix_keypad();
    
    //config FAN
    FAN_DDR = 0;
    FAN = 0;
    //config BUZZER
    BUZZER_DDR = 0;//configure buzzer pin as output
    BUZZER = 0;
    
    //config timer
    init_timer2();
    PEIE = 1;
    GIE = 1;
}
void main(void) {
    unsigned char key;
    init_config();
    while(1){
        key = read_matrix_keypad(STATE);
        //if(operational_flag==POWER_ON_SCREEN){
        if (operational_flag==MENU_SCREEN){
            
            //selecting the mode based on key press
            if(key==1){
                clear_screen();
                operational_flag=MICRO_MODE;
                clcd_print("Power=900w",LINE2(0));
                __delay_ms(200);
                clear_screen();
            }
            else if (key == 2){
                clear_screen();
                operational_flag = GRILL_MODE;
                reset_flag = RESET_MODE;
               
            }
            else if (key == 3){
                clear_screen();
                operational_flag = CONVENTION_MODE;
              
            }
            else if(key == 4){
                operational_flag=START_MODE;
            }
        }
        if(operational_flag == DISPLAY_TIME){
            if(key == 4){
                operational_flag = START;
            }
            else if (key == 5){
                operational_flag = PAUSE;
            }
            else if(key == 6){
                operational_flag = STOP;
            }
        }
        else if(operational_flag == PAUSE){
            //resume microwave oven
            if(key == 4){
                FAN = 1;
                TMR2ON = 1;
                operational_flag = DISPLAY_TIME;
            }
        }
        switch(operational_flag){
            case POWER_ON_SCREEN:
                power_on_screen();
                operational_flag= MENU_SCREEN;
                //display power on screen
                clear_screen();
                break;
            case MENU_SCREEN:
                display_menu_screen();
                break;
            case MICRO_MODE:
                set_time(key,reset_flag);
                break;
            case DISPLAY_TIME :
                time_display();
                break;
            case PAUSE :
                //stop microwave_oven and the timer
                FAN = 0;
                TMR2ON = 0;
                break;
            case STOP :
                FAN = 0;
                TMR2ON = 0;
                min = 0;
                sec = 0;
                clear_screen();
                operational_flag = MENU_SCREEN;
                break;
                
            case GRILL_MODE:
                set_time(key, reset_flag);
                break;
                
            case CONVENTION_MODE:
                //set temperature, set time, display time
                set_temp(key, reset_flag);
                break;
            
        }
        reset_flag = RESET_NOTHING;
    }
}

























