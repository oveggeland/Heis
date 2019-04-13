#include "elev.h"
#include "controll.h"
#include "order.h"
#include <stdio.h>
#include <stdlib.h>


int main() {
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }
	printf("Press STOP button to stop elevator and exit program.\n");
		/*
    elev_set_motor_direction(DIRN_UP);



    while (1) {
        //Initialize, stop at first floor
        if (elev_get_floor_sensor_signal() == N_FLOORS - 1) {
            elev_set_motor_direction(DIRN_DOWN);
        } else if (elev_get_floor_sensor_signal() == 0) {
            elev_set_motor_direction(DIRN_STOP);
            break;
        }

        // Stop elevator and exit program if the stop button is pressed
        if (elev_get_stop_signal()) {
            elev_set_motor_direction(DIRN_STOP);
            break;
        }
    }*/
    controll();
    return 0;
}
