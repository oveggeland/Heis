//Her skal jeg implementere et nytt bestillingsystem
#include "elev.h"
#include "door.h"
#include "logic.h"
#include <stdlib.h>
#include <stdio.h>

//Oversikt over hva som er blitt trykket
int oversikt[N_FLOORS][3] = { 0 };

//Oversikt over staten til vår heis
struct stateHeis* heisenMin;

void initialize() {
	//Skal vi ha med minneallokering???
	heisenMin = (struct stateHeis*) malloc(sizeof(struct stateHeis));
	heisenMin->dir = 0;
	heisenMin->lastFloor = 0;
	heisenMin->targetFloor = -1;
	heisenMin->doorOpen = 0;
	
	setDir(1);
	while (1) {
		if (elev_get_floor_sensor_signal() == N_FLOORS - 1) {
			setDir(-1);
		}
		else if (elev_get_floor_sensor_signal() == 0) {
			setDir(0);
			break;
		}
	}
}

void setDir(int retning) {
	heisenMin->dir = retning;
	elev_set_motor_direction(retning);
}

//Legger inn nye knappetrykk i bestillingsoversikten
void addNewOrder(int retning, int etasje) {
	if (heisenMin->dir == -1) {
		etasje--;
	}
	if (retning != 2) {
		oversikt[etasje][retning+1] = 1;
	}
	else {
		oversikt[etasje][0] = 1;
	}
	elev_set_button_lamp(retning, etasje, 1);
}

//Fjerner bestillinger til etasjen en kommer til
void clearOrdersByFloor(int etasje) {
	if (heisenMin->dir == -1) {
		etasje--;
	}
	for (int i = 0; i < 3; i++) {
		oversikt[etasje][i] = 0;
		clearLightsByFloor(etasje);
	}
}

//Fjerner alle bestillinger, feks ved stoppsignal
void clearAllOrders() {
	for (int i = 0; i < N_FLOORS; i++) {
		for (int j = 0; j < 3; j++) {
			oversikt[i][j] = 0;
		}
		clearLightsByFloor(i);
	}
}

void clearLightsByFloor(int etasje) {
	for (int i = 0; i < 3; i++) {
		elev_set_button_lamp(i, etasje, 0);
	}
}

//Her er det som skjer ved et eventuelt stoppsignal
void stopSignal() {
	elev_set_motor_direction(DIRN_STOP);
	elev_set_stop_lamp(1);
	clearAllOrders();
	if (elev_get_floor_sensor_signal() >= 0) {
		elev_set_door_open_lamp(1);
	}
	holdDoor(3);
	elev_set_door_open_lamp(0);
	elev_set_stop_lamp(0);
	elev_set_motor_direction(1);
}

void floorSensor(int etasje) {
	elev_set_floor_indicator(etasje);
	heisenMin->lastFloor = etasje;

	if (oversikt[etasje][heisenMin->dir]) {
		//Da skal man plukkes opp! :)
		setDir(0);
		openDoor();
		clearOrdersByFloor(etasje);
		setDir(-1);
	}
}