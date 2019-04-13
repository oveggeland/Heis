#include "order.h"
#include "elev.h"
#include "controll.h"
#include <stdio.h>
#include <stdlib.h>

//Deklarerer noe structs og greier

int *hei;
struct bestilling* first;
struct bestilling* current;
struct bestilling* last;

int initOrders(){
  hei = (int*)malloc(sizeof(int));
  *hei = 5;
  first = (struct bestilling*) malloc(sizeof(struct bestilling));
  first->etasje = -1;
  first->retning=-1;
  first->next = NULL;
  current = (struct bestilling*) malloc(sizeof(struct bestilling));
  last = (struct bestilling*) malloc(sizeof(struct bestilling));
  current=first;
  last=first;
  return 3;
};

void addNewOrder(int buttonType, int etasje) {
	struct bestilling* newOrder = (struct bestilling*) malloc(sizeof(struct bestilling));
	newOrder->etasje = etasje;
	newOrder->retning = buttonType;
	newOrder->next = NULL;

	last->next = newOrder;
	last = newOrder;
	elev_set_button_lamp(buttonType, etasje, 1);
}

void clearAllOrders() {
	//Her bør vi kanskje forsøke å frigjøre allokert minne. Se utkommentert kodebit for eksempel til hvordan

	for (int i = 0; i < N_FLOORS; i++) {
		for (int j = 0; j < 3; j++) {
			elev_set_button_lamp(j, i, 0);
		}
	}

	current = first;
	while (1) {
		struct bestilling* temp = current;
		current = temp->next;
		void*slett = temp;
		free(slett);
		if (current == NULL) {
			break;
		}
	}
	

	first->etasje = -1;
	first->retning = -1;
	first->next = NULL;
	current = first;
	last = first;
}

int etasjeTil[N_FLOORS]= {-1};
