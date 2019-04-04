#include "door.h"
#include "elev.h"
#include <stdio.h>
#include <stdlib.h>

void holdDoor(double time){
  for(int c = 1; c <= time*350000000; c++){}
}

void openDoor(){
    elev_set_door_open_lamp(1);
    holdDoor(3);
}

void closeDoor(){
    elev_set_door_open_lamp(0);
}
