int initOrders();
void addNewOrder(int buttonType, int etasje);
void clearAllOrders();

struct bestilling{
  int etasje;
  int retning;
  struct bestilling* next;
};