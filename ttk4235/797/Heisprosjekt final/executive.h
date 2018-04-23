static int currentDir = 0; //Lagrer den retningen heisen kjører eller sist kjørte hvis heisen står i ro i en etasje.
static int lastFloor = 0; //Lagrer siste passerte etasje.
static int stopButtonPressed = 0; //Lagrer en verdi basert på om stoppknappen er trykket mellom to etasjer.
static int doorOpen = 0; //Lagrer om døren er åpen eller ei.

void initialize(void);
double set_timer(void);
int compare_timer(double comparedTime);
void set_light(void);
void from_index_to_button_and_floor(int index, elev_button_type_t *buttonType, int *floor);
void set_floor_lamp(void);
void destination_reached(void);
void stop(void);
int order_over(void);
int order_under(void);
int stop_or_not(void);
void set_direction(void);
void last_floor(void);
void set_motor_direction(void);