//Her skal jeg implementere et nytt bestillingsystem
#include "elev.h"
#include "door.h"
#include "logic.h"
#include <stdlib.h>
#include <stdio.h>

//Oversikt over hva som er blitt trykket
int oversikt[N_FLOORS][3] = { 0 };
int rekke[N_FLOORS] = { -1 , -1, -1, -1};

//Oversikt over staten til v�r heis
struct stateHeis* heis;


//Initialiserer heisen
void initialize() {
	//Skal vi ha med minneallokering???
	heis = (struct stateHeis*) malloc(sizeof(struct stateHeis));
	elev_set_motor_direction(DIRN_DOWN);	
	while (1) {
		if (elev_get_floor_sensor_signal() != -1) {
			elev_set_motor_direction(DIRN_STOP);
			break;
		}
	}
	heis->dir = 0;
	heis->lastFloor = elev_get_floor_sensor_signal();
	heis->targetFloor = elev_get_floor_sensor_signal();
}

//Her implementerer vi hva som skjer når man treffer en etasje
void floorSensor(int etasje) {
	elev_set_floor_indicator(etasje);
	heis->lastFloor = etasje;

	if (oversikt[etasje][heis->dir] || oversikt[etasje][2]) {
		//Da skal man plukkes opp! :)
		setDir(0);
		openDoor();
		clearOrdersByFloor(etasje);
		updateRekke(etasje);
	}
	nextJob();
}

//Legger inn nye knappetrykk i bestillingsoversikten og rekkeoversikten
void addNewOrder(int knapp, int etasje) {
	oversikt[etasje][knapp] = 1;
	for (int i = 0; i < N_FLOORS; i++){
		if (rekke[i]==etasje){
			break;
		}
		else if (rekke[i] == -1){
			rekke[i] = etasje;
			break;
		}
	}
	elev_set_button_lamp(knapp, etasje, 1);
}

//Her er det som skjer ved et eventuelt stoppsignal
void stopSignal() {
	printf("%d ",rekke[0]);
/*
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
	*/
}

//Fjerner bestillinger til etasjen en kommer til
void clearOrdersByFloor(int etasje) {
	for (int i = 0; i < 3; i++) {
		oversikt[etasje][i] = 0;
	}
	clearLightsByFloor(etasje);
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

//Skrur av lys på en bestemt etasje
void clearLightsByFloor(int etasje) {
	for (int i = 0; i < 3; i++) {
		elev_set_button_lamp(i, etasje, 0);
	}
}

void nextJob(){
	if (heis->targetFloor == elev_get_floor_sensor_signal()){
		heis->targetFloor = rekke[0];
	}
	
	if (heis->targetFloor == -1){
		setDir(0);
		heis->targetFloor=rekke[0];
	}
	else if (heis->targetFloor < heis->lastFloor){
		setDir(-1);
	}
	else if(heis->targetFloor > heis->lastFloor){
		setDir(1);
	}
	else if(heis->dir == 0){
		setDir(-1);
	}
	else{
		setDir(1);
	}
}

void updateRekke(int etasje){
	for (int i = 0; i < N_FLOORS; i++){
		if (rekke[i] == etasje){
			while(1){
				if (i!=N_FLOORS-1){
					rekke[i] = rekke[i+1];
				}
				else{
					rekke[i]=-1;
					break;
				}
				i++;
			}
		}
	}
}

//Setter motor-retning og oppdaterer FSM
//Ønsker ikke å sette dir til 2, 
void setDir(int retning) {
	elev_set_motor_direction(retning);
	if (retning == -1){
		heis->dir = 1;
	}
	else if (retning == 1){
		heis->dir = 0;
	}
}