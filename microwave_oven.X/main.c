/*
 * File:   main.c
 * Author: Biancaa.R
 *
 * Created on 22 February, 2025, 1:10 AM
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
//int pre_heat_time;
extern unsigned char min,sec;
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
    init_timer2(void);
    PEIE = 1;
    GIE = 1;
}
void main(void) {
    unsigned char key;
    unsigned char start_mode=0;
    //when start mode is true
    init_config();
    while(1){
        key = read_matrix_keypad(STATE);
        //if(operational_flag==POWER_ON_SCREEN){
        if (operational_flag==MENU_SCREEN){
            
            //selecting the mode based on key press
            if(key==1){
                clear_screen();
                operational_flag=MICRO_MODE;
                start_mode=0;
                clcd_print("Power=900w",LINE2(0));
                __delay_ms(200);
                clear_screen();
            }
            else if (key == 2){
                clear_screen();
                start_mode=0;
                operational_flag = GRILL_MODE;
                reset_flag = RESET_MODE;
               
            }
            else if (key == 3){
                clear_screen();
                start_mode=0;
                operational_flag = CONVENTION_MODE;
                reset_flag=RESET_MODE;
              
            }
            else if(key == 4){
                clear_screen();
                operational_flag=START_MODE;
                start_mode=1;
                reset_flag=RESET_MODE;
            }
        }
        if(operational_flag == DISPLAY_TIME){
            if(key == 4){
                //operational_flag = START;
                //increment cooking time by 30
                if(start_mode){
                   sec=sec+30;
                   if(sec >59){
                       min++;
                       sec=sec-60;
                   }
                }
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
                //clear_screen();
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
                
            case START_MODE:
                //display time
                heat_food();
                break;
            
        }
        reset_flag = RESET_NOTHING;
    }
}

























