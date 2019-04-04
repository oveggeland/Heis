#include "order.h"
#include "elev.h"
#include "controll.h"
#include <stdio.h>
#include <stdlib.h>

//Allokere noe gøy

struct etasjeFra* first;
struct etasjeFra* current;
struct etasjeFra* last;

void initOrders(){
  //first->etasje=(int)malloc(sizeof(int))0;
  first->retning=0;
  first->next = NULL;
  //current=first;
  //last=first;
};

int etasjeTil[4]= {-1,-1,-1,-1};
