
//____FUNKSJONER FOR PRIORITETSALGORITME____

void qs_reset_orders(); //Nullstiller alle ordre
int qs_check_orders(); //Sjekker om en bestillings-knapp er trykket inn, og behandler denne
void qs_set_priority(); //Setter hva som skal være neste etasje ut i fra nåværende ordre og deres plassering
void qs_delete_orders(); //Sletter ordre i etasjen heisen befinner seg i
int qs_get_above_order(); //Sjekker om det finnes bestillinger over heisen, og setter neste etasje til første gyldige bestilling over
int qs_get_below_order();//Sjekker om det finnes bestillinger under heisen, og setter neste etasje til første gyldige bestilling under
int qs_get_number_of_orders(); //Returnerer totalt antall nåværende bestillinger

//____GET- & SET-FUNKSJONER____

void qs_set_next_floor(int floor);
int qs_get_next_floor();
void qs_set_current_floor(int floor);
int qs_get_current_floor();
void qs_set_current_dir(int direction);
int qs_get_current_dir();
void qs_set_last_dir(int direction);
int qs_get_last_dir();

//____TEST FUNKSJONER____

void print_next_floor();
void print_current_floor();
void print_matrix();