#include "controll.h"
#include "elev.h"
#include "door.h"
#include "order.h"
#include <stdio.h>
#include <stdlib.h>

void initialize(){
  //initOrders();
  elev_set_motor_direction(DIRN_DOWN);
  while(1){
    if (elev_get_floor_sensor_signal() == N_FLOORS - 1) {
        elev_set_motor_direction(DIRN_DOWN);
    } else if (elev_get_floor_sensor_signal() == 0) {
        elev_set_motor_direction(DIRN_STOP);
        break;
    }
  }
}


void floorSensor(int etasje){
  elev_set_floor_indicator(etasje);
}

void stopSignal(){
  elev_set_motor_direction(DIRN_STOP);
  elev_set_stop_lamp(1);
  //CLEARALLOLDERS()??
  holdDoor(3);
  elev_set_stop_lamp(0);
}


void controll(){
    initialize();
    while(1){
      if (elev_get_stop_signal()){
        stopSignal();
      }
      int etasje=elev_get_floor_sensor_signal();
      if (etasje>=0){
        floorSensor(etasje);
      }

    }


}
