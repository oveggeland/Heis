#include "door.h"
#include "elev.h"
#include "logic.h"
#include <stdio.h>
#include <stdlib.h>

void holdDoor(double time){
  for(int c = 1; c <= time*350000000; c++)
  {
	  /*
	if (elev_get_stop_signal()){
		stopSignal();
		//Her kan vi eventuelt legge inn break; istedenfor holdDoor(3);
		//Skjønte ikke om vi skulle avbryte stoppen eller begynne den på nytt ved nytt klikk
	}*/
  }
}

void openDoor(){
    elev_set_door_open_lamp(1);
    holdDoor(3);
	elev_set_door_open_lamp(0);
}