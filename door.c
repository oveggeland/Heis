#include "door.h"
#include "elev.h"
#include "controll.h"
#include <stdio.h>
#include <time.h>

void holdDoor(){

  time_t rawtime;
  struct tm* timeinfo;
  
  time ( &rawtime );
  timeinfo = localtime ( &rawtime );
  printf ("her er tida: %s", asctime (timeinfo));
  
  int tall = (int) (asctime(timeinfo))[6];
  if (tall > )

}

void openDoor(){
    elev_set_door_open_lamp(1);
    holdDoor(3);
	elev_set_door_open_lamp(0);
}