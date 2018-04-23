#include "elev.h"

void sm_add_order(elev_button_type_t button, int floor);
void open_door(void);
void sm_arrived_at_floor(int floor);
void sm_timeout();
void sm_stop_button_pressed(void);
void sm_stop_button_released(void);
void sm_check_idle(void);
int sm_requests_below(void);
int sm_requests_above(void);
int sm_set_direction(void);
int sm_check_if_stop(void);
