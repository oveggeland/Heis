#include "controll.h"
#include "elev.h"
#include "door.h"
#include "logic.h"
#include <stdio.h>
#include <stdlib.h>

void controll(){
    initialize();
	setDir(1);
    
	while(1){

		if (elev_get_stop_signal()){
		stopSignal();
		}
		int etasje=elev_get_floor_sensor_signal();
		if (etasje>=0){
		floorSensor(etasje);
		}

		//Legger inn nye bestillinger som kommer inn :) 
		for (int etasje = 0; etasje < N_FLOORS; etasje++) {
			for (int knapp = 0; knapp < 3; knapp++) {
				if (elev_get_button_signal(knapp, etasje)) {
					addNewOrder(knapp, etasje);
				}
			}
		}
		


		//Her kjører heisen bare opp og ned:)
		if (etasje == 3) {
			setDir(-1);
		}
		if (etasje == 0) {
			setDir(1);
		}
	}


}
