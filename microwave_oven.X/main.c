/* 
 * File:   main.c
 * Author: Biancaa. R
 *
 * Created on 5 February, 2025, 7:57 PM
 */
//clcd_putch(): print a character
//clcd_print() : to print a string)
#include <stdio.h>
#include <stdlib.h>
unsigned char operational_flag= POWER_ON_SCREEN;
void init_config(void){
    init_clcd();
    init_matrix_keypad();
}
int main() {
    init_config();
    while(1){
        //if(operational_flag==POWER_ON_SCREEN){
        if (operational_flag==MENU_SCREEN){
            key=read_matrix_keypad(STATE);
            //selecting the mode based on key press
            if(key==1){
                clear_screen();
                operational_flag=MICRO_MODE;
                clcd_print("Power=900w",LINE2(0));
                __delay_ms(200);
                clear_screen();
            }
            else if (key==2){
                operational_flag=GRILL_MODE;
            }
            else if (key==3){
                operational_flag=CONVENTIONAL_MODE;
            }
            else if(key==4){
                operational_flag=START_MODE;
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
                break;
            case GRILL_MODE:
                break;
            case CONVENTION_MODE:
                break;
            case SMART_MODE:
                break;
        }
    }
}

