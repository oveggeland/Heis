#include "controll.h"
#include "elev.h"
#include "door.h"
#include "logic.h"
#include <stdio.h>
#include <stdlib.h>

void checkForUpdates(){
		
	//Sjekker om noen trykker på stoppsignalet
	if (elev_get_stop_signal()){
		stopSignal();
	}
	
	//Her sjekker vi om heisen har kommet til en etasje
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
}

void controll(){
    initialize();
    
	
	//While-løkken leter etter en hendelse. Mulige hendelser er stopp-knapp, bestillingsknapp og at heisen har ankommet en etasje.
	while(1){
		checkForUpdates();
	}
}