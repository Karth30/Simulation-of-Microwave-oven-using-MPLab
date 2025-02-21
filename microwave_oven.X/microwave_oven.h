
#ifndef MICROWAVE_OVEN_H
#define	MICROWAVE_OVEN_H
unsigned int pre_heat_time;
void clear_screen(void);
void power_on_screen(void);
void display_menu_screen(void);
void set_time(unsigned char key, unsigned char reset_flag);
void heat_food(void);
void time_display(void);
void set_temp(unsigned char key, unsigned char reset_flag);

#endif	/* MICROWAVE_OVEN_H */
