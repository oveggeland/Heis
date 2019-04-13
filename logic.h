//Dette er headerfilen tildet nye systemet

struct stateHeis{
	int dir;
	int lastFloor;
	int targetFloor;
	int doorOpen;
};

void initialize();

void setDir(int retning);

void addNewOrder(int etasje, int retning);
void clearAllOrders();

void clearLightsByFloor(int etasje);

void stopSignal();

void floorSensor(int etasje);